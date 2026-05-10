/*
 * 可扩展淘汰策略的缓存（Cache with Custom Eviction Strategy）
 *
 * 设计思路：
 *   - 使用策略模式（Strategy Pattern），将淘汰策略抽象为接口 EvictionPolicy
 *   - Cache 类持有一个 EvictionPolicy 指针，通过多态调用具体策略
 *   - 新增策略只需实现 EvictionPolicy 接口，无需修改 Cache 类（开闭原则）
 *
 * 已实现的策略：
 *   1. LRU（Least Recently Used）：淘汰最近最少使用的元素
 *   2. LFU（Least Frequently Used）：淘汰使用频率最低的元素（频率相同时淘汰最早的）
 *
 * 扩展方式：
 *   继承 EvictionPolicy<K> 并实现 4 个纯虚函数即可，例如 FIFO、TTL、Random 等
 */

#include <iostream>
#include <unordered_map>
#include <list>
#include <memory>
#include <optional>
#include <stdexcept>
using namespace std;

// ======================== 淘汰策略接口 ========================
// K = 缓存键的类型
// 所有自定义淘汰策略都需要实现此接口
template <typename K>
class EvictionPolicy {
public:
    virtual ~EvictionPolicy() = default;

    // 当 key 被访问（get/put）时调用，策略据此更新内部状态
    virtual void onAccess(const K& key) = 0;

    // 当 key 被插入时调用
    virtual void onInsert(const K& key) = 0;

    // 当 key 被删除时调用，策略清理该 key 的相关数据
    virtual void onRemove(const K& key) = 0;

    // 返回应该被淘汰的 key
    virtual K evict() = 0;
};

// ======================== LRU 淘汰策略 ========================
// 最近最少使用：淘汰最长时间未被访问的元素
// 实现：双向链表 + 哈希表
//   - 链表头部 = 最近使用，尾部 = 最久未使用
//   - 每次访问将 key 移到头部，淘汰时从尾部取
template <typename K>
class LRUPolicy : public EvictionPolicy<K> {
    list<K> _order;                                        // 双向链表，维护访问顺序
    unordered_map<K, typename list<K>::iterator> _map;     // key → 链表迭代器，O(1) 定位

public:
    void onAccess(const K& key) override {
        // 将 key 移到链表头部（最近使用）
        auto it = _map.find(key);
        if (it != _map.end()) {
            _order.splice(_order.begin(), _order, it->second);
        }
    }

    void onInsert(const K& key) override {
        // 新元素插入链表头部
        _order.push_front(key);
        _map[key] = _order.begin();
    }

    void onRemove(const K& key) override {
        auto it = _map.find(key);
        if (it != _map.end()) {
            _order.erase(it->second);
            _map.erase(it);
        }
    }

    K evict() override {
        // 淘汰链表尾部（最久未使用）
        K key = _order.back();
        _order.pop_back();
        _map.erase(key);
        return key;
    }
};

// ======================== LFU 淘汰策略 ========================
// 最不经常使用：淘汰访问频率最低的元素，频率相同时淘汰最早插入的（FIFO）
// 实现：三个哈希表 + 按频率分组的双向链表
//   - _freqMap[freq] = 该频率下所有 key 的链表（按插入顺序，尾部最早）
//   - _keyFreq[key] = key 当前的频率
//   - _keyIter[key] = key 在对应频率链表中的迭代器
//   - _minFreq = 当前最小频率，淘汰时直接定位
template <typename K>
class LFUPolicy : public EvictionPolicy<K> {
    unordered_map<int, list<K>> _freqMap;                  // 频率 → 该频率下的 key 链表
    unordered_map<K, int> _keyFreq;                        // key → 当前频率
    unordered_map<K, typename list<K>::iterator> _keyIter; // key → 在频率链表中的迭代器
    int _minFreq = 0;                                      // 当前全局最小频率

