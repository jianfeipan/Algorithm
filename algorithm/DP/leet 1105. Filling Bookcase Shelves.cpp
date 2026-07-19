class Solution {
public:
    
    
    int minHeightShelves(vector<vector<int>>& books, int shelfWidth) 
    {
        vector<vector<vector<int>>> memory(books.size(), vector<vector<int>>(1000, vector<int>(1000, -1)));

        return minHeightShelves_DP(books, 0, 0, 0, shelfWidth, memory);
    }

    
    int minHeightShelves_DP(vector<vector<int>>& books, 
                            int from, int currentHight, int currentWidth,
                            int shelfWidth, 
                            vector<vector<vector<int>>>& memory) 
    {
        auto & cache = memory[from][currentHight][currentWidth]; 
        if(cache != -1) return cache;
        
        if(from == books.size() - 1)
        {
            if(currentWidth + books[from][0] <= shelfWidth)
                cache = max(currentHight, books[from][1]);
            else
                cache = currentHight+ books[from][1];
                
            return cache;
        }
        
        int minHeight = INT_MAX;
        if(currentWidth + books[from][0] <= shelfWidth)
        {
            int maxHightIfPutCurrent = max(currentHight, books[from][1]);
            
            minHeight = minHeightShelves_DP(books, from+1, maxHightIfPutCurrent, currentWidth+books[from][0], shelfWidth, memory);
        }
        minHeight = min(minHeight, 
                        currentHight + minHeightShelves_DP(books, from+1,  books[from][1], books[from][0], shelfWidth, memory));
        cache = minHeight;
        return minHeight;
    }

    
    
    int minHeightShelves_tablution(vector<vector<int>>& books, int shelfWidth) 
    {
        //DP
        vector<int> minHeights(books.size() +1, 0);

        for(int current = 0; current < books.size(); current++) 
        {
            int currentShelfHeight = books[current][1];
            int currentShelfWidth = books[current][0];
            
            minHeights[current+1] = currentShelfHeight + minHeights[current];
            
            for(int prev = current-1; prev >= 0; prev--) 
            {
                const int prevBookWidth = books[prev][0];
                const int prevBookHeight = books[prev][1];
                
                if (prevBookWidth + currentShelfWidth > shelfWidth) break;
                
                currentShelfWidth += prevBookWidth; /* adding prev book to current shelf */
                currentShelfHeight = max(currentShelfHeight, prevBookHeight);
                
                int prevShelfHeightAfterRemovingPrevBook = minHeights[prev];
                minHeights[current+1] = min(prevShelfHeightAfterRemovingPrevBook + currentShelfHeight, 
                                            minHeights[current+1]);
            }
        }
        
        return minHeights[books.size()];
        
    }
 
};
