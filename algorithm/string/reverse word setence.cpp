#include <stdio.h>
#include <string.h>
#include <string>
#include <time.h>
#include <unordered_map>
#include <iostream>
using namespace std;

void reverse_word(string & word, size_t from, size_t to)
{
    size_t left = from;
    size_t right = to;
    
    while(left<right)
    {
        auto temp = word[left];
        word[left]= word[right];
        word[right]= temp;
        ++left;
        --right;
    }
}
void reverse_word(string & word)
{
    reverse_word(word, 0, word.size()-1);
}


void reverse_setence(string& setence)
{
    //Hello world --> world Hello
    reverse_word(setence, 0, setence.size()-1);

    int privious = 0;
    for(int i=0; i<setence.size(); ++i)
    {
        if(setence[i] == ' ')
        {
            reverse_word(setence, privious, i-1);
            privious = i+1;
        }
    }
    reverse_word(setence, privious, setence.size()-1);
    
}
  
  
int main(int argc, char *argv[])
{
    string word("Hello world");
    
    reverse_word(word);
    
    cout<<word<<endl;
    
    string setence("Hello world");
    reverse_setence(setence);
    
    cout<<setence<<endl;

    return 0;
}
