#include <unordered_map>
#include <unordered_set>
#include <vector>
#include <queue>

using namespace std;

class Twitter {
private:
    using Time = int;

    struct Tweet {
        Time time;
        int id;
    };

    struct Node {
        Time time;
        int tweetId;
        int userId;
        int index; // index in that user's tweet list

        bool operator<(const Node& other) const {
            return time < other.time; // max-heap by time
        }
    };

    unordered_map<int, vector<Tweet>> tweets;
    unordered_map<int, unordered_set<int>> follows;
    Time globalTime = 0;

public:
    Twitter() {}

    void postTweet(int userId, int tweetId) {
        tweets[userId].push_back({globalTime++, tweetId});
    }

    vector<int> getNewsFeed(int userId) {
        priority_queue<Node> pq;

        // include self automatically
        follows[userId].insert(userId);

        // push latest tweet from each followee
        for (int followee : follows[userId]) {
            auto& t = tweets[followee];
            if (!t.empty()) {
                int idx = t.size() - 1;
                pq.push({t[idx].time, t[idx].id, followee, idx});
            }
        }

        vector<int> feed;

        while (!pq.empty() && feed.size() < 10) {
            auto cur = pq.top();
            pq.pop();

            feed.push_back(cur.tweetId);

            int nextIdx = cur.index - 1;
            if (nextIdx >= 0) {
                auto& t = tweets[cur.userId];
                pq.push({t[nextIdx].time, t[nextIdx].id, cur.userId, nextIdx});
            }
        }

        return feed;
    }

    void follow(int followerId, int followeeId) {
        follows[followerId].insert(followeeId);
    }

    void unfollow(int followerId, int followeeId) {
        if (followerId != followeeId)
            follows[followerId].erase(followeeId);
    }
};