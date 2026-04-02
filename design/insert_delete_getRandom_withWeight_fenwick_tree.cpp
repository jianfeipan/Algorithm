class RandomizedSet {
public:
    RandomizedSet() : _totalWeight(0) {}

    bool insert(int val, int weight) {
        if (_valToIndex.count(val)) return false;
        if (weight <= 0) return false;

        _valToIndex[val] = _values.size();
        _values.push_back(val);
        _weights.push_back(weight);

        _totalWeight += weight;
        _prefix.push_back(_totalWeight);
        return true;
    }

    bool remove(int val) {
        if (!_valToIndex.count(val)) return false;

        size_t idx = _valToIndex[val];

        _totalWeight -= _weights[idx];

        _values.erase(_values.begin() + idx);
        _weights.erase(_weights.begin() + idx);
        _valToIndex.erase(val);

        for (size_t i = idx; i < _values.size(); ++i) {
            _valToIndex[_values[i]] = i;
        }

        rebuildPrefix();
        return true;
    }

    int getRandom() {
        if (_values.empty()) throw std::runtime_error("empty set");

        long long r = 1 + rand() % _totalWeight;
        auto it = std::lower_bound(_prefix.begin(), _prefix.end(), r);
        return _values[it - _prefix.begin()];
    }

private:
    void rebuildPrefix() {
        _prefix.clear();
        long long sum = 0;
        for (int w : _weights) {
            sum += w;
            _prefix.push_back(sum);
        }
    }

    unordered_map<int, size_t> _valToIndex;
    vector<int> _values;
    vector<int> _weights;
    vector<long long> _prefix;
    long long _totalWeight;
};


// rebuild prefixis O(n) -> are we having more update or more getRandome ?

/*
 * 树状数组（Fenwick Tree / Binary Indexed Tree, BIT）
 *
 * 核心思想：
 *   利用二进制的最低位（lowbit）巧妙地将前缀和拆分为 O(logN) 个子段，
 *   从而实现 O(logN) 的单点更新和前缀和查询。
 *
 * 关键操作：lowbit(i) = i & (-i)
 *   - 取 i 的二进制最低位的值
 *   - 例: i=6 (110) → lowbit=2 (10)，表示 bit[6] 存储了从 index 5 到 6 的和
 *
 * 数组下标从 1 开始（下标 0 不使用），大小为 n+1
 */
class FenwickTree {
public:
    // 构造函数：创建大小为 n 的树状数组，下标 [1, n]，初始值全为 0
    FenwickTree(int n) : bit(n + 1, 0) {}

    // 单点更新：将 index 位置的值增加 delta
    // 从 index 出发，沿着 i += lowbit(i) 的路径向上更新所有包含该点的节点
    // 时间复杂度：O(logN)
    void add(int index, long long delta) {
        for (int i = index; i < (int)bit.size(); i += i & -i) {
            bit[i] += delta;
        }
    }

    // 前缀和查询：返回 [1, index] 的累计和
    // 从 index 出发，沿着 i -= lowbit(i) 的路径向下累加
    // 例: prefixSum(7)  →  bit[7] + bit[6] + bit[4]
    //     7(111) → 6(110) → 4(100) → 0 结束
    // 时间复杂度：O(logN)
    long long prefixSum(int index) const {
        long long sum = 0;
        for (int i = index; i > 0; i -= i & -i) {
            // i & -i 取最低位: 例 0b11010 → lowbit = 0b10
            sum += bit[i];
        }
        return sum;
    }

    // 查询整个数组的总和
    long long totalSum() const {
        return prefixSum((int)bit.size() - 1);
    }

    // 在前缀和上做二分查找（lowerBound）
    // 找到最小的下标 idx，使得 prefixSum(idx) >= target
    // 应用场景：加权随机选择——随机一个 target，找到它落在哪个元素上
    // 时间复杂度：O(logN)（倍增法，比普通二分更高效）
    int lowerBound(long long target) const {
        int idx = 0;
        // 找到不超过 bit.size() 的最大 2 的幂作为起始步长
        int step = 1;
        while ((step << 1) < (int)bit.size()) {
            step <<= 1;
        }

        // 从最大步长开始，逐步减半（类似二进制拆分）
        // 每步尝试向右跳 step，如果跳过去后前缀和仍不够，就跳过去
        for (; step > 0; step >>= 1) {
            int next = idx + step;
            if (next < (int)bit.size() && bit[next] < target) {
                idx = next;
                target -= bit[next]; // 减去已累加的部分
            }
        }

        return idx + 1; // 返回 1-indexed 的下标
    }

private:
/*
 * 树状数组的直觉理解：
 *
 * 原始数组的前缀和树可以看成：
 *                          36
 *             10           26
 *       3     7     11     15
 *    1  2  3  4  5   6   7  8
 *
 * 去掉冗余节点（偶数位可以由上层减去左兄弟得到）：
 *                          36
 *             10           *
 *       3     *     11     *
 *    1  *  3  *  5   *   7  *
 *
 * 这样不需要额外空间，只用一个一维数组即可！
 *
 * 核心技巧：用 lowbit(i) = i & (-i) 控制循环方向
 *   - 更新时：index += lowbit(index)，向右上方传播
 *     例: 更新 index=5 → 影响 bit[5], bit[6], bit[8]（只需 logN 次）
 *   - 查询时：index -= lowbit(index)，向左累加
 *     例: 查询 prefixSum(7) → 累加 bit[7], bit[6], bit[4]
 *
 * 这就是从 O(N) 优化到 O(logN) 的关键！
 */
    vector<long long> bit; // 树状数组，下标从 1 开始
};

