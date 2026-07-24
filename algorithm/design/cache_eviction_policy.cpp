#include <iostream>
#include <unordered_map>
#include <list>
#include <memory>
#include <optional>
#include <stdexcept>
using namespace std;

template <typename K, typename Derived>
class EvictionPolicy {
public:
    // CRTP 不需要虚析构函数，因为我们不通过基类指针 delete 子类对象
    // 这里的接口不再是 virtual，而是普通的成员函数
    void onAccess(const K& key) {
        impl().onAccessImpl(key);
    }

    void onInsert(const K& key) {
        impl().onInsertImpl(key);
    }

    void onRemove(const K& key) {
        impl().onRemoveImpl(key);
    }

    K evict() {
        return impl().evictImpl();
    }

private:
    Derived& impl() {
        return static_cast<Derived&>(*this);
    }
};

// ======================== LRU 淘汰策略 ========================
// 最近最少使用：淘汰最长时间未被访问的元素
// 实现：双向链表 + 哈希表
//   - 链表头部 = 最近使用，尾部 = 最久未使用
//   - 每次访问将 key 移到头部，淘汰时从尾部取
template <typename K>
class LRUPolicy : public EvictionPolicy<K, LRUPolicy<K>> {
    list<K> most_recent_;                                        // 双向链表，维护访问顺序
    unordered_map<K, typename list<K>::iterator> pos_;     // key → 链表迭代器，O(1) 定位

public:
    void onAccess(const K& key) {
        // 将 key 移到链表头部（最近使用）
        auto it = pos_.find(key);
        if (it != pos_.end()) {
            most_recent_.splice(most_recent_.begin(), most_recent_, it->second);
            // no need to update pos_: the splice touches the pointers to next andprev, the iterator itself wasn't touched.
        }
    }

    void onInsert(const K& key) {
        // 新元素插入链表头部
        most_recent_.push_front(key);
        pos_[key] = most_recent_.begin();
    }

    void onRemove(const K& key) {
        auto it = pos_.find(key);
        if (it != pos_.end()) {
            most_recent_.erase(it->second);
            pos_.erase(it);
        }
    }

    K evict() {
        // 淘汰链表尾部（最久未使用）
        K key = most_recent_.back();
        most_recent_.pop_back();
        pos_.erase(key);
        return key;
    }
};

// ======================== LFU 淘汰策略 ========================
// 最不经常使用：淘汰访问频率最低的元素，频率相同时淘汰最早插入的（FIFO）
// 实现：三个哈希表 + 按频率分组的双向链表
//   - by_freq_[freq] = 该频率下所有 key 的链表（按插入顺序，尾部最早）
//   - freq_[key] = key 当前的频率
//   - pos_[key] = key 在对应频率链表中的迭代器
//   - min_freq_ = 当前最小频率，淘汰时直接定位
template <typename K>
class LFUPolicy : public EvictionPolicy<K, LFUPolicy<K>> {
    unordered_map<size_t, list<K>> by_freq_;                  // 频率 → 该频率下的 key 链表
    unordered_map<K, size_t> freq_;                        // key → 当前频率
    unordered_map<K, typename list<K>::iterator> pos_; // key → 在频率链表中的迭代器
    size_t min_freq_ = 0;                                      // 当前全局最小频率

public:
    void onAccess(const K& key) {
        // assert(freq_.count(key));

        const auto freq = freq_[key];
        // 从旧频率链表中移除
        by_freq_[freq].erase(pos_[key]);
        // 如果旧频率链表空了，清理并可能更新 min_freq_
        if (by_freq_[freq].empty()) {
            by_freq_.erase(freq);
            if (min_freq_ == freq) min_freq_ = freq + 1;// it's obvious freq + 1 is there, the current one!
        }
        // 插入新频率链表的头部
        const auto newFreq = freq + 1;
        freq_[key] = newFreq;
        by_freq_[newFreq].push_front(key);
        pos_[key] = by_freq_[newFreq].begin();
    }

    void onInsert(const K& key) {
        // 新元素频率为 1，插入频率 1 的链表头部
        freq_[key] = 1;
        by_freq_[1].push_front(key);
        pos_[key] = by_freq_[1].begin();
        min_freq_ = 1; // 新插入的元素频率一定是最小的
    }

    void onRemove(const K& key) {
        if (freq_.find(key) == freq_.end()) return;

        const auto f = freq_[key];
        by_freq_[f].erase(pos_[key]);
        
        if (by_freq_[f].empty()) {
            by_freq_.erase(f);
            // Only update min_freq_ if we have other elements left
            // assert(!freq_.empty(), "no element failes the evition.");
            if (min_freq_ == f && !freq_.empty()) {
                // This is only needed if you manually remove items
                // Usually not hit during standard eviction
                while (!by_freq_.count(min_freq_) && min_freq_ < 1000000) { // Safety cap
                    min_freq_++;
                }
            }
        }
        
        freq_.erase(key);
        pos_.erase(key);
        if (freq_.empty()) min_freq_ = 0;
    }

