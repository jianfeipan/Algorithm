

#include <algorithm>
#include <functional>
#include <iostream>
#include <list>
#include <memory>
#include <stdio.h>
#include <string.h>
#include <unordered_map>
#include <vector>
#include <map>
#include <stack>
#include <unordered_set>
#include <stdexcept>
#include <deque>

using namespace std;

/*
phone book
    -a user can have severl telephone numbers
    -auto complect when typying name
    -show numbers by name
    -show other 4 neighbors 's numbers
    -find person by number
    
*/


class PhoneBook
{
public:
    PhoneBook():_numberByName(), _nameByNumber(){}


    void recorde(const string & name, const string & phoneNumber)
    {
        if(!isValidName(name) || !isValidPhoneNumber(phoneNumber)) throw invalid_argument("name or phone number not valid");
        
        _nameByNumber[phoneNumber] = name;
        _numberByName[name].insert(phoneNumber);
    }
    
    
    vector<string> autoComplete(const string & name, int limitNumber)
    {
        vector<string> names;names.reserve(limitNumber);
        auto it = _numberByName.find(name);
        while(it!=_numberByName.end() && names.size()<limitNumber && it->first[name.size()-1] == name[name.size() -1 ])
        {
            names.push_back(it->first);
            ++it;
        }

        
        return names;
    }
    
    const unordered_set<string> & getNumbersByName(const string & name)
    {
        return _numberByName[name];
    }
    
    vector<string> geNeighborsByName(const string & name)
    {
        deque<string> neighbors;
        auto current = _numberByName.find(name);
        auto it = current;
        while(it!=_numberByName.begin() && neighbors.size()<2)
        {
            --it;
            neighbors.push_front(it->first);
        }
        
        if(it==_numberByName.begin() && neighbors.size()<2)
        {
             neighbors.push_front(it->first);
        }
        
        it = current;
        while(it!=_numberByName.begin() && neighbors.size()<4)
        {
            ++it;
            neighbors.push_back(it->first);
        }
        
        return vector<string>(neighbors.begin(), neighbors.end());
    }
    
    
private:


   
    
    bool isValidName(const string & /*name*/)
    {
        return true;//TODO : lower case only 'a'-'z' no space
    }

    bool isValidPhoneNumber(const string & /*phoneNumber*/)
    {
        return true;//TODO
    }
    
private:
    //PrefixTreeNode _trie;
    map<string, unordered_set<string>> _numberByName;//--> neighber feature is very hard to handle by the trie solution, treemap is better
    unordered_map<string, string> _nameByNumber;
};




int main(int argc, char *argv[])
{
    PhoneBook book;
    book.recorde("a", "1");
    book.recorde("ab", "12");
    book.recorde("abc", "123");
    book.recorde("abcd", "1234");
    book.recorde("abcdef", "123456");
    book.recorde("aa", "11");
    book.recorde("ac", "12");
    book.recorde("ad", "13");
    
    
    const auto & autoComplete = book.autoComplete("abc",5);
    for(const auto & name : autoComplete) cout<<name<<", ";
    cout<<endl;
    
    const auto & neighbors = book.geNeighborsByName("abc");
    for(const auto & name : neighbors) cout<<name<<", ";
    cout<<endl;
    
    
    const auto & numbers = book.getNumbersByName("abcd");
    for(const auto & name : numbers) cout<<name<<", ";
    cout<<endl;
    
    
    return 0;
}
