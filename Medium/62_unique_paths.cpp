#include<vector>
#include<cmath>
using std::vector;
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
class Solution2 {
public:
    //Most efficient solution: a one-liner. O(m+n) time complexity, O(1) space complexity
    /*
        This is a solution that uses the combinatorics formula:
            (m+n-2)!/((n-1)!*(m-1)!)
        All paths have n-1 steps to the right, m-1 steps downwards. Different paths are just different
        sequences of steps (right and down steps taken in different order). So, to count the number of unique paths, you just need to compute the following:
            -Total number of steps: m+n-2
            -Number of times steps to the right repeat: n-1
            -Number of times steps downwards repeat: m-1
        It's basically asking how many ordered sets can represent the robot's path, with n-1 steps
        right and m-1 steps down.
        If you find this confusing, pick up a book on discrete math that talks about combinatorics,
        that'll fix your confusion. Once you internalize combinatorics, this exercise is easy.         
    */
    int uniquePaths(const int& m, const int& n) {
        //The +0.5 is due to floating-point arithmetic imprecision.
        //This algorithm works as long as the expression next to +0.5 has an accuracy of +-0.5
        return std::tgamma(m+n-1)/(std::tgamma(n)*std::tgamma(m))+0.5;
    }
};
