// https://leetcode.com/problems/set-matrix-zeroes/
#include<vector>
using std::vector;
class Solution {
public:
    //Constant space solution, which uses the input matrix to set zeroes.
    //First row and column are used to indicate where to put zeroes.
    //A zero in matrix[0][j] indicates that the jth column must be zeroed
    //A zero in matrix[i][0] indicates that the ith row must be zeroed
    void setZeroes(vector<vector<int>>& matrix) {
        // Flags for first row and column zeroing
        bool zeroFirstRow{}, zeroFirstColumn{};
        const size_t lastRowIndex{matrix.size()-1}, lastColumnIndex{matrix[0].size()-1};

        // Check if first row has any zero in the original matrix
        for(size_t j=0; j<=lastColumnIndex; ++j)
        {
            if(matrix[0][j]==0)
            {
                zeroFirstRow=true;
                break;
            }
        }
        // Check if first column has any zero in the original matrix
        for(size_t i=0; i<=lastRowIndex; ++i)
        {
            if(matrix[i][0]==0)
            {
                zeroFirstColumn=true;
                break;
            }
        }
        //Now travel the matrix
        for(size_t i=1; i<=lastRowIndex; ++i)
        {
            for(size_t j=1; j<=lastColumnIndex; ++j)
            {
                //If both matrix[0][j] and matrix[i][0] are already zero, checking the current cell is unnecessary
                if(matrix[0][j]!=0 || matrix[i][0]!=0)
                {
                    if(matrix[i][j]==0)
                    {
                        matrix[i][0]=0;
                        matrix[0][j]=0;
                    }
                }
            }
        }
        // Zero columns based on markers in first row
        for(size_t j=1; j<=lastColumnIndex; ++j)
        {
            if(matrix[0][j]==0)
            {
                for(size_t i=1; i<=lastRowIndex; ++i)
                {
                    matrix[i][j]=0;
                }
            }
        }
        // Zero rows based on markers in first column
        for(size_t i=1; i<=lastRowIndex; ++i)
        {
            if(matrix[i][0]==0)
            {
                for(size_t j=1; j<=lastColumnIndex; ++j)
                {
                    matrix[i][j]=0;
                }
            }
        }
        // Zero first row if needed
        if(zeroFirstRow)
        {
            for(size_t j=0; j<=lastColumnIndex; ++j)
            {
                matrix[0][j]=0;
            }
        }
        // Zero first column if needed
        if(zeroFirstColumn)
        {
            for(size_t i=0; i<=lastRowIndex; ++i)
            {
                matrix[i][0]=0;
            }
        }
    }
};