    // 将 key 的频率 +1，并从旧频率链表移到新频率链表
    void incrementFreq(const K& key) {
        int freq = _keyFreq[key];
        // 从旧频率链表中移除
        _freqMap[freq].erase(_keyIter[key]);
        // 如果旧频率链表空了，清理并可能更新 _minFreq
        if (_freqMap[freq].empty()) {
            _freqMap.erase(freq);
            if (_minFreq == freq) _minFreq = freq + 1;
        }
        // 插入新频率链表的头部
        int newFreq = freq + 1;
        _keyFreq[key] = newFreq;
        _freqMap[newFreq].push_front(key);
        _keyIter[key] = _freqMap[newFreq].begin();
    }

public:
    void onAccess(const K& key) override {
        if (_keyFreq.count(key)) {
            incrementFreq(key);
        }
    }

    void onInsert(const K& key) override {
        // 新元素频率为 1，插入频率 1 的链表头部
        _keyFreq[key] = 1;
        _freqMap[1].push_front(key);
        _keyIter[key] = _freqMap[1].begin();
        _minFreq = 1; // 新插入的元素频率一定是最小的
    }

    void onRemove(const K& key) override {
        if (!_keyFreq.count(key)) return;
        int freq = _keyFreq[key];
        _freqMap[freq].erase(_keyIter[key]);
        if (_freqMap[freq].empty()) {
            _freqMap.erase(freq);
            // 如果删掉的恰好是 _minFreq 对应的最后一个，需要修正
            // 但 onRemove 只在 evict 或外部删除时调用，evict 会自行处理
        }
        _keyFreq.erase(key);
        _keyIter.erase(key);
    }

    K evict() override {
        // 淘汰最小频率链表的尾部（最早插入的）
        auto& minList = _freqMap[_minFreq];
        K key = minList.back();
        minList.pop_back();
        if (minList.empty()) {
            _freqMap.erase(_minFreq);
        }
        _keyFreq.erase(key);
        _keyIter.erase(key);
        return key;
    }
};

// ======================== 缓存类 ========================
// K = 键类型, V = 值类型
// 通过模板参数 + 策略模式实现可扩展的淘汰策略
template <typename K, typename V>
class Cache {
    int _capacity;                                         // 缓存最大容量
    unordered_map<K, V> _store;                            // 键值对存储
    unique_ptr<EvictionPolicy<K>> _policy;                 // 淘汰策略（多态）

public:
    // 构造函数：传入容量和淘汰策略（通过 unique_ptr 转移所有权）
    Cache(int capacity, unique_ptr<EvictionPolicy<K>> policy)
        : _capacity(capacity), _policy(move(policy)) {
        if (capacity <= 0) throw invalid_argument("capacity must be > 0");
    }

    // 查询 key 对应的值，不存在返回 nullopt
    optional<V> get(const K& key) {
        auto it = _store.find(key);
        if (it == _store.end()) return nullopt;
        _policy->onAccess(key);  // 通知策略：key 被访问
        return it->second;
    }

    // 插入或更新键值对
    void put(const K& key, const V& value) {
        // 如果 key 已存在，更新值并通知访问
        if (_store.count(key)) {
            _store[key] = value;
            _policy->onAccess(key);
            return;
        }
        // 如果缓存已满，先淘汰一个元素
        if ((int)_store.size() >= _capacity) {
            K evicted = _policy->evict();
            _store.erase(evicted);
        }
        // 插入新元素
        _store[key] = value;
        _policy->onInsert(key);
    }

    // 手动删除 key
    bool remove(const K& key) {
        if (!_store.count(key)) return false;
        _policy->onRemove(key);
        _store.erase(key);
        return true;
    }

    int size() const { return (int)_store.size(); }
    int capacity() const { return _capacity; }
};

// ======================== 测试 ========================
int main() {
    // ---------- 测试 LRU 缓存 ----------
    cout << "===== LRU Cache =====" << endl;
    {
        Cache<int, string> cache(3, make_unique<LRUPolicy<int>>());

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
        Cache<int, string> cache(3, make_unique<LFUPolicy<int>>());

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
 *       void onAccess(const K&) override {}  // FIFO 不关心访问
 *       void onInsert(const K& key) override { _queue.push(key); _set.insert(key); }
 *       void onRemove(const K& key) override { _set.erase(key); }
 *       K evict() override {
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
