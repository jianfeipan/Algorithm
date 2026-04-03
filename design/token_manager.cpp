/*
Designe a system to manage tokens for a web application.
with a fixed TTL (Time To Live) for each token.
use lazy expiration to make sure the check of tocken doesn't cause bottleneck

*/

#include <iostream>
#include <unordered_map>
#include <string>
#include <chrono>

using namespace std;
using Clock = chrono::steady_clock;
using TimePoint = chrono::time_point<Clock>;

class TokenManager {
    int ttlSeconds;
    // token -> expiration time
    unordered_map<string, TimePoint> tokens;

public:
    TokenManager(int ttlSeconds) : ttlSeconds(ttlSeconds) {}

    // Generate/store a token. Returns the token string.
    void addToken(const string& token) {
        tokens[token] = Clock::now() + chrono::seconds(ttlSeconds);
    }

    // Validate a token — lazy expiration: only check expiry when accessed.
    bool validateToken(const string& token) {
        auto it = tokens.find(token);
        if (it == tokens.end()) return false;

        if (Clock::now() > it->second) {
            // Token expired — remove lazily on access
            tokens.erase(it);
            return false;
        }
        return true;
    }

    // Refresh a token's TTL (e.g. on activity). Returns false if token is missing/expired.
    bool refreshToken(const string& token) {
        auto it = tokens.find(token);
        if (it == tokens.end()) return false;

        if (Clock::now() > it->second) {
            tokens.erase(it);
            return false;
        }
        it->second = Clock::now() + chrono::seconds(ttlSeconds);
        return true;
    }

    // Remove a token explicitly (e.g. logout).
    void revokeToken(const string& token) {
        tokens.erase(token);
    }

    size_t size() const { return tokens.size(); }
};

// ---- demo ----
int main() {
    TokenManager mgr(3); // 3-second TTL

    mgr.addToken("abc123");
    mgr.addToken("xyz789");

    cout << "Validate abc123: " << mgr.validateToken("abc123") << "\n"; // 1
    cout << "Validate unknown: " << mgr.validateToken("nope")  << "\n"; // 0

    cout << "Sleeping 2s...\n";
    this_thread::sleep_for(chrono::seconds(2));

    cout << "Refresh abc123: " << mgr.refreshToken("abc123") << "\n";   // 1 (reset TTL)

    cout << "Sleeping 2s...\n";
    this_thread::sleep_for(chrono::seconds(2));

    // abc123 was refreshed so still alive; xyz789 should be expired
    cout << "Validate abc123: " << mgr.validateToken("abc123") << "\n"; // 1
    cout << "Validate xyz789: " << mgr.validateToken("xyz789") << "\n"; // 0 (lazily expired)

    cout << "Active tokens (lazy count): " << mgr.size() << "\n"; // 1 (xyz789 was erased on access)

    mgr.revokeToken("abc123");
    cout << "After revoke, validate abc123: " << mgr.validateToken("abc123") << "\n"; // 0

    return 0;
}


