class Solution {
public:
    int scheduleCourse(vector<vector<int>>& courses) //O(N * N)-->every course could take or not
    {//same to remove max left, but use a maxHeap to find the max instead of iterating : O(NlogN)
        sort(courses.begin(), courses.end(), [](const auto & left, const auto & right){
            return left[1] < right[1];
        });
        int time = 0, count = 0;
        
        priority_queue<int> maxHeap;//by default less, maxHeap
        
        for (int current = 0; current < courses.size(); current++) 
        {
            if (time + courses[current][0] <= courses[current][1])//can take current
            {
                time += courses[current][0];
                maxHeap.push(courses[current][0]);
            }
            else 
            {
                if(!maxHeap.empty())
                {
                    if (maxHeap.top() > courses[current][0]) 
                    {
                        time += courses[current][0] - maxHeap.top();
                        maxHeap.pop();
                        maxHeap.push(courses[current][0]);
                    }
                }
            }
        }
        return maxHeap.size();
        
    }
    
    
    int scheduleCourse_remove_leftmax(vector<vector<int>>& courses) //O(N * N)-->every course could take or not
    {
        sort(courses.begin(), courses.end(), [](const auto & left, const auto & right){
            return left[1] < right[1];
        });
        int time = 0, count = 0;
        for (int current = 0; current < courses.size(); current++) 
        {
            if (time + courses[current][0] <= courses[current][1])//can take current
            {
                time += courses[current][0];
                count++;
            }
            else 
            {
                int leftMax = current;
                for (int j = 0; j < current; ++j) 
                {
                    if (courses[j][0] > courses[leftMax][0])
                        leftMax = j;
                }
                
                if (courses[leftMax][0] > courses[current][0]) {
                    time += courses[current][0] - courses[leftMax][0];
                }
                courses[leftMax][0] = -1;
            }
        }
        return count;
        
    }
    
    
    int scheduleCourse_DP_recursion(vector<vector<int>>& courses) //O(N * days)-->size of memory
    {
        //DP
        sort(courses.begin(), courses.end(), [](const auto & left, const auto & right){
            return left[1] < right[1];
        });
        vector<vector<int>> memory(courses.size(), vector<int>(courses.back()[1], -1));
        return scheduleCourse(courses, 0, 0, memory);
        
    }
    
    int scheduleCourse(const vector<vector<int>> & courses, int fromCourse, int fromDay, vector<vector<int>> & memory)
    {
        if(courses.back()[1] <= fromDay) return 0;
        
        auto & cache = memory[fromCourse][fromDay];
        if(cache != -1) return cache;
        
        if(fromCourse == courses.size()-1) 
        {
            cache = fromDay <= courses[fromCourse][1] - courses[fromCourse][0] 
                ? 1
                : 0;
            return cache;
        }
        
        int maxCourses = 0;
        if(fromDay <= courses[fromCourse][1] - courses[fromCourse][0])
        {
            maxCourses = 1 + scheduleCourse(courses, fromCourse+1, fromDay + courses[fromCourse][0], memory);
        }
        
        maxCourses = max(maxCourses, scheduleCourse(courses, fromCourse+1, fromDay, memory));
        
        cache = maxCourses;
        return maxCourses;
    }
};
