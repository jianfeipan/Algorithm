#include <vector>
#include <climits>
#include <iostream>
#include <algorithm>
using namespace std;
/*
loop sort: O(n^2)
    select
    insert
    bubble

divide and conquer sort: O(nlogn)
    merge sort
    quick sort
    heap sort

linear time sort: O(n)
    counting sort
    bucket sort
    radix sort
*/

/* loop sort: O(n^2) */

class select_sort{
public:
    template<typename T>
    static void sort(vector<T>& nums){
        const auto n = nums.size();
        for(size_t i = 0; i < n; ++i){
            size_t min_i = i;
            for(size_t j = i + 1; j < n; ++j) if(nums[j] < nums[min_i]) min_i = j;
            
            swap(nums[i], nums[min_i]);
        }
    }
};

class insert_sort{
public:
    template<typename T>
    static void sort(vector<T>& nums){
        const auto n = nums.size();
        for(size_t i = 1; i < n; ++i){
            const auto cur = nums[i];
            int left = i - 1;

            while(left >= 0 && nums[left] > cur){
                // move to right
                nums[left + 1] = nums[left];
                --left;
            }
            nums[left + 1] = cur;
        }
    }
};

class bubble_sort{
public:
    template<typename T>
    static void sort(vector<T>& nums){
        const auto n = nums.size();
        for(size_t sorted = n-1; sorted > 0; --sorted){// sorted place has the largest from 0-sorted
            for(size_t j = 0; j < sorted; ++j){// from 0 to sroted-1, fload up the bubble
                if(nums[j] > nums[j+1]) swap(nums[j], nums[j+1]);
            }
        }
    }
};

// devide and conquer: O(nlogn)
class merge_sort{
private:
    template<typename T>
    static void _sort(vector<T>& nums, int l, int r){
        if(l >= r) return;
        auto m = l + (r - l) / 2;
        _sort<T>(nums, l, m);
        _sort<T>(nums, m + 1, r);

        // merge
        vector<T> merged(r - l + 1);
        {
            int i = l;     // [l, ...,m]
            int j = m + 1; // [m+1,..,r]
            int k = 0;
            while(i <= m && j <= r){
                if(nums[i] < nums[j]){ merged[k] = nums[i]; ++i; ++k; } 
                else                 { merged[k] = nums[j]; ++j; ++k; }
            }
            while(i <= m){ merged[k] = nums[i]; ++i; ++k; }
            while(j <= r){ merged[k] = nums[j]; ++j; ++k; }
        }

        copy(merged.begin(), merged.end(), nums.begin() + l);// copy back to nums
    }

public:
    template<typename T>
    static void sort(vector<T>& nums){ _sort<T>(nums, 0, nums.size() - 1); }
};

class quick_sort{
private:
    template<typename T>
    static int _partition(vector<T>& nums, int left, int right){
        const auto pivot = nums[left];

        auto i = left + 1;
        auto j = right;
        while(i < j){
            while(i < j && nums[j] >= pivot) --j; // from right skip the larger
            while(i < j && nums[i] <= pivot) ++i; // from left skip the smaller
            if(i < j) swap(nums[i], nums[j]);
        }
        swap(nums[left], nums[i]);// i now is moved the last smaller than pivot
        return i;
    }

    template<typename T>
    static void _quick_sort(vector<T>& nums, int left, int right){
        if(left >= right) return;
        int p = _partition<T>(nums, left, right);

        _quick_sort<T>(nums, left, p - 1);
        _quick_sort<T>(nums, p + 1, right);
    }
public:
    template<typename T>
    static void sort(vector<T>& nums){ _quick_sort<T>(nums, 0, static_cast<int>(nums.size()) - 1); }
};

