/*

Problem: Task manager with insert/delete/execute-next
Design a data structure to manage executable tasks.

Each task has:

taskId (unique)
priority (higher means executed earlier)
createdAt (or seq ) to break ties among equal priority (earlier first)
Support operations:

add(taskId, priority)
remove(taskId) (task may or may not exist; removing a task prevents future execution)
executeNext() -> taskId | null
Returns and removes the highest-priority remaining task.
Tie-breaker: smaller createdAt/seq first.
Requirements
Aim for O(log n) per operation.
You may not linearly scan all tasks on executeNext() .
Notes
Explain how you handle remove() efficiently even if the task is not at the top of the heap when removed.
*/

#include <iostream>
#include <set>
#include <unordered_map>
#include <optional>
using namespace std;

class TaskManager {
    int seq = 0;
    // {-priority, seq, taskId} — negative priority so std::set gives highest-priority first
    set<tuple<int, int, int>> tasks;
    // taskId -> iterator into `tasks` for O(log n) removal
    unordered_map<int, set<tuple<int, int, int>>::iterator> lookup;

public:
    void add(int taskId, int priority) {
        // If task already exists, remove old entry first
        remove(taskId);
        auto [it, _] = tasks.emplace(-priority, seq++, taskId);
        lookup[taskId] = it;
    }

    void remove(int taskId) {
        auto it = lookup.find(taskId);
        if (it != lookup.end()) {
            tasks.erase(it->second);
            lookup.erase(it);
        }
    }

    optional<int> executeNext() {
        if (tasks.empty()) return nullopt;
        auto it = tasks.begin();
        int taskId = get<2>(*it);
        lookup.erase(taskId);
        tasks.erase(it);
        return taskId;
    }
};

/*
 * How remove() works efficiently:
 *   We store an iterator to each task's position in the ordered set inside
 *   an unordered_map keyed by taskId. This lets us jump straight to the
 *   element in the set and erase it in O(log n), without scanning.
 *
 * Complexity:
 *   add()         — O(log n)  (set insert + possible erase)
 *   remove()      — O(log n)  (map lookup O(1) avg + set erase O(log n))
 *   executeNext() — O(log n)  (set begin + erase)
 */

int main() {
    TaskManager tm;

    tm.add(1, 5);
    tm.add(2, 10);
    tm.add(3, 10);  // same priority as task 2, but added later
    tm.add(4, 1);

    // Should execute task 2 first (priority 10, earlier seq than task 3)
    auto t = tm.executeNext();
    cout << "Execute: " << (t ? to_string(*t) : "null") << endl;  // 2

    // Remove task 3 before it gets executed
    tm.remove(3);

    // Next should be task 1 (priority 5), since task 3 was removed
    t = tm.executeNext();
    cout << "Execute: " << (t ? to_string(*t) : "null") << endl;  // 1

    t = tm.executeNext();
    cout << "Execute: " << (t ? to_string(*t) : "null") << endl;  // 4

    t = tm.executeNext();
    cout << "Execute: " << (t ? to_string(*t) : "null") << endl;  // null

    return 0;
}
