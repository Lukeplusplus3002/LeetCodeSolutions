//problem link: https://leetcode.com/problems/spiral-matrix/
#include<vector>
using std::vector;

// Solution1: Classic boundary shrinking approach
class Solution1 {
public:
    vector<int> spiralOrder(const vector<vector<int>>& matrix) {
        vector<int> answer;
        // left/right: column indices, top/bottom: row indices
        uint8_t left{}, right{static_cast<uint8_t>(matrix[0].size()-1)};
        size_t top{}, bottom{matrix.size()-1};
        answer.reserve((bottom+1)*(right+1));
        // Traverse while boundaries are valid
        while(top<=bottom && left<=right)
        {
            // If only one row remains
            if(top==bottom)
            {
                for(uint8_t j{left}; j<=right; ++j)
                    answer.push_back(matrix[top][j]);
                break;    
            }
            // If only one column remains
            else if(left==right)
            {
                for(size_t i{top}; i<=bottom; ++i)
                    answer.push_back(matrix[i][left]);
                break;    
            }
            // Traverse outer layer in 4 steps
            else
            {
                // Top row: left to right
                for(uint8_t j{left}; j<=right; ++j)
                    answer.push_back(matrix[top][j]);    
                // Right column: top+1 to bottom-1
                for(size_t i{++top}; i<bottom; ++i)
                    answer.push_back(matrix[i][right]);
                // Bottom row: right to left
                for(uint8_t j{static_cast<uint8_t>(--right+2)}; j-->left;)
                    answer.push_back(matrix[bottom][j]);
                // Left column: bottom-1 to top
                for(size_t i{--bottom+1}; i-->top;)
                    answer.push_back(matrix[i][left]);
                ++left; // Shrink left boundary
            }
        }
        return answer;
    }
};

// Solution2: Layer-by-layer, handles odd/even dimensions
class Solution2 {
public:
    vector<int> spiralOrder(const vector<vector<int>>& matrix) {
        vector<int> answer;
        uint8_t left{};
        size_t top{};
        const uint8_t columnCount{static_cast<uint8_t>(matrix[0].size())};
        const size_t rowCount{matrix.size()};
        answer.reserve(rowCount*columnCount);
        // Traverse layers until center is reached
        while(top<(rowCount+1)/2 && left<(columnCount+1)/2)
        {
            const uint8_t right{static_cast<uint8_t>(columnCount-left)};
            const size_t bottom{rowCount-top};
            // If last remaining row (odd row count)
            if(top==(rowCount+1)/2-1 && rowCount % 2 != 0)
            {
                for(uint8_t j{left}; j<right; ++j)
                    answer.push_back(matrix[top][j]);
                break;    
            }
            // If last remaining column (odd column count)
            else if(left==(columnCount+1)/2-1 && columnCount % 2 != 0)
            {
                for(size_t i{top}; i<bottom; ++i)
                    answer.push_back(matrix[i][left]);
                break;    
            }
            // Traverse outer layer in 4 steps
            else
            {
                // Top row
                for(uint8_t j{left}; j<right; ++j)
                    answer.push_back(matrix[top][j]);    
                // Right column
                for(size_t i{++top}; i<bottom-1; ++i)
                    answer.push_back(matrix[i][right-1]);
                // Bottom row
                for(uint8_t j{right}; j-->left;)
                    answer.push_back(matrix[bottom-1][j]);
                // Left column
                for(size_t i{bottom-1}; i-->top;)
                    answer.push_back(matrix[i][left]);
                ++left; // Shrink left boundary
            }
        }
        return answer;
    }
};

// Solution3: Layer-by-layer, then handle center separately
class Solution3 {
public:
    vector<int> spiralOrder(const vector<vector<int>>& matrix) {
        vector<int> answer;
        size_t left{};
        size_t top{};
        const size_t columnCount{matrix[0].size()};
        const size_t rowCount{matrix.size()};
        answer.reserve(rowCount*columnCount);
        // Traverse all full layers except possibly the center
        while(top<(rowCount+1)/2-1 && left<(columnCount+1)/2-1)
        {
            const size_t right{columnCount-left};
            const size_t bottom{rowCount-top};
            // Top row
            for(size_t j{left}; j<right; ++j)
                answer.push_back(matrix[top][j]);    
            // Right column
            for(size_t i{++top}; i<bottom-1; ++i)
                answer.push_back(matrix[i][right-1]);
            // Bottom row
            for(size_t j{right}; j-->left;)
                answer.push_back(matrix[bottom-1][j]);
            // Left column
            for(size_t i{bottom-1}; i-->top;)
                answer.push_back(matrix[i][left]);
            ++left; 
        }
        // Handle remaining center row/column if needed
        const size_t right{columnCount-left};
        const size_t bottom{rowCount-top};
        if(top!=bottom-1 && left!=right-1)
        {
            // Full layer
            for(size_t j{left}; j<right; ++j)
                answer.push_back(matrix[top][j]);    
            for(size_t i{++top}; i<bottom-1; ++i)
                answer.push_back(matrix[i][right-1]);
            for(size_t j{right}; j-->left;)
                answer.push_back(matrix[bottom-1][j]);
            for(size_t i{bottom-1}; i-->top;)
                answer.push_back(matrix[i][left]);
        }else
        {
            // Only one row or column left
            if(top==bottom-1)
            {
                for(size_t j{left}; j<right; ++j)
                    answer.push_back(matrix[top][j]);
            }else
            {
                for(size_t i{top}; i<bottom; ++i)
                    answer.push_back(matrix[i][left]);
            }
        }
        return answer;
    }
};

