//problem link: https://leetcode.com/problems/find-the-index-of-the-first-occurrence-in-a-string/
#include<string>
using std::string, std::string_view;
class Solution {
public:
    int strStr(const string &haystack, const string &needle) {//no need to modify the parameters
        const size_t sizeOfNeedle{needle.size()};
        if(sizeOfNeedle>haystack.size())
        {
            return -1;
        }
        size_t i{};//index for each character of haystack
        const size_t lastIndex{haystack.size()-sizeOfNeedle};//greatest valid index i can be
        for(i; i<=lastIndex; ++i)
        {
            const string_view haystackWord{&haystack[i], sizeOfNeedle};//use of string_view (a string reference) to avoid creating copies
            if(haystackWord==needle)
            {
                return i;
            }
        }
        return -1;
    }
};
/*
The function below also works for this problem, but it defeats the purpose of learning.
class Solution {
public:
    int strStr(string haystack, string needle) {
        return haystack.find(needle);
    }
};
*/
