#include <unordered_map>
#include <unordered_set>
#include <queue>

using namespace std;
class Twitter {
private:
    using UserId = int;
    using TweetId = int;
    using Time = int;
    using Tweet = pair<Time, TweetId>;
    using Tweets = vector<Tweet>;
    unordered_map<UserId, Tweets> user_tweets;

    using Users = unordered_set<UserId>;
    unordered_map<UserId, Users> user_following;

    int t;
public:
    Twitter() : t(0){
        
    }
    
    void postTweet(int userId, int tweetId) {

        user_tweets[userId].emplace_back(t, tweetId);
        ++t;
    }
    
    vector<int> getNewsFeed(int userId) {
        constexpr static int MAX = 10;
        using Index = int;
        priority_queue<pair<Time, tuple<TweetId, UserId, Index>>> maxHeap;

        for(auto publisher : user_following[userId]){
            auto& tweets = user_tweets[publisher];
            if(!tweets.empty()){
                auto index = tweets.size() -1;
                auto time = tweets.back().first;
                auto tweetId = tweets.back().second;
                maxHeap.push({time, {tweetId, publisher, index}});
            }
        }

        vector<int> top10;// k way merge
        for(int i=0; i<MAX; ++i){
            if(maxHeap.empty()) break;
            auto [time, tweet] = maxHeap.top();maxHeap.pop();
            auto [tweetId, publisher, index] = tweet;
            top10.push_back(tweetId);
            
            --index;
            if(index>-1){
                const auto& tweets = user_tweets[publisher];
                auto time = tweets[index].first;
                auto tweetId = tweets[index].second;
                maxHeap.push({time, {tweetId, publisher, index}});
            }
        }
        return top10;
    }
    
    void follow(int followerId, int followeeId) {
        user_following[followerId].insert(followeeId);
    }
    
    void unfollow(int followerId, int followeeId) {
        user_following[followerId].erase(followeeId);
    }
};
