/*
 * 线段树（Segment Tree）+ 懒标记（Lazy Propagation）
 *
 * 本实现用于解决 LeetCode 1851. 包含每个查询的最小区间
 *
 * 核心思路：
 *   1. 将所有区间端点和查询点进行坐标压缩，映射到连续的小下标
 *   2. 用线段树维护每个压缩后的点被覆盖的最小区间长度
 *   3. 对每个区间 [l, r]，在线段树上对 [compress(l), compress(r)] 区间更新，值为区间长度
 *   4. 对每个查询点，单点查询该点被覆盖的最小区间长度
 *
 * 线段树结构说明：
 *   - 使用数组存储完全二叉树，节点 i 的左子节点为 2*i+1，右子节点为 2*i+2
 *   - tree[i] 存储该节点对应区间的最小值
 *   - lazy[i] 存储待下推的懒标记（延迟更新的值）
 */
class SegmentTree {
public:
    int n;              // 原始数组的大小（即压缩后的坐标数量）
    vector<int> tree;   // 线段树数组，存储每个节点对应区间的最小值
    vector<int> lazy;   // 懒标记数组，延迟下推更新，避免每次更新都递归到叶子节点

    // 构造函数：初始化大小为 N 的线段树
    SegmentTree(int N) {
        this->n = N;
        tree.assign(4 * N, INT_MAX);
        /* 为什么要 4*N：
           线段树是一棵完全二叉树，对于 N 个叶子节点，
           最坏情况下需要约 2*2N = 4N 个节点来存储整棵树。
           （当 N 不是 2 的幂时，最后一层可能不满，但预分配 4N 保证足够）
        */
        lazy.assign(4 * N, INT_MAX); // INT_MAX 表示"无更新"，即没有待下推的值
    }

    // 懒标记下推：将当前节点的懒标记传递给左右子节点
    // treeidx: 当前节点在数组中的下标
    // lo, hi: 当前节点代表的区间 [lo, hi]
    void propagate(int treeidx, int lo, int hi) {
        if (lazy[treeidx] != INT_MAX) {
            // 用懒标记更新当前节点的值（取最小值）
            tree[treeidx] = min(tree[treeidx], lazy[treeidx]);
            if (lo != hi) {
                // 不是叶子节点，将懒标记下推给左右子节点
                lazy[2 * treeidx + 1] = min(lazy[2 * treeidx + 1], lazy[treeidx]);
                lazy[2 * treeidx + 2] = min(lazy[2 * treeidx + 2], lazy[treeidx]);
            }
            // 清除当前节点的懒标记
            lazy[treeidx] = INT_MAX;
        }
    }

    // 区间更新：在 [left, right] 范围内更新最小值为 val
    // treeidx: 当前节点下标
    // lo, hi: 当前节点代表的区间
    // left, right: 需要更新的目标区间
    // val: 要更新的值
    void update(int treeidx, int lo, int hi, int left, int right, int val) {
        // 先下推懒标记，确保当前节点的值是最新的
        propagate(treeidx, lo, hi);

        // 当前区间与目标区间完全不相交，直接返回
        if (lo > right || hi < left) return;

        // 当前区间完全被目标区间包含，打上懒标记并下推
        if (lo >= left && hi <= right) {
            lazy[treeidx] = min(lazy[treeidx], val);
            propagate(treeidx, lo, hi);
            return;
        }

        // 当前区间与目标区间部分重叠，递归更新左右子树
        int mid = (lo + hi) / 2;
        update(2 * treeidx + 1, lo, mid, left, right, val);
        update(2 * treeidx + 2, mid + 1, hi, left, right, val);

        // 回溯时更新当前节点的值为左右子节点的最小值
        tree[treeidx] = min(tree[2 * treeidx + 1], tree[2 * treeidx + 2]);
    }

    // 单点查询：查询下标 idx 处的最小值
    // treeidx: 当前节点下标
    // lo, hi: 当前节点代表的区间
    // idx: 要查询的目标下标
    int query(int treeidx, int lo, int hi, int idx) {
        // 先下推懒标记
        propagate(treeidx, lo, hi);
        // 到达叶子节点，返回值
        if (lo == hi) return tree[treeidx];

        // 根据 idx 的位置决定递归查询左子树还是右子树
        int mid = (lo + hi) / 2;
        if (idx <= mid) return query(2 * treeidx + 1, lo, mid, idx);
        else return query(2 * treeidx + 2, mid + 1, hi, idx);
    }

    // 对外暴露的区间更新接口（隐藏内部递归细节）
    void update(int left, int right, int val) {
        update(0, 0, n - 1, left, right, val);
    }

    // 对外暴露的单点查询接口
    int query(int idx) {
        return query(0, 0, n - 1, idx);
    }
};

/*
 * LeetCode 1851. 包含每个查询的最小区间
 *
 * 题意：给定若干区间 intervals 和若干查询点 queries，
 *       对每个查询点，找出包含该点的最小区间的长度。
 *       如果没有区间包含该点，返回 -1。
 *
 * 解法：坐标压缩 + 线段树
 *   1. 收集所有区间端点和查询点，去重排序后进行坐标压缩
 *   2. 对每个区间，在线段树的对应压缩区间上更新区间长度（取最小值）
 *   3. 对每个查询点，在线段树上单点查询最小区间长度
 */
class Solution {
public:
    vector<int> minInterval(vector<vector<int>>& intervals, vector<int>& queries) {
        // 第一步：收集所有需要用到的坐标点（区间端点 + 查询点）
        vector<int> points;

        for (const auto& interval : intervals) {
            points.push_back(interval[0]); // 区间左端点
            points.push_back(interval[1]); // 区间右端点
        }
        for (int q : queries) {
            points.push_back(q);           // 查询点
        }

        // 排序并去重，为坐标压缩做准备
        sort(points.begin(), points.end());
        points.erase(unique(points.begin(), points.end()), points.end());

        // 第二步：坐标压缩——将原始坐标映射为连续的小下标（0, 1, 2, ...）
        // 这样线段树的大小只取决于不同坐标的数量，而不是坐标值的范围
        unordered_map<int, int> compress;
        for (int i = 0; i < points.size(); ++i) {
            compress[points[i]] = i;
        }

        // 第三步：创建线段树，大小为压缩后的坐标数量
        SegmentTree segTree(points.size());

        // 第四步：对每个区间，在线段树上进行区间更新
        // 将区间长度作为值更新到对应的压缩区间上（取最小值）
        for (const auto& interval : intervals) {
            int start = compress[interval[0]]; // 压缩后的左端点下标
            int end = compress[interval[1]];   // 压缩后的右端点下标
            int len = interval[1] - interval[0] + 1; // 区间长度
            segTree.update(start, end, len);
        }

        // 第五步：对每个查询点，单点查询最小区间长度
        vector<int> ans;
        for (int q : queries) {
            int idx = compress[q];
            int res = segTree.query(idx);
            // 如果结果仍为 INT_MAX，说明没有区间包含该查询点，返回 -1
            ans.push_back(res == INT_MAX ? -1 : res);
        }

        return ans;
    }
};
