#include <unordered_map>
#include <list>
#include <optional>
#include <utility>

template<typename K, typename V>
class lru_cache {
    using ListType = std::list<std::pair<K, V>>;
    using It = typename ListType::iterator;

    std::unordered_map<K, It> store_;
    ListType most_recent_;
    size_t capacity_;

public:
    explicit lru_cache(size_t capacity) : capacity_(capacity) {}

    void set(const K& key, const V& value) {
        if (capacity_ == 0) return;

        auto [it, inserted] = store_.try_emplace(key, It{});
        if (inserted) {
            most_recent_.emplace_front(key, value);
            it->second = most_recent_.begin();
        } else {
            auto list_it = it->second;
            list_it->second = value; // Update value
            most_recent_.splice(most_recent_.begin(), most_recent_, list_it);
        }

        if (store_.size() > capacity_) { // Evict LRU item
            const auto& key_to_evict = most_recent_.back().first;
            store_.erase(key_to_evict);
            most_recent_.pop_back();
        }
    }

    std::optional<V> get(const K& key) {
        auto it = store_.find(key);
        if (it != store_.end()) {
            auto list_it = it->second;
            most_recent_.splice(most_recent_.begin(), most_recent_, list_it);
            return list_it->second;
        }
        return std::nullopt;
    }
};