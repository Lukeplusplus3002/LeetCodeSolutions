//problem link: https://leetcode.com/problems/repeated-substring-pattern/
#include<string>
using std::string, std::string_view;
class Solution {
public:
    bool repeatedSubstringPattern(const string &s) {
        const size_t sizeOfS{s.size()};
        for(size_t groupOf=sizeOfS/2; groupOf>=1; --groupOf)//groupOf represents the number of characters of the possibly repeated group. For example, if the string is "abcdeabcde", groupOf will be 5, as "abcde" is a single group. I evaluate larger groups first (as they're faster to analyze)
        {
            if(sizeOfS % groupOf == 0)//if groupOf is not a divisor of sizeOfS, a string of size 'groupOf' repeated itself can't mathematically fit in the string 's'
            {
                const string_view group{&s[0], groupOf};//the first group is the one I use to verify subsequent groups
                bool isRepeated{1};//becomes false when two groups don't match
                for(size_t i=groupOf; i<=sizeOfS-groupOf; i+=groupOf)//sizeOfS-groupOf is the maximum valid index 'i' can take
                {
                    const string_view comparisonGroup{&s[i], groupOf};
                    if(group!=comparisonGroup)
                    {
                        isRepeated=false;
                        break;
                    }
                }
                if(isRepeated)
                {
                    return true;
                }
            }
        }
        return false;//all possible groups are analyzed. If none of them can form a repeated string, false is returned
    }
};

//here's another solution using std::string::find. Performs worse, but it's also clean and valid
class Solution {
public:
    bool repeatedSubstringPattern(const string &s) {
        const size_t sizeOfS{s.size()};
        for(size_t groupOf=sizeOfS/2; groupOf>=1; --groupOf)
        {
            if(sizeOfS % groupOf == 0)
            {
                const string_view group{&s[0], groupOf};
                bool isRepeated{1};
                for(size_t i=groupOf; i<=sizeOfS-groupOf; i+=groupOf)
                {
                    if(s.find(group, i)!=i)
                    {
                        isRepeated=false;
                        break;
                    }
                }
                if(isRepeated)
                {
                    return true;
                }
            }
        }
        return false;
    }
};
