#include <vector>
#include <unordered_map>
#include <unordered_set>
/*
merge chunks if they are next to each other.
a chunk is defined by 
    addresse and size

*/
struct Chunk {
    std::byte* begin{nullptr};
    size_t size{0};
};
void merge(std::vector<Chunk>& chunks) {
    if (chunks.empty()) return;

    std::unordered_map<std::byte*, size_t> begin_index; 
    begin_index.reserve(chunks.size());
    for(size_t i = 0; i < chunks.size(); ++i) begin_index[chunks[i].begin] = i;
    
    std::vector<char> to_remove(chunks.size(), false);    // natually sorted

    for(size_t i = 0; i < chunks.size(); ++i) {
        auto& current = chunks[i];
        
        auto it = begin_index.find(current.begin + current.size);
        while (it != begin_index.end()) {
            current.size += chunks[it->second].size;
            to_remove[it->second] = true;
            begin_index.erase(it);
            
            it = begin_index.find(current.begin + current.size);
        }
    }

    /*
        i         tail
                  
chunks    0 1 2 3 4 5 6 7 8
              x   x       x
    
to_rm     2 4 8 
    
    */

    size_t tail = chunks.size()-1;
    for(size_t i = 0; i <=tail; ++i) {
        if (to_remove[i]) {
            while(i<tail && to_remove[tail]) --tail;
            if (i < tail) {
                chunks[i] = std::move(chunks[tail]);
                --tail;
            }
        } 
    }
    chunks.resize(tail + 1);
}
