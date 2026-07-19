class Solution {

    /*


    Given a list of non-negative integers nums, arrange them such that they form the largest number and return it.

Since the result may be very large, so you need to return a string instead of an integer.

 

Example 1:

Input: nums = [10,2]
Output: "210"
Example 2:

Input: nums = [3,30,34,5,9]
Output: "9534330"


Fact:
    total digit number is fixed (tatal sum digit number of all numbers)
    need keep left bigger
    string is easiyer to compare digit by digit

idea:
    [10, 2]
    1<2, so put 2 first
    see in the code

pay attention:
    corner case: [0, 0], and [0]


    */


    static bool biggerDigit(const string & left, const string & right){        
        if(left.size() == right.size()) return left>right;
   
        /*      
        else 
        for exmaple
        [40, 3] should be 403 -> "40" > "3"
        [30, 3] should be 330 -> "3" > "30"
        [34, 3] should be 343 -> "34" > "3"

        --> loop the longer one with the lenght of shorter one, compare till big or small  

        for exmaple : 3131 30 < 31 == 30 < 31, 3131 32 > 31 == 32 > 31, --> same size ompare
        and if no enough digit:  
        3131 3 , 31 == 3 , 31 --> change longer, shorter position 31, 3 == 1 < 3 --> first 3 is the same and second 1 is smaller
        3131 4 , 31 == 4 , 31 --> change longer, shorter position 31, 4 == 4 > 3 --> first digit 4 is bigger


        */
        else if(left.size() > right.size())
        {   
            const auto & leftPart = left.substr(0, right.size());
            if(leftPart==right) return biggerDigit( left.substr(right.size()), right);
            else return leftPart > right;
        }
        else //if(left.size()<right.size())
        {
            const auto & leftPart = right.substr(0, left.size());
            if(left==leftPart) return biggerDigit(left, right.substr(left.size()));
            else return left > leftPart;
        }
    }
public:
    string largestNumber(vector<int>& nums) {
        vector<string> numsStr(nums.size());
        for(int i = 0; i< nums.size(); ++i )
        {
            numsStr[i] = std::to_string(nums[i]);
        }

        
        std::sort(numsStr.begin(), numsStr.end(), biggerDigit);

        //remove zeros in the front
        stringstream ss;
        bool haveNoZeroValue = false;
        for(int i = 0; i< numsStr.size(); ++i )
        {
            if(numsStr[i] != "0") haveNoZeroValue = true;
            if(haveNoZeroValue)
                ss<<numsStr[i];
        }

        

        return haveNoZeroValue ? ss.str() : "0";
    }
};
