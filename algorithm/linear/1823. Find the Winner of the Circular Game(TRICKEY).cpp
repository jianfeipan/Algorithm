/*
There are n friends that are playing a game. The friends are sitting in a circle and are numbered from 1 to n in clockwise order. More formally, moving clockwise from the ith friend brings you to the (i+1)th friend for 1 <= i < n, and moving clockwise from the nth friend brings you to the 1st friend.

The rules of the game are as follows:

Start at the 1st friend.
Count the next k friends in the clockwise direction including the friend you started at. The counting wraps around the circle and may count some friends more than once.
The last friend you counted leaves the circle and loses the game.
If there is still more than one friend in the circle, go back to step 2 starting from the friend immediately clockwise of the friend who just lost and repeat.
Else, the last friend in the circle wins the game.
Given the number of friends, n, and an integer k, return the winner of the game

Input: n = 5, k = 2
Output: 3
Explanation: Here are the steps of the game:
1) Start at friend 1.
2) Count 2 friends clockwise, which are friends 1 and 2.
3) Friend 2 leaves the circle. Next start is friend 3.
4) Count 2 friends clockwise, which are friends 3 and 4.
5) Friend 4 leaves the circle. Next start is friend 5.
6) Count 2 friends clockwise, which are friends 5 and 1.
7) Friend 1 leaves the circle. Next start is friend 3.
8) Count 2 friends clockwise, which are friends 3 and 5.
9) Friend 5 leaves the circle. Only friend 3 is left, so they are the winner.
Example 2:

Input: n = 6, k = 5
Output: 1
Explanation: The friends leave in this order: 5, 4, 6, 2, 3. The winner is friend 1.
*/

class Solution {
/*
fact:
    circle count, clocktwise, repeat to one left
idea:
    1 make an linked list and do the rules --> need a Node->next structure
    2 we can do it recursivly :  


*/
private:
    void print_vector(vector<bool> players)
    {
        cout<<"[";
        for(int i = 0; i<players.size(); ++i) cout<< (players[i]? i : -1) <<", ";
        cout<<"]";
        cout<<endl;


    }

public:
    int findTheWinner_brutforce(int n, int k) {//O(N*K)
        vector<bool> players(n, true);
        
        int i = 1;
        int current = 0;
        while(i<n)//loop n-1 times
        {
            // print_vector(players);
            int j = 0;
            while(j<k)//count k - i times
            {
                if(players[current]) {
                    // cout<<current<<":j= "<<j;
                    j++;
                }
                 current=(current+1)%n; 
            }
            // cout<<endl;

            current=(current-1 +n)%n; 
            players[current] = false;
            
            // cout<< current <<"out, "<<endl;

            do
            {
                current=(current+1)%n; 
            }while(!players[current]);
            // cout<< current <<" next "<<endl;

            ++i;
        }
        for(int i=0; i<n; ++i) if(players[i]) return i+1;
        return -1;
    }

    int findTheWinner(int n, int k) { //thing from the target to initial: you already have the winner, how to put all players back ? 
        int winner = 0, cur = 1;//winner set to 0, indeed it's the relative position

        for(int i = 1; i <= n; i++) {//last removed is winner, so we generate n times, we got all players back
            winner = (winner + k) % i;// with i player, k distance will have another player, which will be remove this time, so winner will be winner + k  to avoid being removed.
        }

        return winner+1;
    }
};
