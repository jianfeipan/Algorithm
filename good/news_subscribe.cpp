#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <deque>
#include <algorithm>
#include <cstdint>


struct Subscription {
   uint32_t id;
   uint32_t minInterest;
   uint32_t maxNewsPerSecond;
   std::unordered_set<std::string> topics;
};


struct NewsItem {
   uint32_t id;
   double timestamp;
   uint32_t interest;
   std::vector<std::string> topics;
};


class NewsProvider {
private:
   std::unordered_map<uint32_t, Subscription> subscriptions;
   std::unordered_map<uint32_t, NewsItem> newsItems;


   std::unordered_map<uint32_t, std::unordered_set<uint32_t>> deliveredNews;
   std::unordered_map<uint32_t, std::deque<double>> deliveryTimestamps;


public:
   bool
   AddSubscription(
       uint32_t id,
       uint32_t minInterest,
       uint32_t maxNewsPerSecond,
       const std::vector<std::string>& topics) {


       // option 1
       if (subscriptions.find(id) != subscriptions.end()) {
           auto& sub = subscriptions[id];
           sub.minInterest = minInterest;
           sub.maxNewsPerSecond = maxNewsPerSecond;
           sub.topics = std::unordered_set<std::string>(topics.begin(), topics.end());
           return true;
       }


       Subscription sub;
       sub.id = id;
       sub.minInterest = minInterest;
       sub.maxNewsPerSecond = maxNewsPerSecond;
       sub.topics = std::unordered_set<std::string>(topics.begin(), topics.end());


       subscriptions[id] = std::move(sub);
       // option 2
       subscriptions[id] = {id, minInterest, maxNewsPerSecond, std::unordered_set<std::string>(topics.begin(), topics.end())};
       // option3 best:
       std::unordered_set<std::string> topicSet(topics.begin(), topics.end());
       auto [it, inserted] = subscriptions.try_emplace(
           id,
           id,
           minInterest,
           maxNewsPerSecond,
           std::move(topicSet)
       );


       if (!inserted) {
           auto& sub = it->second;
           sub.minInterest = minInterest;
           sub.maxNewsPerSecond = maxNewsPerSecond;
           sub.topics = std::move(topicSet); // Recycle the topicSet we made
       }
       return true;
   }


   bool
   removeSubscription(uint32_t id) {


       auto it = subscriptions.find(id);
       if (it == subscriptions.end()) {
           return false;
       }
       subscriptions.erase(it);
       deliveredNews.erase(id);
       deliveryTimestamps.erase(id);
       return true;
   }


   bool NewsReceived(uint32_t id, double timestamp, uint32_t interest, const std::vector<std::string>& topics) {
       if (newsItems.find(id) != newsItems.end()) {
           return false;
       }


       NewsItem item{id, timestamp, interest, topics};
       newsItems[id] = std::move(item);
       return true;
   }


   // Adjusted return type depending on what your specific stub requires.
   // If the template requires std::unordered_map, change it here.
   std::unordered_map<uint32_t, std::vector<uint32_t>> Publish(double timestamp, double maxAge) {


       // 1. Filter out expired news based on maxAge constraint
       std::vector<uint32_t> news_ids;
       for (const auto& [id, item] : newsItems) {
           if (timestamp - item.timestamp <= maxAge && timestamp >= item.timestamp) {
               news_ids.push_back(id);
           }
       }


       // 2. Sort eligible news by specified priority constraints
        std::sort(news_ids.begin(), news_ids.end(),[this](uint32_t left, uint32_t right){
           const auto& left_news = this->newsItems.at(left);
           const auto& right_news = this->newsItems.at(right);


           if (left_news.interest != right_news.interest) {
               return left_news.interest > right_news.interest; // Highest interest first
           }
           if (left_news.timestamp != right_news.timestamp) {
               return left_news.timestamp < right_news.timestamp; // Oldest timestamp first
           }
           return left_news.id > right_news.id; // Highest ID first
        });


       std::unordered_map<uint32_t, std::vector<uint32_t>> result;


       // 3. Process news delivery
       for (const auto& news_id : news_ids) {
           std::vector<uint32_t> notifiedSubs;
           const auto& item = newsItems.at(news_id);
           for (const auto& [subId, sub] : subscriptions) {
               // Minimum interest score criteria (cheap check first)
               if (item.interest < sub.minInterest) {
                   continue;
               }


               // Topic matching
               bool topicMatches = std::any_of(item.topics.begin(), item.topics.end(), [&](const std::string& topic) {
                   return sub.topics.count(topic);
               });


               if (!topicMatches) {
                   continue;
               }


               // No duplicate delivery
               // Use find() to avoid inserting an empty entry for subs that never received news.
               auto deliveredIt = deliveredNews.find(subId);
               if (deliveredIt != deliveredNews.end() && deliveredIt->second.count(news_id)) {
                   continue;
               }


               // Sliding window rate limiting check [current_publish_time - 1.0, current_publish_time]
               // Only touch deliveryTimestamps once we know the sub is a candidate.
               auto& dq = deliveryTimestamps[subId];
               while (!dq.empty() && dq.front() < timestamp - 1.0) {
                   dq.pop_front();
               }


               if (dq.size() < sub.maxNewsPerSecond) {
                   // Crucial Fix: Push the current execution 'timestamp' to evaluate window limits correctly,
                   // or if the problem requires tracking item.timestamp, swap it with 'item.timestamp'.
                   dq.push_back(item.timestamp);
                   deliveredNews[subId].insert(item.id);
                   notifiedSubs.push_back(subId);
               }
           }


           if (!notifiedSubs.empty()) {
               result[news_id] = std::move(notifiedSubs);
           }
       }


       return result;
   }
};


