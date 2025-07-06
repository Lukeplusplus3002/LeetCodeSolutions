//problem link: https://leetcode.com/problems/valid-anagram/
#include<string>
using std::string;
class Solution {
public:
    bool isAnagram(const string &s, const string &t) {//no need to modify parameters
        const size_t sizeOfBoth{s.size()};//meant to be the size of both strings if they're anagrams with one another
        if(sizeOfBoth!=t.size())
        {
            return false;
        }
        int az[26]{};//this controls each character (from a to z) frequency in both strings. If a character appears in 's', the corresponding index increases by one; in contrast, if a character appears in 't', its corresponding index decreases by one. In the end, if both strings are anagrams, this must end up being an array of zeroes. Note that index 0 corresponds to character 'a', while index 25 corresponds to character 'z'
        for(size_t i=0; i<sizeOfBoth; ++i)
        {//see ASCII table to understand this
            ++az[s[i]-'a'];
            --az[t[i]-'a'];
        }
        for(int &letter : az)
        {
            if(letter!=0)
            {
                return false;
            }
        }
        return true;
    }
};
