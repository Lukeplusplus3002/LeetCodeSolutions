//problem link: https://leetcode.com/problems/move-zeroes/
#include<vector>
using std::vector, std::swap; 
class Solution {
public:
    void moveZeroes(vector<int>& nums) {
        size_t zeroes{1}, i{};//'zeroes' represents the number of zeroes encountered. Meaningful when at least one zero is in the vector.
        const size_t sizeOfNums{nums.size()};
        //find the first zero in nums
        for(i; i<sizeOfNums; ++i)
        {
            if(nums[i]==0)
            {
                break;
            }
        }
        for(i; i<sizeOfNums-1; ++i)
        {
            int &currentIPlusOne{nums[i+1]};
            if(currentIPlusOne==0)
            {
                ++zeroes;
            }else
            {
                swap(currentIPlusOne, nums[i-zeroes+1]);//swap the element after nums[i] with the first zero of the array
            }
        }
    }
};
