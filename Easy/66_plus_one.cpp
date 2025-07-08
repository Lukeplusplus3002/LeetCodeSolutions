//problem link: https://leetcode.com/problems/plus-one/
#include<vector>
using std::vector;
class Solution {
public:
    vector<int> plusOne(vector<int>& digits) {
        for(size_t i=digits.size(); i-->0; )
        {
            int &digit{digits[i]};
            if(digit!=9)
            {
                ++digit;
                return digits;
            }else
            {
                digit=0;
            }
        }
        digits.push_back(0);
        digits[0]=1;
        return digits;
    }
};
