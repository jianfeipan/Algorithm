/*
ABCDE 变成 DEFGH 就是平移了一下…然后给一个字典确定某个单词是都有效，要求是恢复全文，
只考虑lower case.

第一个单词找出所有possible shift distance然后第二个用第一个的结果narrow down这些可能的distance…
一直到最后剩下一个就是我们要的…问是不是要读完所有单词,找到剩一个distance程序里的for就break了.


*/

string decode(const string & src, cosnt vector<string> & dict)
{
    
}
