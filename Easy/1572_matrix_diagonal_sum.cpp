//problem link: https://leetcode.com/problems/matrix-diagonal-sum/
#include<vector>
using std::vector;
class Solution {
public:
/*
The problem specifies that the center cell must not be added twice to the answer. If the number of rows
(or columns) is even, no center exists; it only exists if that number if odd.
THe maximum value of the sum is 20000, so 16 bits are enough. If the matrix has 100 rows, 100 columns, and all cells have 100 as their value, then the sum is as follows:
The number of elements in either diagonal is the same as the number of rows (or columns) of the matrix. So,
there are 100 elements in the primary diagonal. Because the number of rows is even and the matrix is
square, there is no center cell. Also, the secondary diagonal has 100 elements, so we can calculate the
sum with the following operation: 100*100*2, which yields 20000
*/
    uint16_t diagonalSum(const vector<vector<int>>& mat) {
        uint16_t answer{};
        const uint8_t size{static_cast<uint8_t>(mat.size())};
        for(uint8_t i{}; i<size; ++i)
            answer+=mat[i][i]+mat[i][mat.size()-1-i];
        return (size & 1) ? answer-mat[size/2][size/2] : answer;    
    }
};
