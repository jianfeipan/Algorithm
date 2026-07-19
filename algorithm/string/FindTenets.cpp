static bool isTenet(const std::string & left, const std::string & right)
{
    
    if(left.size()!=right.size())
        return false;
    
    for(int i = 0; i<left.size(); ++i )
    {
        if(left[i] != right[right.size() - i -1])
            return false;
    }
    return true;
}

#include <iostream>
#include <string>
#include <vector>


std::vector<std::string> findTernets(const std::vector<std::string> & words)
{
    std::vector<std::string> tenets;
    
    for(int i = 0; i<words.size(); ++i)
    {
        for(int j = i +1; j<words.size();++j)
        {
            if(isTenet(words[i], words[j]))
            {
                tenets.push_back(words[i]);
                tenets.push_back(words[j]);
            }
        }
    }
    
    
    return tenets;
}

void test(const std::vector<std::string> & words)
{
    std::cout<<"test: {";
    for(const auto & word : words)
        std::cout<<word<<" ";
        
    std::cout<<" } output : { ";    
    auto results = findTernets(words);
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
