/*
1079. Letter Tile Possibilities
Medium
2.3K
64
Companies
You have n  tiles, where each tile has one letter tiles[i] printed on it.

Return the number of possible non-empty sequences of letters you can make using the letters printed on those tiles.

 

Example 1:

Input: tiles = "AAB"
Output: 8
Explanation: The possible sequences are "A", "B", "AA", "AB", "BA", "AAB", "ABA", "BAA".
Example 2:

Input: tiles = "AAABBC"
Output: 188
Example 3:

Input: tiles = "V"
Output: 1
 
*/


class Solution {

    /*
    fact:
        AA-> A, AA
        AB-> A, B, AB, BA

    idea:
        what you have is resources, 
        every time you put a letter, you sonsume one letter from the resource and you have one possibility. 


        

    */

private:
    int countDifferentTilePossibilities(vector<int> &freq){

        int sum = 0;
        for(int i = 0 ; i < 26 ; i++){
            if(freq[i] > 0){
                freq[i]--;
                sum++; //if we take this letter, we have one possibility
                sum += countDifferentTilePossibilities(freq); //How many possibility left 


                freq[i]++;//back track: if we don't take this letter, to go next round and take another letter
            }
            
        }
        return sum;
    }
public:
    int numTilePossibilities(string tiles) {
        vector<int> freq(26, 0);
        for(auto &ch:tiles)
            freq[ch - 'A']++;

        return countDifferentTilePossibilities(freq);
    }
};
