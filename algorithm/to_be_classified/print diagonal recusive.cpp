#include <algorithm>
#include <functional>
#include <iostream>
#include <list>
#include <memory>
#include <stdio.h>
#include <string.h>
#include <unordered_map>
#include <unordered_set>
#include <vector>
#include <stack>
#include <map>
#include <queue>

using namespace std;

/*
print diagonal
*/
static void diagonalPrintLin(int number)
{
    if(number == 0) cout<<"";
    else
    {
        cout<<"*";
        diagonalPrintLin(number-1);
    }
}

static void diagonalPrintLins(int lin, int n)//0,2
{
    if(lin ==2*n )
    {
         diagonalPrintLin(lin - n);
    }
    else if(lin < n)
    {
        diagonalPrintLin(lin);
        cout<<endl;
        diagonalPrintLins(lin+1, n);
    }
    else if(lin < 2*n)
    {
        diagonalPrintLins(lin+1, n);
        cout<<endl;
        diagonalPrintLin(lin-n);
    }
}

void diagonalPrintTo(int n)
{
    diagonalPrintLins(0, n);
}

int main(int argc, char *argv[])
{

    diagonalPrintTo(4);
    return 0;
}
