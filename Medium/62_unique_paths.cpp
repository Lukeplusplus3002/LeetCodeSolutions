#include<vector>
#include<array>
using std::vector, std::array;
class Solution1 {
public:
//O(m*n) time complexity, O(n) space complexity. Extremely readable and short
    int uniquePaths(const int& m, const int& n) {
        //The grid is traveled one row at a time, with the vector row being the current row
        //Notice that the first row is just n 1s, which is the initial value of the vector row
        std::vector<int> row(n, 1);
        for(int i{1}; i<m; ++i)
        {
            //travel all cells from the current row
            for(int j{1}; j<n; ++j)
                row[j]=row[j]+row[j-1];
            /*
                In this algorithm, current cell=cell above+preceding cell. Notice that "cell above"
                is just the old value of the current cell. So, in this algorithm, each cell is updated
                by adding old value with preceding value.
            */
        }
        return row[n-1];//return the last cell of the last row
    }
};
