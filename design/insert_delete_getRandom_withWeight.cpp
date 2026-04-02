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

// more update: using a Fenwick tree
class FenwickTree {
public:
    FenwickTree(int n) : bit(n + 1, 0) {}

    void add(int index, long long delta) {
        for (int i = index; i < (int)bit.size(); i += i & -i) {
            bit[i] += delta;
        }
    }

    long long prefixSum(int index) const {
        long long sum = 0;
        for (int i = index; i > 0; i -= i & -i) {
          // i & -i lowest bit: 0x11010 -> i&-1 = 0x10
            sum += bit[i];
        }
        return sum;
    }

    long long totalSum() const {
        return prefixSum((int)bit.size() - 1);
    }

    int lowerBound(long long target) const {
        int idx = 0;
        int step = 1;
        while ((step << 1) < (int)bit.size()) {
            step <<= 1;
        }

        for (; step > 0; step >>= 1) {
            int next = idx + step;
            if (next < (int)bit.size() && bit[next] < target) {
                idx = next;
                target -= bit[next];
            }
        }

        return idx + 1;
    }

private:
/*
                          36
             10           26 
       3     7     11     15
    1  2  3  4  5   6   7  8

    remove redendant : the even bit can be computed from layer about - bit[i-1]

                          36
             10           * 
       3     *     11     *
    1  *  3  *  5   *   7  *

    so no extra space used!!

    the magic is loop with index+= (or -=) lowestBit( i&-i)
    garentee you to loop the prefix_sum you need to accumulate 
    ex: if you add a number to index 5, 
          from index 5 to right: 5 6,8 (logN)  only update thses 3 instead of all [5, 8]
          this is the key from O(N) to O(LogN)



*/
    vector<long long> bit;
};

class WeightedRandomizedSet {
public:
    explicit WeightedRandomizedSet(int maxSize)
        : _bit(maxSize), _totalWeight(0) {}

    bool insert(int val, int weight) {
        if (_valToIndex.count(val)) return false;
        if (weight <= 0) return false;

        int idx = (int)_values.size();
        _values.push_back(val);
        _weights.push_back(weight);
        _valToIndex[val] = idx;

        _bit.add(idx + 1, weight);
        _totalWeight += weight;
        return true;
    }

    bool remove(int val) {
        if (!_valToIndex.count(val)) return false;

        int idx = _valToIndex[val];
        int lastIdx = (int)_values.size() - 1;

        int removedWeight = _weights[idx];
        _bit.add(idx + 1, -removedWeight);
        _totalWeight -= removedWeight;

        if (idx != lastIdx) {
            int lastVal = _values[lastIdx];
            int lastWeight = _weights[lastIdx];

            _bit.add(lastIdx + 1, -lastWeight);

            _values[idx] = lastVal;
            _weights[idx] = lastWeight;
            _valToIndex[lastVal] = idx;

            _bit.add(idx + 1, lastWeight);
        }

        _values.pop_back();
        _weights.pop_back();
        _valToIndex.erase(val);

        return true;
    }

    int getRandom() const {
        if (_values.empty()) {
            throw std::runtime_error("set is empty");
        }

        long long target = 1 + rand() % _totalWeight;
        int fenwickIndex = _bit.lowerBound(target);
        int idx = fenwickIndex - 1;
        return _values[idx];
    }

private:
    unordered_map<int, int> _valToIndex;
    vector<int> _values;
    vector<int> _weights;
    FenwickTree _bit;
    long long _totalWeight;
};
