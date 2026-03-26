/*
// complex game rules....

You are given an integer array hand where hand[i] is the value written on the ith card and an integer groupSize.

You want to rearrange the cards into groups so that each group is of size groupSize, and card values are consecutively increasing by 1.

Return true if it's possible to rearrange the cards in this way, otherwise, return false.

Example 1:

Input: hand = [1,2,4,2,3,5,3,4], groupSize = 4

Output: true
Explanation: The cards can be rearranged as [1,2,3,4] and [2,3,4,5].

Example 2:

Input: hand = [1,2,3,3,4,5,6,7], groupSize = 4

Output: false


idea:
    use group size to "consum" hands
    fron smallest, take groupSize card, consecutively
    then another group ... -> a map, with key in order

    if in one group, not consecutive: false
    if no enough in a group --> this can be check by N%groupSize==0
O(n*logn)


*/
class Solution {
public:
    bool isNStraightHand(vector<int>& hand, int groupSize) {
        if(hand.size() % groupSize != 0) return false;
        
        using Card = int;
        using Count = int;
        map<Card, Count> histogram;
        for(auto card:hand) ++histogram[card];

        int groups = hand.size() / groupSize;
        for(int group = 0; group<groups; ++group){
            if(histogram.empty()) return false;
            auto& [start, count] = *histogram.begin();
            for(int i = 0; i<groupSize; ++i){
                auto found = histogram.find(start+i);
                if(found == histogram.end())  false;

                --(found->second);
                if(found->second == 0) histogram.erase(found);              
            }
        }

        return histogram.empty();

    }
};


/*we are having nlogn mostly for the sorting, 
however we don't need it: 
we expect numbers to be consecutive, and the smallest number should always be in a group
so we just do 
    while (count[start - 1] > 0) start--;
to get to the smallest number, then go right to check until the current number

all those whiles, depends on the number it self, so it's constant O(1), doesn't depends on N
*/
class Solution {
public:
    bool isNStraightHand(vector<int>& hand, int groupSize) {
        if (hand.size() % groupSize != 0) return false;

        unordered_map<int, int> count;
        for (int num : hand) count[num]++;

        for (int num : hand) {
            int start = num;
            while (count[start - 1] > 0) start--;
            while (start <= num) {
                while (count[start] > 0) {
                    for (int i = start; i < start + groupSize; i++) {
                        if (count[i] == 0) return false;
                        count[i]--;
                    }
                }
                start++;
            }
        }
        return true;
    }
};