// Solution4: Bit manipulation for boundaries, single variable for state
class Solution4 {
public:
    vector<int> spiralOrder(const vector<vector<int>>& matrix) {
        vector<int> answer;
        // shrink factor uses 3 least significant bits, column count uses next 4 bits
        uint8_t shrinkAndColumnCount{static_cast<uint8_t>(matrix[0].size()<<3)};
        const uint8_t area{static_cast<uint8_t>(matrix.size()*(shrinkAndColumnCount>>3))};
        answer.reserve(matrix.size()*(shrinkAndColumnCount>>3));
        // Traverse until all elements are added
        while(answer.size()!=area)
        {
            const uint8_t shrinkCount{static_cast<uint8_t>(shrinkAndColumnCount & 0b111)};
            // Top row
            for(uint8_t i{shrinkCount}; i<=(shrinkAndColumnCount>>3)-1-shrinkCount; ++i)
            {
                answer.push_back(matrix[shrinkCount][i]);
            }
            if(answer.size()==area)
                break;
            // Right column
            for(auto it{matrix.begin()+1+shrinkCount}; it<=matrix.end()-2-shrinkCount; ++it)
            {
                answer.push_back((*it)[(shrinkAndColumnCount>>3)-1-shrinkCount]);
            }
            if(answer.size()==area)
                break;
            // Bottom row
            for(int8_t i{static_cast<int8_t>((shrinkAndColumnCount>>3)-1-shrinkCount)}; i>=shrinkCount; --i)
            {
                answer.push_back(matrix[matrix.size()-1-shrinkCount][i]);
            }
            if(answer.size()==area)
                break;
            // Left column
            for(auto it{matrix.end()-2-shrinkCount}; it>=matrix.begin()+1+shrinkCount; --it)
            {
                answer.push_back((*it)[shrinkCount]);
            }
            ++shrinkAndColumnCount; // Increase shrink factor
        }
        return answer;
    }
};

// Solution5: Special cases for 1/2 rows, otherwise spiral with explicit indices
class Solution5 {
public:
    vector<int> spiralOrder(const vector<vector<int>>& matrix) {
        size_t const numberOfRows{matrix.size()};
        vector<int> answer;
        answer.reserve(numberOfRows*(matrix[0].size()));
        switch(numberOfRows)
        {
            case 1:
                // Single row: left to right
                for(size_t i=0; i<=matrix[0].size()-1; ++i)
                {
                    answer.push_back(matrix[0][i]);
                }
                break;
            case 2:
                // First row: left to right
                for(size_t i=0; i<=matrix[0].size()-1; ++i)
                {
                    answer.push_back(matrix[0][i]);
                }
                // Second row: right to left
                for(size_t i=matrix[0].size()-1; i>=0; --i)
                {
                    answer.push_back(matrix[1][i]);
                    if(i==0)
                    {
                        break;
                    }
                }
                break;
            default:
                // General case: spiral traversal with explicit indices
                size_t firstOfColumn{1}, lastOfColumn{numberOfRows-2}, firstOfRow{}, lastOfRow{matrix[0].size()-1};
                const size_t numberOfElements{numberOfRows*matrix[0].size()};
                while(answer.size()!=numberOfElements)
                {
                    // Top row
                    for(size_t i=firstOfRow; i<=lastOfRow; ++i)
                    {
                        answer.push_back(matrix[firstOfColumn-1][i]);
                    }
                    if(answer.size()==numberOfElements)
                    {
                        break;
                    }
                    ++firstOfRow;
                    --lastOfRow;
                    // Right column
                    for(size_t i=firstOfColumn; i<=lastOfColumn; ++i)
                    {
                        answer.push_back(matrix[i][lastOfRow+1]);
                    }
                    if(answer.size()==numberOfElements)
                    {
                        break;
                    }
                    ++firstOfColumn;
                    --lastOfColumn;
                    // Bottom row
                    for(size_t i=lastOfRow+1; i>=firstOfRow-1; --i)
                    {
                        answer.push_back(matrix[lastOfColumn+2][i]);
                        if(i==0)
                        {
                            break;
                        }
                    }
                    if(answer.size()==numberOfElements)
                    {
                        break;
                    }
                    // Left column
                    for(size_t i=lastOfColumn+1; i>=firstOfColumn-1; --i)
                    {
                        answer.push_back(matrix[i][firstOfRow-1]);
                        if(i==0)
                        {
                            break;
                        }
                    }
                }
        }
        return answer;
    }
};

// Solution6: Iterator-based spiral traversal, shrink boundaries each layer
class Solution6 {
public:
    vector<int> spiralOrder(const vector<vector<int>>& matrix) {
        vector<int> answer;
        answer.reserve(matrix.size()*(matrix[0].size()));
        const size_t area{answer.capacity()};
        auto row{matrix.begin()}; 
        auto column{(*row).begin()};
        uint8_t shrinkCount{};
        // Traverse until all elements are added
        while(answer.size()<area)
        {
            // Top row: left to right
            for(column; column<(*row).end()-shrinkCount; ++column)
                answer.push_back(*column);
            if(answer.size()==area)
                break;
            // Right column: top+1 to bottom-1
            for(++row; row<matrix.end()-1-shrinkCount; ++row)
            {
                column=(*row).end()-1-shrinkCount;
                answer.push_back(*column);
            }
            if(answer.size()==area)
                break;
            // Bottom row: right to left
            for(column=(*row).end()-1-shrinkCount; column>=(*row).begin()+shrinkCount; --column)
                answer.push_back(*column);
            if(answer.size()==area)
                break;    
            // Left column: bottom-1 to top+1
            for(--row; row>matrix.begin()+shrinkCount; --row)
            {
                column=(*row).begin()+shrinkCount;
                answer.push_back(*column);
            }
            ++shrinkCount; // Move to next inner layer
            ++row;
            column=(*row).begin()+shrinkCount;
        }
        return answer;
    }
};
