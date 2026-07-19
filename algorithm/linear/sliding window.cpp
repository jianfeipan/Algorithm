#include <iostream>
#include <vector>
using namespace std;

/*
     0  1  2  3  4  5
A = [3, 1, 5, 7, 8, 2] 
        ^     ^
W = 3 


B[0] = (3 + 1 + 5) / 3
B[1] = (1 + 5 + 5) / 3

B[4] =  (8 + 2)/2
B[5] = 2

len(B) == len(A)

scope : 
      W size_t , W maybe > size of A
      
*/

  vector<double> makeSlidingWindowAvg_improved(const vector<int> & nums, size_t w)
  {
   
    if(w == 0) return {};//may throw an exception
    
    vector<double> swavg;swavg.reserve(nums.size());
    
    int sum = 0;
    size_t realW = 0;
    for(size_t i = 0; i < w; ++i)
    {
      if(i < nums.size())
      {
        sum+=nums[i];
        ++realW;
      }
    }   
    swavg.push_back((double)sum/realW);
    
    for(size_t from = 1; from<nums.size(); ++from)
    {
     
      sum-=nums[from-1];
      
      if(from + w -1 < nums.size())
        sum+=nums[from + w -1];
      else
        --realW;
      
      swavg.push_back((double)sum/realW);
      
    }
    
    return swavg;
  }

  vector<double> makeSlidingWindowAvg(const vector<int> & nums, size_t w)
  {
   
    if(w == 0) return {};//may throw an exception
    
    vector<double> swavg;swavg.reserve(nums.size());
    
    for(size_t from = 0; from<nums.size(); ++from)
    {
      int sum = 0;
      int realSizeW = 0;
      for(size_t i = 0; i < w; ++i)
      {
        if(i+from < nums.size())
        {
          ++realSizeW;
          sum+=nums[i+from];
        }
      }
      swavg.push_back((double)sum/realSizeW);
    }
    
    return swavg;
  }



// To execute C++, please define "int main()"
int main() {
  
  vector<int> nums({3, 1, 5, 7, 8, 2});
  size_t w = 3;
  
  vector<double> swavg = makeSlidingWindowAvg_improved(nums, w);
  
  for(auto i : swavg)
  {
    cout<< i<<", ";
  }
  cout<<endl;
  return 0;

}
