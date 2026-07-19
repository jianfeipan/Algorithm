/*
A matrix diagonal is a diagonal line of cells starting from some cell in either the topmost row or leftmost column and going in the bottom-right direction until reaching the matrix's end. For example, the matrix diagonal starting from mat[2][0], where mat is a 6 x 3 matrix, includes cells mat[2][0], mat[3][1], and mat[4][2].

Given an m x n matrix mat of integers, sort each matrix diagonal in ascending order and return the resulting matrix.

 

Example 1:

Input: mat = [[3,3,1,1],[2,2,1,2],[1,1,1,2]]
Output: [[1,1,1,1],[1,2,2,2],[1,2,3,3]]
*/

class Solution {
/*
fact:
    matrix diagonal has different lenght, based on the matrix size  
idea:
    - I know how to sort a vector (std::stort())
    - can we do the transformation  easily between  original matrix and a vector of Matrix diagonal ? 
        -> we just call std::sort for all Matrix diagonal vectors  then we transform back to matrix

*/
private:
    vector<vector<int>> toMatrixDiagonals(const vector<vector<int>> & matrix)
    {
        //(m x n) --> (m+n-1, *)
        int lineCount = matrix.size();//m
        int colCount = matrix[0].size();//n


        vector<vector<int>> res(lineCount+colCount-1, vector<int>());

        for(int i=0; i<res.size(); ++i)
        {
            //(x0, y0) --> push until reach lineCount or colCount
            int line = 0;
            int col = 0;
            if(i < lineCount-1)
            {
                line = lineCount - i -1;
            }
            else if(i > lineCount-1)
            {
                col = i - lineCount +1;
            }


            while(line < lineCount && col < colCount)
            {
                res[i].push_back(matrix[line][col]);
                ++line;
                ++col;
            }
        }
        return res;
    }

    void toMatrix(const vector<vector<int>> & matrixDiagonals, vector<vector<int>> & matrix)
    {
        //(m+n-1, *) -> ?? (m,n)
        int lineCount = matrix.size();//m
        int colCount = matrix[0].size();//n


        for(int i=0; i<matrixDiagonals.size(); ++i)
        {
            
            int line = 0;
            int col = 0;
            if(i < lineCount-1)
            {
                line = lineCount - i -1;
            }
            else if(i > lineCount-1)
            {
                col = i - lineCount +1;
            }

            for(int num : matrixDiagonals[i])
            {
                //cout << "("<< line<<","<< col<<"): "<< num<<endl;
                matrix[line][col] = num;
                ++line;
                ++col;
            }
        }
    }


public:
    vector<vector<int>> diagonalSort_zoom_out(vector<vector<int>>& mat) {

        if(mat.empty()) return mat;
        vector<vector<int>> matrixDiagonals = toMatrixDiagonals(mat);

        for(auto & matrixDiagonal : matrixDiagonals)
        {
            std::sort(matrixDiagonal.begin(), matrixDiagonal.end());
        }

        vector<vector<int>> res = mat;
        toMatrix(matrixDiagonals, res);

        return res;
    }

    //better way is to do that sort "IN PLACE": you just need one vector, set back the result immidiatly

     vector<vector<int>> diagonalSort(vector<vector<int>>& mat) {
        vector<int> k;
        int m = mat.size() , n = mat[0].size();
        for (int r=0; r<m; r++)        // r-> row
        {
            k.clear();
            for (int j=0,i=r; j<n && i<m ; j++,i++) k.push_back(mat[i][j]);    // add to vector
            sort(k.begin(),k.end());
            for (int j=0,i=r; j<n && i<m ; j++,i++) mat[i][j]=k[j];            // replace
        }
        for (int c=1; c<n; c++)       // c->column
        {
            k.clear();
            for (int i=0, j=c; j<n && i<m; i++, j++) k.push_back(mat[i][j]);   // add to vector
            sort(k.begin(),k.end());
            for (int i=0, j=c; j<n && i<m; i++, j++) mat[i][j] = k[i];         //replace
        }
        return mat;  
    }
};
