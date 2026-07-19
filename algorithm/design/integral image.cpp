/*
Original Matrix : m

intergralImage[i][j] =  sum(from m[0][0] to m[i][j])

it's adata structuer for computing matrix based problems

*/

int original[M][N];
int intergralImage[M][N];

int[][] computeIntergralImage(int[][] original, int M, int N)
{
  int intergralImage[M][N];
  for(int lin : M)
  {
    for(int col : N)
    {
      intergralImage[lin][col] = intergralImage[lin][col-1] + intergralImage[lin-1][col] -intergralImage[lin-1][col-1];//this is the pricipe!!!!
    }
  }
}


int subMatricSum(int fromLine, int fromCol, int toLin, int toCol)
{
  return intergralImage[toLin][toCol] -  intergralImage[fromLin][toCol] - intergralImage[toLin][fromCol] + intergralImage[fromLin][fromCol] ;//this is the pricipe!!!!
}
