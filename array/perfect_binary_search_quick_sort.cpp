#include <vector>
using namespace std;


bool IS_BLUE(int v){
    return v<5;
}

int binary_search(const vector<int>& a){
    const auto& N = a.size();
    int l = -1;
    int r = N;
    auto m = l+(r-l)/2;
    while(l+1!=r){
        if(IS_BLUE(a[m])) l=m;
        else r=m;
    }
    return r;
}

/*
BBBBBB] [RRRRRR
     l   r

IS_BLUE(v) v<5:  return r : lower_bound: first element >= 5
IS_BLUE(v) v<=5: return r : upper_bound:
*/

// Lomuto partition
int partition(vector<int>&a, int l, int r){
    auto p = r;


    while(l<r){
        if(a[l]<=a[p]) ++l;
        else if(a[p]<=a[r]) ++r;
        else swap(a[l], a[r]);
    }
    swap(a[p], a[l-1]); // now l=r and a[r]>=a[p]
    return l-1;
}

void quick_sort(vector<int>& a, int l, int r){
    if(l>=r) return;

    const auto p = partition(a, l, r);
    quick_sort(a, l, p-1);
    quick_sort(a, p+1, l);
}
