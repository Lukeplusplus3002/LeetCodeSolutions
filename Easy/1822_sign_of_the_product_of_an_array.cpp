//problem link: https://leetcode.com/problems/sign-of-the-product-of-an-array/
#include<vector>
using std::vector;
class Solution {
public:
    int arraySign(vector<int>& nums) {
        bool isNegative{};
        for(const int &num : nums)
        {
            if(num<0)
            {
                isNegative=!isNegative;
            }else if(num==0)
            {
                return 0;
            }
        }
        if(isNegative)
        {
            return -1;
        }else
        {
            return 1;
        }
    }
};
