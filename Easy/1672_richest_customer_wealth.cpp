//problem link: https://leetcode.com/problems/richest-customer-wealth/
#include<vector>
using std::vector;
class Solution {
public:
//Each person can have a maximum wealth of 5000 due to the problem's constraints. This is because there
//is a maximum of 50 banks, and each bank account can hold up to 100. 13 bits are enough to represent 
//values up to 5000.
    uint16_t maximumWealth(const vector<vector<int>>& accounts) {
        uint16_t maxWealth{};
        for(const auto &individual : accounts)
        {
            uint16_t accWealth{};
            for(const int &money : individual)
            {
                accWealth+=money;
            }
            if(accWealth>maxWealth)
                maxWealth=accWealth;
        }
        return maxWealth;
    }
};
