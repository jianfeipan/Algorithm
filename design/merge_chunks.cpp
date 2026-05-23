/*
Our library sends messages using descriptors. Each descriptor contains:

data: pointer/address of the message
length: message size in bytes

Some messages may be directly contiguous in memory and can be merged.

Example input:

{data: 1000, length: 24} GAP: 8B , END = 1000 + 24 = 1024
{data: 1032, length: 24} GAP: 0B
{data: 1056, length: 16}

The second descriptor ends at 1056, exactly where the third begins, so they can be merged:

{data: 1000, length: 24}
{data: 1032, length: 40}

Write a function group_descriptors that takes a list of descriptors and returns a new list where all contiguous descriptors are merged.

The input descriptors are not guaranteed to be sorted.
*/
#include <unordered_map>
#include <vector>
#include <algorithm>
using namespace std;

using Data = vector<size_t>;
using Len = vector<size_t>;
struct Descriptors{
    Data data;
    Len len;
};

void
group_descriptors(Descriptors& descriptors) {
    // assert(descriptors.data.size() == descriptors.len.size());
    if (descriptors.data.empty()) return;
    
    const auto& n = descriptors.data.size();
    vector<size_t> index(n);
    for (int i=0; i<n; ++i) index[i] = i;
    
    std::sort(index.begin(), index.end(), [&descriptors](size_t left, size_t right) {
        return descriptors.data[left] < descriptors.data[right]; 
    });
    
    vector<size_t> to_remove;
    
    size_t prev_end = 0;
    for (size_t i : index) {
        // if () // skip the first
        auto& start =  descriptors.data[i];
        auto& len = descriptors.len[i];
        if (start!=0 && start == prev_end) {
            // merge
            descriptors.len[i-1] += len;
            prev_end += len;
            // current index to be removed
            to_remove.push_back(i);
        }else {
            prev_end = start+len;
        }
    }
    
    for (size_t i : to_remove) {
        descriptors.data[i]= descriptors.data.back(); // assignement!  no need for swap
        descriptors.data.pop_back();
        descriptors.len[i] = descriptors.len.back();
        descriptors.len.pop_back();
    }
    
}


void
group_descriptors_hash(Descriptors& descriptors) {
    using End = size_t;
    using Index = size_t;
    unordered_map<End, Index> ends;
    const auto& n = descriptors.data.size();
    
    for (size_t i = 0; i<n; ++i) {
        const auto& start =  descriptors.data[i];
        const auto& len = descriptors.len[i];
        ends[start+len] = i;
    }
    
    vector<size_t> to_remove;
    for (size_t i = 0; i<n; ++i) {
        const auto& start =  descriptors.data[i];
        const auto& len = descriptors.len[i];
        
        auto it = ends.find(start);
        if (it!=ends.end()) {
            descriptors.len[it->second]+=len;
            to_remove.push_back(i);
        }
    }

    for (size_t i : to_remove) {
        descriptors.data[i]= descriptors.data.back(); // assignement!  no need for swap
        descriptors.data.pop_back();
        descriptors.len[i] = descriptors.len.back();
        descriptors.len.pop_back();
    }
    
}

