class Solution {
private:
    int digitsSum(int num){
        int sum = 0;
        while(num>0){
            const auto digit = num%10;
            sum+= (digit*digit);
            num/=10;
        }
        return sum;
    }
public:
    bool isHappy(int n) {
        unordered_set<int> res;
        int num = digitsSum(n);
        while(num != 1){
            if(res.contains(num)) return false;
            res.insert(num);
            num = digitsSum(num);
        }

        return true;
    }
};

// for any circle detection, fast slow pointer is helpful to use more time but less space
class Solution {
public:
    bool isHappy(int n) {
        int slow = n, fast = sumOfSquares(n);

        while (slow != fast) {
            fast = sumOfSquares(fast);
            fast = sumOfSquares(fast);
            slow = sumOfSquares(slow);
        }

        return fast == 1;
    }

private:
    int sumOfSquares(int n) {
        int output = 0;
        while (n != 0) {
            output += (n % 10) * (n % 10);
            n /= 10;
        }
        return output;
    }
};