/*
 * 加权随机集合（Weighted Randomized Set）
 *
 * 功能：支持插入、删除元素（每个元素有一个权重），以及按权重概率随机选取元素。
 *
 * 核心思路：
 *   - 用数组存储元素和权重，用哈希表维护值到下标的映射
 *   - 用树状数组维护权重的前缀和，实现 O(logN) 的加权随机选取
 *   - 删除时用「与最后一个元素交换」的技巧，保持数组紧凑，避免空洞
 *
 * 操作复杂度：
 *   - insert:    O(logN)
 *   - remove:    O(logN)
 *   - getRandom: O(logN)
 */
class WeightedRandomizedSet {
public:
    // 构造函数：maxSize 为最大元素数量（用于初始化树状数组大小）
    explicit WeightedRandomizedSet(int maxSize)
        : _bit(maxSize), _totalWeight(0) {}

    // 插入元素 val，权重为 weight
    // 如果 val 已存在或 weight <= 0，返回 false
    bool insert(int val, int weight) {
        if (_valToIndex.count(val)) return false;  // 不允许重复插入
        if (weight <= 0) return false;              // 权重必须为正

        int idx = (int)_values.size();  // 新元素放在数组末尾
        _values.push_back(val);
        _weights.push_back(weight);
        _valToIndex[val] = idx;         // 记录值到下标的映射

        _bit.add(idx + 1, weight);      // 在树状数组中更新权重（下标从1开始，所以 idx+1）
        _totalWeight += weight;
        return true;
    }

    // 删除元素 val
    // 使用「交换到末尾再删除」的经典技巧，保持数组连续
    bool remove(int val) {
        if (!_valToIndex.count(val)) return false;  // 元素不存在

        int idx = _valToIndex[val];                 // 要删除的元素的下标
        int lastIdx = (int)_values.size() - 1;      // 数组最后一个元素的下标

        // 第一步：从树状数组中移除被删除元素的权重
        int removedWeight = _weights[idx];
        _bit.add(idx + 1, -removedWeight);          // 减去权重（等价于移除）
        _totalWeight -= removedWeight;

        // 第二步：如果不是最后一个元素，将最后一个元素移到当前位置填补空洞
        if (idx != lastIdx) {
            int lastVal = _values[lastIdx];
            int lastWeight = _weights[lastIdx];

            // 先从树状数组中移除末尾元素的权重
            _bit.add(lastIdx + 1, -lastWeight);

            // 将末尾元素移动到被删除的位置
            _values[idx] = lastVal;
            _weights[idx] = lastWeight;
            _valToIndex[lastVal] = idx;  // 更新末尾元素的下标映射

            // 在新位置重新插入末尾元素的权重
            _bit.add(idx + 1, lastWeight);
        }

        // 第三步：弹出末尾，清理映射
        _values.pop_back();
        _weights.pop_back();
        _valToIndex.erase(val);

        return true;
    }

    // 按权重概率随机选取一个元素
    // 权重越大的元素被选中的概率越高
    // 原理：在 [1, totalWeight] 中随机一个数 target，
    //       用树状数组的 lowerBound 找到 target 落在哪个元素的权重区间内
    int getRandom() const {
        if (_values.empty()) {
            throw std::runtime_error("set is empty");
        }

        long long target = 1 + rand() % _totalWeight;   // 随机一个 [1, totalWeight] 的值
        int fenwickIndex = _bit.lowerBound(target);      // 找到前缀和 >= target 的最小下标
        int idx = fenwickIndex - 1;                      // 转换回 0-indexed
        return _values[idx];
    }

private:
    unordered_map<int, int> _valToIndex;  // 值 → 数组下标 的映射，用于 O(1) 查找
    vector<int> _values;                  // 存储所有元素的值
    vector<int> _weights;                 // 存储每个元素对应的权重
    FenwickTree _bit;                     // 树状数组，维护权重的前缀和
    long long _totalWeight;               // 所有元素权重的总和
};

