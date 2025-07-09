//problem link: https://leetcode.com/problems/can-make-arithmetic-progression-from-sequence/
#include<vector>
#include <algorithm>
using std::vector, std::sort;
class Solution {
public:
    bool canMakeArithmeticProgression(vector<int>& arr) {
        sort(arr.begin(), arr.end());
        const int r{arr[1]-arr[0]};
        const size_t lastIndex{arr.size()-1};
        for(size_t i=2; i<=lastIndex; ++i)
        {
            if(arr[i]-arr[i-1]!=r)
            {
                return false;
            }
        }
        return true;
    }
};//this solution has O(n*log(n)) time complexity
