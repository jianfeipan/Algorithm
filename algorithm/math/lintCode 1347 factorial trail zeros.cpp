class Solution {
public:
    /**
     * @param n: a integer
     * @return: return a integer
     */
    //ATTENTION : factorial will quickly pass INT_MAX, should think differently
    /*
    where do the zeros come : by 5 * 2, any other numbers cannot make a trail zero
    since in n, we have so many 2s, so how many 5 in n, will make same number of 0s

    for example : 10: has tow 5s: 1*2*3*4*5*6*7*8*9*10, 5 will contribute one 5 and 10 will contribut another
    for 20 : 5, 10, 15, 20 will have 4 5 as factor
    for 50 : 5,10,15,20,25,30,35,40,45,50 will have 10 5 as facrtor

    fives(N) = N/5 + fives(N/5)   

    */
    int trailingZeroes(int n) {
        
        if (n >= 5) {
            return n / 5 + trailingZeroes (n / 5);
        } else {
            return 0;
        


    }
    
};
