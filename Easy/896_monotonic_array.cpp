#include<vector>
using std::vector;
class Solution {
public:
    bool isMonotonic(const vector<int>& nums) {
        const int &first{nums[0]};
        const size_t lastIndex{nums.size()-1};
        if(first==nums[lastIndex])//all elements must be equal if this expression returns true
        {
            for(const int &current : nums)
            {
                if(current != first)
                {
                    return false;
                }
            }
            return true;
        }
        const bool sign{first-nums[lastIndex] > 0};//sign is 0 when the array must be monotone increasing
        //sign is 1 when the array must be monotone decreasing
        for(size_t i=0; i<lastIndex; ++i)
        {
            if(nums[i]-nums[i+1] > 0  !=  sign  &&  nums[i] != nums[i+1])
            {
                return false;
            }
        }
        return true;
    }
};
