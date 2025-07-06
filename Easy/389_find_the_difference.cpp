//problem link: https://leetcode.com/problems/find-the-difference/
#include<string>
using std::string;
class Solution {
public:
    char findTheDifference(const string &s, const string &t) {
        const size_t sizeOfS{s.size()};
        unsigned int sumOfS{}, sumOfT{};//these two variables are for adding each character of both strings with one another
        for(size_t i=0; i<sizeOfS; ++i)
        {
            sumOfS+=s[i];
            sumOfT+=t[i];
        }
        sumOfT+=t[sizeOfS];
        return sumOfT-sumOfS;//just return the difference between both sums, which is the ASCII value of the added character
    }
};
