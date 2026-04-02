/*
2048 game
Implement the "move" logic for a 4x4 grid
and pack the entire board in to a single unit64_t for high speed comparison
*/

#include <cstdint>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <array>

/*
 * Board packing:
 *   64-bit integer, 16 nibbles (4 bits each), one per cell.
 *   Nibble value 0 = empty, k>0 = tile 2^k.
 *   Row 0 is the top 16 bits, row 3 is the bottom 16 bits.
 *
 *   Layout (nibble indices, MSB first):
 *     row0: [15 14 13 12]   (bits 60-63, 56-59, 52-55, 48-51)
 *     row1: [11 10  9  8]
 *     row2: [ 7  6  5  4]
 *     row3: [ 3  2  1  0]
 */

using Board = uint64_t;
using Row   = uint16_t;          // one row = 4 nibbles

/*
we don't work with 0 2 4 8 16 ...
we work with 0 1 2  3 4...
*/

// ── Precomputed tables (filled once) ────────────────────────────
//every row is a uint_64_t 0x0000 to oxFFFF
// precompute all possible transactions, left right and score
static Row  move_left_table [65536];   // row -> row after sliding left (2^16)
static Row  move_right_table[65536];   // row -> row after sliding right
static int  score_table     [65536];   // row -> score gained by that slide

// ── Nibble / row helpers ────────────────────────────────────────

inline Row get_row(Board b, int r) {
    return static_cast<Row>((b >> (r * 16)) & 0xFFFF);
}

inline Board set_row(Board b, int r, Row row) {
    Board mask = static_cast<Board>(0xFFFF) << (r * 16);
    return (b & ~mask) | (static_cast<Board>(row) << (r * 16));
}

inline int get_cell(Board b, int pos) {           // pos 0..15
    return (b >> (pos * 4)) & 0xF;
}

inline Board set_cell(Board b, int pos, int val) {
    Board mask = static_cast<Board>(0xF) << (pos * 4);
    return (b & ~mask) | (static_cast<Board>(val & 0xF) << (pos * 4));
}

// Reverse a 16-bit row (swap the four nibbles)
inline Row reverse_row(Row r) {
    return ((r & 0xF) << 12) | ((r & 0xF0) << 4) |
           ((r & 0xF00) >> 4) | ((r & 0xF000) >> 12);
}

// Transpose the board (rows <-> columns)
Board transpose(Board b) {
    // Swap nibbles so that column i becomes row i
    Board t = 0;
    for (int r = 0; r < 4; ++r)
        for (int c = 0; c < 4; ++c) {
            int val = get_cell(b, r * 4 + c);
            t = set_cell(t, c * 4 + r, val);
        }
    return t;
}

// ── Build lookup tables ─────────────────────────────────────────
void init_tables() {
    for (int row = 0; row < 65536; ++row) {
        // Unpack the four nibbles
        int cells[4] = {
            (row >>  0) & 0xF,
            (row >>  4) & 0xF,
            (row >>  8) & 0xF,
            (row >> 12) & 0xF
        };
        /*
        for exmaple: cells = [1 2 0  0] represent [2 4 0 0 ] in the game of this row
        
        */

        // Slide left: compact non-zero to the left, then merge
        int merged[4] = {0, 0, 0, 0};
        int score = 0;
        int wp = 0;                           // write pointer

        // 1. compact
        int buf[4] = {0};
        int n = 0;// how many nums in max
        for (int i = 0; i < 4; ++i)
            if (cells[i]) buf[n++] = cells[i]; // copy

        // 2. merge adjacent equal tiles (left to right)
        for (int i = 0; i < n; ) {
            if (i + 1 < n && buf[i] == buf[i + 1]) {
                int new_val = buf[i] + 1;     // exponent increases by 1, 2 become 4, 1 become 2
                merged[wp++] = new_val;
                score += (1 << new_val);      // score = value of merged tile
                i += 2;
            } else {
                merged[wp++] = buf[i];
                i += 1;
            }
        }

        Row result = static_cast<Row>(
            (merged[0] <<  0) | (merged[1] <<  4) |
            (merged[2] <<  8) | (merged[3] << 12));

        Row rev_row    = reverse_row(static_cast<Row>(row));
        Row rev_result = reverse_row(result);

        move_left_table [row]     = result;
        move_right_table[rev_row] = rev_result;
        score_table     [row]     = score;
    }
}

// ── Move functions ──────────────────────────────────────────────

