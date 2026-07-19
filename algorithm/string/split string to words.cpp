int main()
{
    //cout<< "cleaned :  " << removeUselessParentheses("((a+b)*c) + ((a+b) + c/(d + s))") <<endl;
    
    string input("this is a test, are you happy to be here? yes!");
    
    {   
        string buffer;
        for(char c : input)
        {
            if(c-'a'>=0 && c-'a'<=25)
            {
                buffer+=c;
            }
            else if(buffer.empty())
            {
                cout<< buffer<<endl;
                buffer.clear();
            }
        }
    }
    {
    istringstream iss(input);
    string buffer;
    while(iss>>buffer) cout<<buffer<<endl;
    
    }
    return 0;
}
