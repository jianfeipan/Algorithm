class Twitter {
private:
    using User = int;
    unordered_map<User, unordered_set<User>> followees_; 

    using Time = size_t;
    using Tid = int;
    using Tweet = pair<Time, Tid>;
    unordered_map<User, vector<Tweet>> tweets_;

    Time t_;
public:
    Twitter() : t_(0) {
        
    }
    
    void postTweet(int userId, int tweetId) {
        tweets_[userId].push_back({t_, tweetId});
        ++t_;
    }
    
    vector<int> getNewsFeed(int userId) {
        constexpr size_t feeds_num = 10;

        priority_queue<Tweet, vector<Tweet>, greater<Tweet>> earlist;
        auto push = [&] (const Tweet& tweet) {
            if (earlist.size() < feeds_num) {
                earlist.push(tweet);
            } else {
                if (tweet.first > earlist.top().first) {
                    earlist.pop();
                    earlist.push(tweet);
                }
            }
        };

        // push my tweets
        for(const auto& tweet : tweets_[userId]) push(tweet);

        // push my folowees' tweets
        for (const auto& followee : followees_[userId]) {
            for(const auto& tweet : tweets_[followee]) {
                push(tweet);
            }
        }

        vector<int> feeds; feeds.reserve(feeds_num);
        while (!earlist.empty()) {
            feeds.push_back(earlist.top().second);
            earlist.pop();
        }
        return { feeds.rbegin(), feeds.rend() };
    }
    
    void follow(int followerId, int followeeId) {
        if(followerId == followeeId) return;
        // update or insert
        followees_[followerId].insert(followeeId);
    }
    
    void unfollow(int followerId, int followeeId) {
        // if exist...
        followees_[followerId].erase(followeeId);
    }
};
