

#include <algorithm>
#include <functional>
#include <iostream>
#include <list>
#include <memory>
#include <stdio.h>
#include <string.h>
#include <unordered_map>
#include <vector>
#include <stack>
#include <unordered_set>
#include <stdexcept>

using namespace std;

/*
phone book
    -a user can have severl telephone numbers
    -auto complect when typying name
    -show numbers by name
    -show other 4 neighbors 's numbers
    -find person by number
    
*/


struct PrefixTreeNode
{
    PrefixTreeNode():numbers(), next(26), parent(nullptr){}
    unordered_set<string> numbers;
    vector<unique_ptr<PrefixTreeNode>> next;   
    PrefixTreeNode * parent;
};

class PhoneBook
{
public:
    PhoneBook():_trie(), _nameByNumber(){}


    void recorde(const string & name, const string & phoneNumber)
    {
        if(!isValidName(name) || !isValidPhoneNumber(phoneNumber)) throw invalid_argument("name or phone number not valid");
        
        _nameByNumber[phoneNumber] = name;
        get(name).numbers.insert(phoneNumber);
    }
    
    
    vector<string> autoComplete(const string & name, int limitNumber)
    {
        vector<string> names;
        
        auto & current = get(name);
        dfsVisit(current, name, names, limitNumber);
        
        return names;
    }
    
    const unordered_set<string> & getNumbersByName(const string & name)
    {
        return get(name).numbers;
    }
    
    vector<string> geNeighborsByName(const string & name)
    {
        //this is tricky, it we want to get last and next names, we need track back to the parent node
        vector<string> neighbers;
        auto & current = get(name);

        //last two neighbers
        auto * parent = current.parent;
        string trackBackStr = name.substr(0, name.size() - 1);
        char currentletter = trackBackStr[trackBackStr.size() -1 ];
        
        for(int i = currentletter - 'a'-1; i>=0; --i)
        {
            if(parent->next[i])
                dfsVisit(*parent->next[i], trackBackStr.substr(0, trackBackStr.size() - 1), neighbers, 2);
        }
        
        
        while(neighbers.size()<2 && parent)
        {
            currentletter = trackBackStr[trackBackStr.size() -1 ];
            for(int i = 25; i>=0 && neighbers.size()<4; --i)
            {
                if(i != currentletter-'a' && parent->next[i])
                    dfsVisit(*parent->next[i], trackBackStr, neighbers, 2);
            }
            parent = parent->parent;
            trackBackStr = trackBackStr.substr(0, trackBackStr.size() - 1);

        }
        
        //nextTwoNeighbers
        dfsVisit(current, name, neighbers, 4);
        
        return neighbers;
    }
    
    
private:

    void dfsVisit(PrefixTreeNode & node, string currentTyping, vector<string> & names, size_t limit)
    {
        if(names.size() >= limit) return;
        
        if(!node.numbers.empty()) names.push_back(currentTyping);
        for(size_t i = 0; i<node.next.size(); ++i)
        {
            if(node.next[i])
            {
                string nextTyping(currentTyping);
                nextTyping += ('a'+i);
                dfsVisit(*node.next[i], nextTyping, names, limit);
            }
        }
    }

    PrefixTreeNode & get(const string & name)
    {
        PrefixTreeNode * current = &_trie;
        for(char c : name)
        {
            if(!current->next[c-'a'])
            {
                current->next[c-'a'].reset(new PrefixTreeNode());
                current->next[c-'a']->parent = current;
            }
            current = current->next[c-'a'].get();
        }
        
        return *current;
    }
    
    bool isValidName(const string & /*name*/)
    {
        return true;//TODO : lower case only 'a'-'z' no space
    }

    bool isValidPhoneNumber(const string & /*phoneNumber*/)
    {
        return true;//TODO
    }
    
private:
    PrefixTreeNode _trie;
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
    
    
    const auto & autoComplete = book.autoComplete("ab",5);
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
