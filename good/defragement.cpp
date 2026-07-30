#include <vector>
#include <unordered_set>
#include <memory>      // std::construct_at, std::destroy_at
#include <utility>     // std::move
#include <cstddef>  
/*
given: 
    vector of objects in a buffer
mission: 
    defragmement the buffer
output:
    new buffer size
*/

// Assumption: we don't care the order of the elements of vector
/*
repeat the quesion: 

draw a test case: 

    objects: [a,    b ,c  ]  
    buffer   [null, c, a, null b]
    what we want: [x,x,x,null, null]

    we don't need to do anything of c,a, just move b to begining of the buffer

solution: 
    we need a map to know which addresse is occupied by which index
    find the first free slot in buffer, 
    go over vector, if the addresse is out of boundry, move it to the slot, and point to next free slot.


*/
template<typename T>
size_t defragement(std::vector<T*>& objects, void* begin_buffer) {
    if (objects.empty() || begin_buffer == nullptr) return 0;

    std::unordered_set<T*> occupied; occupied.reserve(objects.size());
    for (auto slot : objects)  if(slot) occupied.insert(slot);    // prevent nullptr situation

    const size_t object_count = occupied.size();

    const auto begin_slot = static_cast<T*>(begin_buffer);
    const auto end_slot = begin_slot + object_count;           // occupied.size() is the real size without nullptr

    auto free_slot = begin_slot;
    for (size_t index = 0; index < objects.size(); ++index) {
        auto current_slot = objects[index];

        if (current_slot >= end_slot || 
            current_slot < begin_slot ) {               // also cover the slots before begin_slot
            
            while(occupied.count(free_slot)) ++free_slot;

            std::construct_at(free_slot, std::move(*current_slot));  // new (free_slot)T(std::move(*obj));
            std::destroy_at(current_slot);                           // obj->~T();
                                                                     // free(obj) --> don't do this, you don't own the memory
            objects[index] = free_slot;
                                                                // occupied.erase(current_slot); 
                                                                // occupied.insert(free_slot);
                                                                // NO NEED TO UPDATE SET: free slot incremented and will never hit the out-of-boundry or just updated
            ++free_slot;
        }
    }
    return object_count*sizeof(T);
}
