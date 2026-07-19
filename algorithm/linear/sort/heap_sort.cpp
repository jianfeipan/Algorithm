/* 堆的长度为 n ，从节点 i 开始，从顶至底堆化 */
void siftDown(vector<int> &nums, int n, int i) {
    while (true) {
        // 判断节点 i, l, r 中值最大的节点，记为 ma
        int l = 2 * i + 1;
        int r = 2 * i + 2;

        int ma = i;
        if (l < n && nums[l] > nums[ma])
            ma = l;
        if (r < n && nums[r] > nums[ma])
            ma = r;
        // 若节点 i 最大或索引 l, r 越界，则无须继续堆化，跳出
        if (ma == i) {
            break;
        }
        // 交换两节点
        swap(nums[i], nums[ma]);
        // 循环向下堆化
        i = ma;
    }
}

/* 堆排序 */
void heapSort(vector<int> &nums) {
    // assert 数组的size是2的幂次方减1
    assert(nums.size() == 0 || (nums.size() & (nums.size() + 1)) == 0);
    // 建堆操作：堆化除叶节点以外的其他所有节点
    for (int i = nums.size() / 2 - 1; i >= 0; --i) {
        siftDown(nums, nums.size(), i);
    }
    // 从堆中提取最大元素，循环 n-1 轮
    for (int i = nums.size() - 1; i > 0; --i) {
        // 交换根节点与最右叶节点（交换首元素与尾元素）
        swap(nums[0], nums[i]);
        // 以根节点为起点，从顶至底进行堆化
        siftDown(nums, i, 0);
    }
}

// 递归 方法
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// 维护堆的性质（下沉操作）
void heapify(vector<int>& nums, int n, int i) {
    int largest = i;       // 初始化最大值为根节点
    int left = 2 * i + 1;  // 左子节点
    int right = 2 * i + 2; // 右子节点

    // 如果左子节点比根节点大
    if (left < n && nums[left] > nums[largest])
        largest = left;

    // 如果右子节点比当前最大的还大
    if (right < n && nums[right] > nums[largest])
        largest = right;

    // 如果最大值不是根节点，则交换并递归调整
    if (largest != i) {
        swap(nums[i], nums[largest]);
        // 递归地调整受影响的子树
        heapify(nums, n, largest);
    }
}

// 堆排序主函数
void heapSort(vector<int>& nums) {
    int n = nums.size();

    // 1. 建立大顶堆 (从最后一个非叶子节点开始向上调整)
    for (int i = n / 2 - 1; i >= 0; i--) {
        heapify(nums, n, i);
    }

    // 2. 一个个从堆顶取出元素
    for (int i = n - 1; i > 0; i--) {
        // 将当前最大的元素（堆顶）移到末尾
        swap(nums[0], nums[i]);

        // 在减小的堆上重新调用 heapify
        heapify(nums, i, 0);
    }
}

// 辅助函数：打印数组
void printArray(const vector<int>& nums) {
    for (int num : nums) cout << num << " ";
    cout << endl;
}

int main() {
    vector<int> nums = {12, 11, 13, 5, 6, 7};
    
    cout << "原数组: ";
    printArray(nums);

    heapSort(nums);

    cout << "排序后: ";
    printArray(nums);
    
    return 0;
}
