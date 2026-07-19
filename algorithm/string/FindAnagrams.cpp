#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

static bool equals(const std::vector<int> & left, const std::vector<int> & right)
{
    for(int i = 0; i<26; ++ i)
    {
        if(left[i] != right[i])
            return false;
    }
    return true;
}

std::vector<std::string> findAnagrams(const std::vector<std::string> & words)
{
    std::vector<std::string> anagrames;
    std::vector<std::vector<int>> charDigram(words.size(), std::vector<int>(26, 0));
    for(int i = 0; i<words.size(); ++i)
    {
        for(const auto & c : words[i])
        {
            charDigram[i][c-'a'] ++;
        }
    }//O(N*M)
    
    for(int i = 0; i<words.size(); ++i)
    {
        for(int j = i +1; j<words.size();++j)
        {
            if(equals(charDigram[i], charDigram[j]))
            {
                anagrames.push_back(words[i]);
                anagrames.push_back(words[j]);
            }
        }
    }//O(N^2)
    
    //O(N*M + N^2)
    return anagrames;
}


static std::vector<std::vector<int>> diagram(const std::vector<std::string> & words)
{
    std::vector<std::vector<int>> charDigram(words.size(), std::vector<int>(26, 0));
    for(int i = 0; i<words.size(); ++i)
    {
        for(const auto & c : words[i])
        {
            charDigram[i][c-'a'] ++;
        }
    }//O(N*M)
    return charDigram;
}

std::vector<std::string> findAnagrams_linear(const std::vector<std::string> & words)
{
    std::vector<std::string> anagrames;
    std::vector<std::vector<int>> charDigram=diagram(words); // or we can use std::sort(word.begin(), word.end()); to fingerPrint the words
    
    std::map<std::vector<int>, std::vector<std::string>> diams;
    
    for(int i = 0; i<words.size(); ++i)
    {
        diams[charDigram[i]].push_back(words[i]);
    }//O(N)
    
    for(const auto & diam : diams)
    {
        if(diam.second.size()>=2)
        {
            anagrames.insert(anagrames.end(), diam.second.begin(), diam.second.end());
        }
    }
    
    //O(N*M)
    return anagrames;
}

void test(const std::vector<std::string> & words)
{
    std::cout<<"test: {";
    for(const auto & word : words)
        std::cout<<word<<" ";
        
    std::cout<<" } output : { ";    
    auto results = findAnagrams(words);
    for(const auto & result : results)
        std::cout<<result<<" ";
    
    std::cout<<" }"<<std::endl;
}

int main()
{
    test({"dog", "taste", "hello", "god", "state"});
    test({});
    test({"singleWord"});//{}
    test({"a", "b"});//{}
    test({"a", "a"});//{a a}
    test({"ab", "ba"});//{ab ba}
    test({"a", "ab", "ba"});//{ab ba}
    return 0;
}

