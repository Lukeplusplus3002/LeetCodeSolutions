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
//here's another solution, much easier to read and just as efficient
class Solution {
public:
    bool isMonotonic(const vector<int>& nums) {
        bool increasing{1}, decreasing{1};
        for(size_t i=1; i<nums.size(); ++i)
        {
            if(nums[i-1]-nums[i] > 0)
            {
                increasing=false;
                if(!decreasing)//early exit when both are false
                {
                    break;
                }
            }else if(nums[i-1]-nums[i] < 0)
            {
                decreasing=false;
                if(!increasing)//another early exit case
                {
                    break;
                }
            }
        }
        return increasing || decreasing;
    }
};
