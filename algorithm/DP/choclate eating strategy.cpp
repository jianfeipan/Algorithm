#include <algorithm>
#include <deque>
#include <iostream>
#include <string>
#include <vector>
#include <utility>
/*
You’ve just got a tube of delicious chocolates and plan to eat one piece a day – either by picking the one on the left or the right.
Each piece has a positive integer that indicates how tasty it is. Since taste is subjective, there is also an expectancy factor. A piece will taste better if you eat it later: if the taste is m (as in hmm) on the first day, it will be km on day number k.
Your task is to design an efficient algorithm that computes an optimal chocolate eating strategy and tells you how much pleasure to expect.
*/
static int maxChoclateUtility_greedy(std::deque<int> choclates) 
{
   /*
      greedy : eat from small, keep bigger ones for later to be more happy
   */
   int maxUtility = 0;
   int dayCount = 1;
   while (!choclates.empty())
   {
      int left = choclates.front();
      int right = choclates.back();

      if (left <= right)
      {
         std::cout << "left : " << left << std::endl;
         choclates.pop_front();
         maxUtility += dayCount * left;
      }
      else
      {
         std::cout << "right : " << left << std::endl;
         choclates.pop_back();
         maxUtility += dayCount * right;
      }
      ++dayCount;

   }

   return maxUtility;
}
//T: O(N)
//S: O(1)

static int maxChoclateUtility_recusive(const std::deque<int> & choclates, int day)
{
    if (choclates.empty())
    {   
        return 0;
    }
    auto leftBranch = choclates;
    int maxUtilityIfTakeLeft = leftBranch.front() * day;
    leftBranch.pop_front();
    maxUtilityIfTakeLeft += maxChoclateUtility_recusive(leftBranch, day + 1);


   auto rightBranch = choclates;
   int maxUtilityIfTakeRight = rightBranch.back() * day;
   rightBranch.pop_back();
   maxUtilityIfTakeRight += maxChoclateUtility_recusive(rightBranch, day + 1);

   return std::max(maxUtilityIfTakeLeft, maxUtilityIfTakeRight);
}
//T(N) = T(N-1) + T(N-2) +O(1)
//T: O(2^N)

static int maxChoclateUtility_DP_recusive(std::deque<int> choclates)
{
   return maxChoclateUtility_recusive(choclates, 1);
}
//T: O(2^N)
//S: O(logN)

static int maxChoclateUtility_DP_with_memory_recusive(const std::vector<int> & choclates, std::vector<std::vector<std::pair<int, bool>>> & memory, int from, int to, int day)
{
    std::cout<<"("<<from<<","<<to<<") :"<<memory[from][to].first<<std::endl;
    if (from == to)
    {   
        memory[from][to] = { choclates[from] * day, true};
    }
    else if(memory[from][to].first==-1)
    {
        int maxUtilityIfTakeLeft = choclates[from] * day;

        maxUtilityIfTakeLeft += maxChoclateUtility_DP_with_memory_recusive(choclates, memory, from + 1, to, day + 1);


        int maxUtilityIfTakeRight = choclates[to] * day;

        maxUtilityIfTakeRight += maxChoclateUtility_DP_with_memory_recusive(choclates, memory, from, to -1, day + 1);
        
        if(maxUtilityIfTakeLeft>=maxUtilityIfTakeRight)
            memory[from][to] = { maxUtilityIfTakeLeft, true};
        else
            memory[from][to] = {maxUtilityIfTakeRight, false};
        
    }
    std::cout<<"("<<from<<","<<to<<")="<<memory[from][to].first<<std::endl;
    return memory[from][to].first;
}

static int maxChoclateUtility_DP_with_memory(const std::vector<int> & choclates)
{
    //MaxUtility with i -> j left  and pickLeft : we need to memorise operation and score
    std::vector<std::vector<std::pair<int, bool>>> memory(choclates.size() , std::vector<std::pair<int, bool>>(choclates.size(), {-1, false}));
    
    return maxChoclateUtility_DP_with_memory_recusive(choclates, memory, 0, choclates.size()-1, 1);
}

void printMatrix(const std::vector<std::vector<std::pair<int, bool>>> & memory)
{
    for(const auto & line : memory)
    {
        for(const auto & e : line)
        {
            std::cout<<"\t"<<e.first;
        }
        std::cout<<std::endl;
    }
     std::cout<<std::endl;
}

static int maxChoclateUtility_DP_with_tablution(const std::vector<int> & choclates)
{
    //MaxUtility with i -> j left  and pickLeft : we need to memorise operation and score
    std::vector<std::vector<std::pair<int, bool>>> memory(choclates.size() , std::vector<std::pair<int, bool>>(choclates.size(), {-1, false}));
    
    
    for(int i = 0; i< choclates.size(); ++i)//last chocolate can be i in [0, N-1]
    {
        memory[i][i] = {choclates[i] * choclates.size(), false};
    }
    
    for(int day = choclates.size() - 1; day>=1; day--)
    {
        for(int i = 0; i < day; ++i)
        {
            int from = i;
            int to = from + (choclates.size() - day);//to - from =  rest days
            
   
            /* [from, to] on day is base on day+1's result
            [from, to] 's next step could be [from+1, to] (pick left) or [from, to - 1] (pick right)
            example: [0,1] 's next step could be pick left : [1,0] and pick right [0,0] 
            
            */
            
            //for example, if now we are on day = n-1, so the memoey[i][i] are aviliable, we can compute max for day = n-1
            const int resultPickLeft = memory[from+1][to].first + choclates[from] * day;
            const int resultPickRight = memory[from][to-1].first + choclates[to] * day ;
            
            if(resultPickLeft>=resultPickRight)
            {
                memory[from][to] =   {resultPickLeft, true}; 
            }
            else
            {
                memory[from][to] =   {resultPickRight, false};
            }
        }
        printMatrix(memory);
    }
    
    
    return memory[0][choclates.size()-1].first;
}


static int maxChoclateUtility(const std::deque<int> & choclates) 
{
   int maxGreedy = maxChoclateUtility_greedy(choclates);
   std::cout << std::endl << "greedy max utility: " << maxGreedy << std::endl;
   
   int maxDPrecusive = maxChoclateUtility_DP_with_memory(std::vector<int>(choclates.begin(), choclates.end()));

   std::cout << std::endl << "max utility DP memory recusive: " << maxDPrecusive << std::endl;
   
   int maxDPTabution = maxChoclateUtility_DP_with_tablution(std::vector<int>(choclates.begin(), choclates.end()));
   std::cout << std::endl << "max utility DP tablution: " << maxDPTabution << std::endl;
   
   
   return maxGreedy;
}

int main()
{
   maxChoclateUtility({1,2,7,1,4,5,2,6});
   return 0;
}