class heap_sort{
private:
    template<typename T>
    static void heapify(vector<T>& nums, int n, int root){
        int l = root * 2 + 1;
        int r = root * 2 + 2;

        int largest = root;
        if (l < n && nums[l] > nums[largest]) largest = l;
        if (r < n && nums[r] > nums[largest]) largest = r;

        if (largest != root) {
            swap(nums[largest], nums[root]);
            heapify<T>(nums, n, largest);
        }
    }

public:
    template<typename T>
    static void sort(vector<T>& nums) {
        int n = static_cast<int>(nums.size());
        if (n < 2) return;

        for (int i = n / 2 - 1; i >= 0; --i) heapify<T>(nums, n, i); // nlogn

        for (int i = n - 1; i > 0; --i) {
            swap(nums[0], nums[i]); // put the largest element at the end: i=n-1 is sorted
            heapify<T>(nums, i, 0); // logn
        }
    }
};

// linear time sort: O(n)
class count_sort{
public:
    static void sort(vector<int>& nums){
        vector<int> count(100);
        for(auto num : nums) ++count[num];

        int j = 0;
        for(int num=0; num<count.size(); ++num){
            for(int k=0; k<count[num]; ++k){
                nums[j] = num;
                ++j;
            }
        }
    }
};

class bucket_sort{
public:
    // nums in [0, 1)
    static void sort(vector<double>& nums){
        constexpr size_t bucket_size = 10;
        vector<vector<double>> buckets(bucket_size);
        for(auto num : nums){
            const int bucket_index = num*bucket_size;
            buckets[bucket_index].push_back(num);
        }

        for(auto& bucket : buckets) std::sort(bucket.begin(), bucket.end());
        
        int i = 0;
        for(const auto& bucket : buckets){
            for(const auto& num : bucket){
                nums[i] = num;
                ++i;
            }
        }
    } 
};

class radix_sort{
private:
    static void _count_sort_digit(vector<int>& nums, int exp){
        const auto n = nums.size();
        
        vector<vector<int>> digit_to_index(10);
        auto digit = [exp](int num){ return (num/exp) % 10; };
        for(int i=0; i<n; ++i) digit_to_index[ digit(nums[i]) ].push_back(i);

        vector<int> sorted(n);
        int i=0;
        for(const auto index_inorder : digit_to_index){
            for(auto index : index_inorder){
                sorted[i] = nums[index];
                ++i;
            }
        }
        swap(nums, sorted);
    }    
public:
    static void sort(vector<int>& nums){
        int m = *max_element(nums.begin(), nums.end());
        // 按照从低位到高位的顺序遍历: 在连续的排序轮次中，后一轮排序会覆盖前一轮排序的结果。举例来说，如果第一轮排序结果 ，而第二轮排序结果 ，那么第二轮的结果将取代第一轮的结果。由于数字的高位优先级高于低位，因此应该先排序低位再排序高位。
        for (int exp = 1; exp <= m; exp *= 10)
            // 对数组元素的第 k 位执行计数排序
            // k = 1 -> exp = 1
            // k = 2 -> exp = 10
            // 即 exp = 10^(k-1)
            // use exp instead o k: avoid duplicating calculation of exp
            _count_sort_digit(nums, exp);
        }
};

// test:

template<typename T>
void printArray(const vector<T>& nums) {
    for (auto num : nums) cout << num << " ";
    cout << endl;
}

template<class Method, typename T>
void test(vector<T> nums = vector<int>{12, 11, 5, 11, 13, 5, 6, 7}){
    cout << typeid(Method).name();
    Method::sort(nums);
    cout << "sorted: ";
    printArray(nums);
}

int main() {
    test<select_sort, int>();
    test<insert_sort, int>();
    test<bubble_sort, int>();
    test<quick_sort,  int>();
    test<merge_sort,  int>();
    test<heap_sort,   int>();
    test<count_sort,  int>();
    test<bucket_sort, double>({0.9, 0.7, 0.8, 0.4, 0.1, 0.3, 0.03});
    test<radix_sort,  int>({105, 356, 428, 348, 818});
}    