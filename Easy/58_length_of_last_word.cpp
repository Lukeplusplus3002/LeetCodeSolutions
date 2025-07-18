//problem link: https://leetcode.com/problems/length-of-last-word/
#include<string>
using std::string;
class Solution {
public:
    int lengthOfLastWord(const string& s) {
        for(size_t i=s.size(); i-->1; )
        /*
        travel through string backwards using index i
        notice how i starts being s.size() but becomes s.size()-1, the string's last index,
        after the first condition check. Also, note that checking the first character
        is not necessary
        */
        {
            if(s[i]!=' ')
            {
                return i-s.rfind(' ', i-1);
                /*
                    find the difference between the position of the last non-space character
                    with the position of the last space character until i-1.
                    If no space character precedes i, s.rfind() will return -1,
                    which stills returns the correct value mathematically
                */
            }
        }
        return 1;
        /*
        if program flow reaches this point, then there's a single
        non-space character followed by s.size()-1 spaces
        */
    }
};
