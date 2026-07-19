#include <stdio.h>
#include <string.h>
#include <string>
#include <time.h>
#include <unordered_map>
#include <unordered_set>
#include <iostream>
#include <sstream>
#include <algorithm>
#include <vector>
using namespace std;
/*
. two string are given had to find the missing string

    Ex - String one - "This is an example"
           String two - "is example" 
         ans - This, an  

*/

 vector<string> findMissing(const string & left, const string & right)
 {
     vector<string> missing;
     unordered_set<string> dict; 
     
     istringstream issRight(right);
     while(issRight)
     {
         string word;
         issRight>>word;
         dict.insert(word);
     }
     
     istringstream issLeft(left);
     while(issLeft)
     {
          string word;
         issLeft>>word;
         if(dict.count(word) == 0) missing.push_back(word);
     }
     
     
     return missing;
 }

int main(int argc, char *argv[])
{
   
    auto missing = findMissing("This is an example", "is example");
    
    for(const auto & word : missing) cout<<word<<","; 
       
    return 0;
}