// =====================================================================
// Tests
// Build: g++ -std=c++20 -Wall -Wextra -O0 -g NewsProvider.cpp -o NewsProvider
// Run:   ./NewsProvider
// =====================================================================


#include <cassert>
#include <cstdio>


namespace test {


static int g_pass = 0;
static int g_fail = 0;
static const char* g_current_test = "";


#define CHECK(cond)                                                              \
   do {                                                                         \
       if (!(cond)) {                                                           \
           std::printf("  [FAIL] %s:%d  %s   (test: %s)\n",                     \
                       __FILE__, __LINE__, #cond, test::g_current_test);        \
           ++test::g_fail;                                                      \
       } else {                                                                 \
           ++test::g_pass;                                                      \
       }                                                                        \
   } while (0)


#define RUN(fn)                                                                  \
   do {                                                                         \
       test::g_current_test = #fn;                                              \
       std::printf("Running %s\n", #fn);                                        \
       fn();                                                                    \
   } while (0)


// Helper: sort a vector<uint32_t> so we can compare deterministically
// (subscription iteration order is unspecified in unordered_map).
static std::vector<uint32_t> sorted(std::vector<uint32_t> v) {
   std::sort(v.begin(), v.end());
   return v;
}


// ---------- AddSubscription ----------


static void test_add_subscription_new() {
   NewsProvider np;
   CHECK(np.AddSubscription(1, 10, 5, {"sports", "tech"}) == true);
}


static void test_add_subscription_update_existing() {
   NewsProvider np;
   np.AddSubscription(1, 10, 5, {"sports"});
   CHECK(np.AddSubscription(1, 20, 2, {"tech"}) == true);


   // Verify update took effect: sports item with interest 15 should NOT be delivered
   // under the updated subscription (minInterest=20, topics={tech}).
   np.NewsReceived(100, 1.0, 15, {"sports"});
   auto r = np.Publish(1.0, 10.0);
   CHECK(r.empty());
}


static void test_add_subscription_empty_topics() {
   NewsProvider np;
   CHECK(np.AddSubscription(1, 0, 10, {}) == true);
   np.NewsReceived(100, 1.0, 100, {"anything"});
   auto r = np.Publish(1.0, 10.0);
   CHECK(r.empty());
}


static void test_add_subscription_duplicate_topics_in_input() {
   NewsProvider np;
   CHECK(np.AddSubscription(1, 0, 10, {"a", "a", "a", "b"}) == true);
   np.NewsReceived(100, 1.0, 5, {"a"});
   auto r = np.Publish(1.0, 10.0);
   CHECK(r.size() == 1);
   CHECK(r[100] == std::vector<uint32_t>{1});
}


// ---------- removeSubscription ----------


static void test_remove_existing() {
   NewsProvider np;
   np.AddSubscription(1, 0, 10, {"a"});
   CHECK(np.removeSubscription(1) == true);
}


static void test_remove_nonexistent() {
   NewsProvider np;
   CHECK(np.removeSubscription(42) == false);
}


static void test_remove_twice() {
   NewsProvider np;
   np.AddSubscription(1, 0, 10, {"a"});
   CHECK(np.removeSubscription(1) == true);
   CHECK(np.removeSubscription(1) == false);
}


static void test_remove_clears_delivery_state() {
   NewsProvider np;
   np.AddSubscription(1, 0, 10, {"a"});
   np.NewsReceived(100, 1.0, 5, {"a"});
   auto r1 = np.Publish(1.0, 10.0);
   CHECK(r1.size() == 1);


   np.removeSubscription(1);
   np.AddSubscription(1, 0, 10, {"a"});
   auto r2 = np.Publish(1.0, 10.0);
   CHECK(r2.size() == 1);
   CHECK(r2[100] == std::vector<uint32_t>{1});
}


// ---------- NewsReceived ----------


static void test_news_received_new() {
   NewsProvider np;
   CHECK(np.NewsReceived(100, 1.0, 5, {"a"}) == true);
}


static void test_news_received_duplicate_rejected() {
   NewsProvider np;
   CHECK(np.NewsReceived(100, 1.0, 5, {"a"}) == true);
   CHECK(np.NewsReceived(100, 2.0, 99, {"b"}) == false);


   // Confirm the original content is preserved.
   np.AddSubscription(1, 0, 10, {"a"});
   auto r = np.Publish(1.0, 10.0);
   CHECK(r.size() == 1);
   CHECK(r[100] == std::vector<uint32_t>{1});
}


// ---------- Publish: filtering by age ----------


static void test_publish_no_news_no_subs() {
   NewsProvider np;
   auto r = np.Publish(1.0, 10.0);
   CHECK(r.empty());
}


static void test_publish_no_subs() {
   NewsProvider np;
   np.NewsReceived(100, 1.0, 5, {"a"});
   auto r = np.Publish(1.0, 10.0);
   CHECK(r.empty());
}


static void test_publish_no_news() {
   NewsProvider np;
   np.AddSubscription(1, 0, 10, {"a"});
   auto r = np.Publish(1.0, 10.0);
   CHECK(r.empty());
}


static void test_publish_age_boundary_inclusive() {
   NewsProvider np;
   np.AddSubscription(1, 0, 10, {"a"});
   np.NewsReceived(100, 1.0, 5, {"a"});
   auto r = np.Publish(6.0, 5.0); // age == maxAge → included
   CHECK(r.size() == 1);
}


static void test_publish_age_expired() {
   NewsProvider np;
   np.AddSubscription(1, 0, 10, {"a"});
   np.NewsReceived(100, 1.0, 5, {"a"});
   auto r = np.Publish(6.001, 5.0); // age > maxAge → excluded
   CHECK(r.empty());
}


static void test_publish_future_news_excluded() {
   NewsProvider np;
   np.AddSubscription(1, 0, 10, {"a"});
   np.NewsReceived(100, 10.0, 5, {"a"});
   auto r = np.Publish(5.0, 100.0); // publish < item → excluded
   CHECK(r.empty());
}


static void test_publish_same_timestamp_included() {
   NewsProvider np;
   np.AddSubscription(1, 0, 10, {"a"});
   np.NewsReceived(100, 5.0, 5, {"a"});
   auto r = np.Publish(5.0, 0.0); // maxAge=0 with equal timestamps → included
   CHECK(r.size() == 1);
}


// ---------- Publish: minInterest ----------


static void test_publish_interest_boundary_equal() {
   NewsProvider np;
   np.AddSubscription(1, 10, 10, {"a"});
   np.NewsReceived(100, 1.0, 10, {"a"});
   auto r = np.Publish(1.0, 10.0);
   CHECK(r.size() == 1);
}


static void test_publish_interest_below() {
   NewsProvider np;
   np.AddSubscription(1, 10, 10, {"a"});
   np.NewsReceived(100, 1.0, 9, {"a"});
   auto r = np.Publish(1.0, 10.0);
   CHECK(r.empty());
}


// ---------- Publish: topic matching ----------


static void test_publish_no_topic_overlap() {
   NewsProvider np;
   np.AddSubscription(1, 0, 10, {"a", "b"});
   np.NewsReceived(100, 1.0, 5, {"c", "d"});
   auto r = np.Publish(1.0, 10.0);
   CHECK(r.empty());
}


static void test_publish_single_topic_match() {
   NewsProvider np;
   np.AddSubscription(1, 0, 10, {"a", "b"});
   np.NewsReceived(100, 1.0, 5, {"b", "z"});
   auto r = np.Publish(1.0, 10.0);
   CHECK(r.size() == 1);
   CHECK(r[100] == std::vector<uint32_t>{1});
}


static void test_publish_multi_topic_match_delivers_once() {
   NewsProvider np;
   np.AddSubscription(1, 0, 10, {"a", "b", "c"});
   np.NewsReceived(100, 1.0, 5, {"a", "b", "c"});
   auto r = np.Publish(1.0, 10.0);
   CHECK(r.size() == 1);
   CHECK(r[100] == std::vector<uint32_t>{1});
}


static void test_publish_news_with_empty_topics() {
   NewsProvider np;
   np.AddSubscription(1, 0, 10, {"a"});
   np.NewsReceived(100, 1.0, 5, {});
   auto r = np.Publish(1.0, 10.0);
   CHECK(r.empty());
}


// ---------- Publish: duplicate suppression ----------


static void test_publish_no_duplicate_across_calls() {
   NewsProvider np;
   np.AddSubscription(1, 0, 10, {"a"});
   np.NewsReceived(100, 1.0, 5, {"a"});


   auto r1 = np.Publish(1.0, 10.0);
   CHECK(r1.size() == 1);


   auto r2 = np.Publish(2.0, 10.0);
   CHECK(r2.empty());
}


// ---------- Publish: rate limiting ----------


static void test_publish_rate_limit_zero() {
   NewsProvider np;
   np.AddSubscription(1, 0, 0, {"a"});
   np.NewsReceived(100, 1.0, 5, {"a"});
   auto r = np.Publish(1.0, 10.0);
   CHECK(r.empty());
}


static void test_publish_rate_limit_one_in_single_batch() {
   NewsProvider np;
   np.AddSubscription(1, 0, 1, {"a"});
   np.NewsReceived(100, 1.0, 5, {"a"});
   np.NewsReceived(101, 1.0, 5, {"a"});


   auto r = np.Publish(1.0, 10.0);
   CHECK(r.size() == 1);
}


static void test_publish_rate_limit_sliding_window_clears() {
   NewsProvider np;
   np.AddSubscription(1, 0, 1, {"a"});
   np.NewsReceived(100, 1.0, 5, {"a"});
   auto r1 = np.Publish(1.0, 10.0);
   CHECK(r1.size() == 1);


   np.NewsReceived(101, 2.5, 5, {"a"});
   auto r2 = np.Publish(2.5, 10.0);
   CHECK(r2.size() == 1);
   CHECK(r2[101] == std::vector<uint32_t>{1});
}


static void test_publish_rate_limit_window_boundary_blocks() {
   // Strict `<` trim: entry with delta == 1.0 is retained → still blocks.
   NewsProvider np;
   np.AddSubscription(1, 0, 1, {"a"});
   np.NewsReceived(100, 1.0, 5, {"a"});
   auto r1 = np.Publish(1.0, 10.0);
   CHECK(r1.size() == 1);


   np.NewsReceived(101, 2.0, 5, {"a"});
   auto r2 = np.Publish(2.0, 10.0);
   CHECK(r2.empty());
}


static void test_publish_rate_limit_window_boundary_allows() {
   // Just past boundary (delta > 1.0) → trimmed → delivery allowed.
   NewsProvider np;
   np.AddSubscription(1, 0, 1, {"a"});
   np.NewsReceived(100, 1.0, 5, {"a"});
   auto r1 = np.Publish(1.0, 10.0);
   CHECK(r1.size() == 1);


   np.NewsReceived(102, 2.001, 5, {"a"});
   auto r2 = np.Publish(2.001, 10.0);
   CHECK(r2.size() == 1);
   CHECK(r2[102] == std::vector<uint32_t>{1});
}


// ---------- Publish: sort order ----------


static void test_publish_sort_order_interest_then_ts_then_id() {
   // Sort: interest desc, then timestamp asc, then id desc.
   //   id=200 interest=10 ts=1.0  ← rank 1 (highest interest)
   //   id=203 interest=5  ts=1.0  ← rank 2 (higher id among same interest+ts)
   //   id=201 interest=5  ts=1.0  ← rank 3
   //   id=202 interest=5  ts=2.0  ← rank 4 (later ts)
   // With rate=2, only ranks 1 & 2 should be delivered.
   NewsProvider np;
   np.AddSubscription(1, 0, 2, {"a"});
   np.NewsReceived(200, 1.0, 10, {"a"});
   np.NewsReceived(203, 1.0, 5,  {"a"});
   np.NewsReceived(201, 1.0, 5,  {"a"});
   np.NewsReceived(202, 2.0, 5,  {"a"});


   auto r = np.Publish(2.0, 10.0);
   CHECK(r.count(200) == 1);
   CHECK(r.count(203) == 1);
   CHECK(r.count(201) == 0);
   CHECK(r.count(202) == 0);
}


// ---------- Publish: multiple subs ----------


static void test_publish_multi_sub_partial_filter() {
   NewsProvider np;
   np.AddSubscription(1, 0,  10, {"a"});   // matches
   np.AddSubscription(2, 20, 10, {"a"});   // minInterest too high
   np.AddSubscription(3, 0,  10, {"b"});   // topic mismatch
   np.NewsReceived(100, 1.0, 5, {"a"});


   auto r = np.Publish(1.0, 10.0);
   CHECK(r.size() == 1);
   CHECK(r[100] == std::vector<uint32_t>{1});
}


static void test_publish_multi_sub_all_delivered() {
   NewsProvider np;
   np.AddSubscription(1, 0, 10, {"a"});
   np.AddSubscription(2, 0, 10, {"a"});
   np.AddSubscription(3, 0, 10, {"a"});
   np.NewsReceived(100, 1.0, 5, {"a"});


   auto r = np.Publish(1.0, 10.0);
   CHECK(r.size() == 1);
   CHECK(sorted(r[100]) == std::vector<uint32_t>({1u, 2u, 3u}));
}


// ---------- Publish: idempotence ----------


static void test_publish_repeated_with_no_new_data() {
   NewsProvider np;
   np.AddSubscription(1, 0, 10, {"a"});
   np.NewsReceived(100, 1.0, 5, {"a"});
   auto r1 = np.Publish(1.0, 10.0);
   CHECK(r1.size() == 1);
   auto r2 = np.Publish(1.0, 10.0);
   CHECK(r2.empty());
}


} // namespace test


int main() {
   using namespace test;


   // AddSubscription
   RUN(test_add_subscription_new);
   RUN(test_add_subscription_update_existing);
   RUN(test_add_subscription_empty_topics);
   RUN(test_add_subscription_duplicate_topics_in_input);


   // removeSubscription
   RUN(test_remove_existing);
   RUN(test_remove_nonexistent);
   RUN(test_remove_twice);
   RUN(test_remove_clears_delivery_state);


   // NewsReceived
   RUN(test_news_received_new);
   RUN(test_news_received_duplicate_rejected);


   // Publish — filtering
   RUN(test_publish_no_news_no_subs);
   RUN(test_publish_no_subs);
   RUN(test_publish_no_news);
   RUN(test_publish_age_boundary_inclusive);
   RUN(test_publish_age_expired);
   RUN(test_publish_future_news_excluded);
   RUN(test_publish_same_timestamp_included);


   // Publish — interest
   RUN(test_publish_interest_boundary_equal);
   RUN(test_publish_interest_below);


   // Publish — topic
   RUN(test_publish_no_topic_overlap);
   RUN(test_publish_single_topic_match);
   RUN(test_publish_multi_topic_match_delivers_once);
   RUN(test_publish_news_with_empty_topics);


   // Publish — duplicates
   RUN(test_publish_no_duplicate_across_calls);


   // Publish — rate limit
   RUN(test_publish_rate_limit_zero);
   RUN(test_publish_rate_limit_one_in_single_batch);
   RUN(test_publish_rate_limit_sliding_window_clears);
   RUN(test_publish_rate_limit_window_boundary_blocks);
   RUN(test_publish_rate_limit_window_boundary_allows);


   // Publish — sort order
   RUN(test_publish_sort_order_interest_then_ts_then_id);


   // Publish — multi-sub
   RUN(test_publish_multi_sub_partial_filter);
   RUN(test_publish_multi_sub_all_delivered);


   // Publish — repeated
   RUN(test_publish_repeated_with_no_new_data);


   std::printf("\n=== %d passed, %d failed ===\n", g_pass, g_fail);
   return g_fail == 0 ? 0 : 1;
}