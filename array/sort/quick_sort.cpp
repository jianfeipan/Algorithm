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
