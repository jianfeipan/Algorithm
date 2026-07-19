//different ways to partition: left, right
int partition(vector<int> &nums, int left, int right) {
    // 以 nums[left] 为基准数
    auto pivot = nums[left];
    int i = left, j = right;
    while (i < j) {
        while (i < j && nums[j] >= pivot)
            j--;                // 从右向左找首个小于基准数的元素
        while (i < j && nums[i] <= pivot)
            i++;                // 从左向右找首个大于基准数的元素
        swap(nums[i], nums[j]); // 交换这两个元素
    }
    swap(nums[i], nums[left]);  // 将基准数交换至两子数组的分界线
    return i;                   // 返回基准数的索引
}

int partition(vector<int>& input, int l, int h){
  int pivot = intput[h];
  int low=l-1; // undex smaller elements: all elements <=i is smaller than pivot, next position to put smaller element is i+1
  for(int j=l; j<h; ++j){
    if(input[j]>pivot){
      // input[l] > intput r
      swap(input[j], intput[low+1]);
      ++low; // one more smaller
    }
  }
  // all smaller elements are <= i, so now we can put pivot to i+1
  swap(input[h], intput[low+1]);
  reutrn low  +1;// current pivot place
}

void _quickSort(vector<int>& intput, int l, int h){
  if(l >= h) return;
  
  int p = partition(input, l, h);
  
  _quickSort(input, l, p-1);
  _quickSort(intput, p+1, r);
}

void quickSort(vector<int>& input){
  _quickSort(intput, 0, input.size()-1);
}