    K evict() {
        // 淘汰最小频率链表的尾部（最早插入的）
        auto& minList = by_freq_[min_freq_];
        K key = minList.back();
        minList.pop_back();
        if (minList.empty()) {
            by_freq_.erase(min_freq_);
            while(!by_freq_.count(min_freq_)) ++min_freq_; // ???risk
        }
        freq_.erase(key);
        pos_.erase(key);
        return key;
    }
};

// ======================== 缓存类 ========================
// K = 键类型, V = 值类型
// 通过模板参数 + 策略模式实现可扩展的淘汰策略
template <typename K, typename V, class Policy>
class Cache {
    size_t _capacity;                                         // 缓存最大容量
    unordered_map<K, V> _store;                            // 键值对存储
    Policy _policy;                            // 淘汰策略（多态）

public:
    // 构造函数：传入容量和淘汰策略（通过 unique_ptr 转移所有权）
    Cache(size_t capacity)
        : _capacity(capacity), _policy() {
    }

    // 查询 key 对应的值，不存在返回 nullopt
    optional<V> get(const K& key) {
        auto it = _store.find(key);
        if (it == _store.end()) return nullopt;

        _policy.onAccess(key);  // 通知策略：key 被访问
        return it->second;
    }

    // 插入或更新键值对
    void put(const K& key, const V& value) {
        
        auto [_, inserted] = _store.try_emplace(key, value);
        if (inserted) {
            _policy.onInsert(key);
        }else {
            _policy.onAccess(key);
        }

        // 如果缓存已满，先淘汰一个元素
        if (_store.size() > _capacity) {
            K evicted = _policy.evict();
            _store.erase(evicted);
        }
    }

    // 手动删除 key
    bool remove(const K& key) {
        if (!_store.count(key)) return false;
        _policy.onRemove(key);
        _store.erase(key);
        return true;
    }

    size_t size() const { return _store.size(); }
    int capacity() const { return _capacity; }
};

// ======================== 测试 ========================
int main() {
    // ---------- 测试 LRU 缓存 ----------
    cout << "===== LRU Cache =====" << endl;
    {
        Cache<int, string, LRUPolicy<int>> cache(3);

        cache.put(1, "one");
        cache.put(2, "two");
        cache.put(3, "three");
        cout << "get(1) = " << cache.get(1).value_or("miss") << endl;  // "one"，此时 1 变为最近使用

        cache.put(4, "four");  // 缓存满，淘汰最久未使用的 key=2
        cout << "get(2) = " << cache.get(2).value_or("miss") << endl;  // "miss"，2 已被淘汰
        cout << "get(3) = " << cache.get(3).value_or("miss") << endl;  // "three"
        cout << "get(4) = " << cache.get(4).value_or("miss") << endl;  // "four"
    }

    cout << endl;

    // ---------- 测试 LFU 缓存 ----------
    cout << "===== LFU Cache =====" << endl;
    {
        Cache<int, string, LFUPolicy<int>> cache(3);

        cache.put(1, "one");
        cache.put(2, "two");
        cache.put(3, "three");
        cache.get(1);  // freq: 1→2
        cache.get(1);  // freq: 1→3
        cache.get(2);  // freq: 2→2

        cache.put(4, "four");  // 缓存满，淘汰频率最低的 key=3（freq=1）
        cout << "get(3) = " << cache.get(3).value_or("miss") << endl;  // "miss"，3 被淘汰
        cout << "get(1) = " << cache.get(1).value_or("miss") << endl;  // "one"
        cout << "get(2) = " << cache.get(2).value_or("miss") << endl;  // "two"
        cout << "get(4) = " << cache.get(4).value_or("miss") << endl;  // "four"
    }

    return 0;
}

/*
 * 类图结构：
 *
 *   EvictionPolicy<K>          （抽象接口）
 *     ├── LRUPolicy<K>         （LRU 实现：双向链表 + 哈希表）
 *     ├── LFUPolicy<K>         （LFU 实现：频率分组链表）
 *     └── ... 可自由扩展 ...    （FIFO, LRU-K, TTL, Random 等）
 *
 *   Cache<K, V>
 *     - 持有 unique_ptr<EvictionPolicy<K>>
 *     - 通过多态调用淘汰策略，Cache 本身无需改动
 *
 * 扩展示例（添加 FIFO 策略）：
 *
 *   template <typename K>
 *   class FIFOPolicy : public EvictionPolicy<K> {
 *       queue<K> _queue;
 *       unordered_set<K> _set;
 *   public:
 *       void onAccess(const K&) {}  // FIFO 不关心访问
 *       void onInsert(const K& key) { _queue.push(key); _set.insert(key); }
 *       void onRemove(const K& key) { _set.erase(key); }
 *       K evict() {
 *           while (!_set.count(_queue.front())) _queue.pop(); // 跳过已删除的
 *           K key = _queue.front(); _queue.pop(); _set.erase(key);
 *           return key;
 *       }
 *   };
 *
 * 复杂度：
 *   LRU:  get/put/remove 均为 O(1)
 *   LFU:  get/put/remove 均为 O(1)
 */