int move_left(Board& b) {
    int total_score = 0;
    Board nb = 0;
    for (int r = 0; r < 4; ++r) {
        Row row = get_row(b, r);
        nb = set_row(nb, r, move_left_table[row]);
        total_score += score_table[row];
    }
    b = nb;
    return total_score;
}

int move_right(Board& b) {
    int total_score = 0;
    Board nb = 0;
    for (int r = 0; r < 4; ++r) {
        Row row = get_row(b, r);
        nb = set_row(nb, r, move_right_table[row]);
        total_score += score_table[reverse_row(row)];
    }
    b = nb;
    return total_score;
}

int move_up(Board& b) {
    // Transpose, slide left, transpose back
    Board t = transpose(b);
    int score = move_left(t);
    b = transpose(t);
    return score;
}

int move_down(Board& b) {
    Board t = transpose(b);
    int score = move_right(t);
    b = transpose(t);
    return score;
}

// Attempt a move; returns score gained, or -1 if board unchanged
int do_move(Board& b, int dir) {
    Board old = b;
    int score = 0;
    switch (dir) {
        case 0: score = move_left(b);  break;
        case 1: score = move_right(b); break;
        case 2: score = move_up(b);    break;
        case 3: score = move_down(b);  break;
    }
    if (b == old) return -1;  // nothing changed
    return score;
}

// ── Utility ─────────────────────────────────────────────────────

int count_empty(Board b) {
    int cnt = 0;
    for (int i = 0; i < 16; ++i)
        if (get_cell(b, i) == 0) ++cnt;
    return cnt;
}

// Place a random tile (90% = 2, 10% = 4) on an empty cell
bool spawn_tile(Board& b) {
    int empty = count_empty(b);
    if (empty == 0) return false;
    int idx = rand() % empty;
    int val = (rand() % 10 == 0) ? 2 : 1;    // exponent: 1=2, 2=4
    for (int i = 0; i < 16; ++i) {
        if (get_cell(b, i) == 0) {
            if (idx == 0) { b = set_cell(b, i, val); return true; }
            --idx;
        }
    }
    return false;
}

bool game_over(Board b) {
    if (count_empty(b) > 0) return false;
    // Check horizontal merges
    for (int r = 0; r < 4; ++r)
        for (int c = 0; c < 3; ++c)
            if (get_cell(b, r*4+c) == get_cell(b, r*4+c+1)) return false;
    // Check vertical merges
    for (int r = 0; r < 3; ++r)
        for (int c = 0; c < 4; ++c)
            if (get_cell(b, r*4+c) == get_cell(b, (r+1)*4+c)) return false;
    return true;
}

void print_board(Board b) {
    std::cout << "┌──────┬──────┬──────┬──────┐\n";
    for (int r = 3; r >= 0; --r) {           // row 3 = top visually
        std::cout << "│";
        for (int c = 0; c < 4; ++c) {
            int v = get_cell(b, r * 4 + c);
            if (v == 0)
                printf(" %4s │", "·");
            else
                printf(" %4d │", 1 << v);
        }
        std::cout << "\n";
        if (r > 0) std::cout << "├──────┼──────┼──────┼──────┤\n";
    }
    std::cout << "└──────┴──────┴──────┴──────┘\n";
}

// ── Interactive game loop ───────────────────────────────────────
int main() {
    srand(static_cast<unsigned>(time(nullptr)));
    init_tables();

    Board board = 0;
    int score = 0;

    spawn_tile(board);
    spawn_tile(board);

    const char* dir_name[] = {"LEFT", "RIGHT", "UP", "DOWN"};

    while (true) {
        print_board(board);
        std::cout << "Score: " << score << "\n";

        if (game_over(board)) {
            std::cout << "Game Over!\n";
            break;
        }

        std::cout << "Move (w/a/s/d or q to quit): ";
        char ch;
        std::cin >> ch;

        int dir = -1;
        switch (ch) {
            case 'a': dir = 0; break;   // left
            case 'd': dir = 1; break;   // right
            case 'w': dir = 2; break;   // up
            case 's': dir = 3; break;   // down
            case 'q': std::cout << "Bye!\n"; return 0;
            default:  std::cout << "Use w/a/s/d\n"; continue;
        }

        int gained = do_move(board, dir);
        if (gained < 0) {
            std::cout << "Invalid move!\n";
            continue;
        }
        score += gained;
        std::cout << dir_name[dir] << " +" << gained << "\n";
        spawn_tile(board);
    }

    return 0;
}

