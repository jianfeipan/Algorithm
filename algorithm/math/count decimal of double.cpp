#include <iostream>
#include <cmath>
#include <cstdio>
#include <string>
#include <vector>
#include <algorithm>
#include <set>
#include <optional>
#include <utility>
#include <climits>
#include <cmath>

using namespace std;

size_t dicimalCount(double num)
{
    size_t count = 0;
    
    num = abs(num);
    num = num - int(num); //---> may close to 1.e-10
    while(num>1.e-9)
    {
        cout<<num<<endl;
        count++;
        num -= (int)num;
        num*=10;
    }
    
    return count-1;
}

int main()
{
    
    cout<< "dicimalCount : " <<dicimalCount(1.123456)<<endl;
    return 0;
}
