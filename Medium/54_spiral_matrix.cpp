//problem link: https://leetcode.com/problems/spiral-matrix/
#include<vector>
using std::vector;
class Solution1 {
public:
    vector<int> spiralOrder(const vector<vector<int>>& matrix) {
        vector<int> answer;
        //shrink factor uses 3 least significant bits, column count uses next 4 bits,
        //most significant bit unused 
        uint8_t shrinkAndColumnCount{static_cast<uint8_t>(matrix[0].size()<<3)};
        const uint8_t area{static_cast<uint8_t>(matrix.size()*(shrinkAndColumnCount>>3))};
        answer.reserve(matrix.size()*(shrinkAndColumnCount>>3));
        while(answer.size()!=area)
        {
            const uint8_t shrinkCount{static_cast<uint8_t>(shrinkAndColumnCount & 0b111)};
            for(uint8_t i{shrinkCount}; i<=(shrinkAndColumnCount>>3)-1-shrinkCount; ++i)
            {
                answer.push_back(matrix[shrinkCount][i]);
            }
            if(answer.size()==area)
                break;
            for(auto it{matrix.begin()+1+shrinkCount}; it<=matrix.end()-2-shrinkCount; ++it)
            {
                answer.push_back((*it)[(shrinkAndColumnCount>>3)-1-shrinkCount]);
            }
            if(answer.size()==area)
                break;
            for(int8_t i{static_cast<int8_t>((shrinkAndColumnCount>>3)-1-shrinkCount)}; i>=shrinkCount; --i)
            {
                answer.push_back(matrix[matrix.size()-1-shrinkCount][i]);
            }
            if(answer.size()==area)
                break;
            for(auto it{matrix.end()-2-shrinkCount}; it>=matrix.begin()+1+shrinkCount; --it)
            {
                answer.push_back((*it)[shrinkCount]);
            }
            ++shrinkAndColumnCount;
        }
        return answer;
    }
};
class Solution2 {
public:
    vector<int> spiralOrder(const vector<vector<int>>& matrix) {
        size_t const numberOfRows{matrix.size()};
        vector<int> answer;
        answer.reserve(numberOfRows*(matrix[0].size()));
        switch(numberOfRows)
        {
            case 1:
                for(size_t i=0; i<=matrix[0].size()-1; ++i)
                {
                    answer.push_back(matrix[0][i]);
                }
                break;
            case 2:
                for(size_t i=0; i<=matrix[0].size()-1; ++i)
                {
                    answer.push_back(matrix[0][i]);
                }
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
                //operation 0: enter row from first to last | operation 1: enter column from top to bottom | operation 2: enter row from last to first | operation 3: enter column from bottom to top
                size_t firstOfColumn{1}, lastOfColumn{numberOfRows-2}, firstOfRow{}, lastOfRow{matrix[0].size()-1};
                const size_t numberOfElements{numberOfRows*matrix[0].size()};
                while(answer.size()!=numberOfElements)
                {
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
class Solution3 {
public:
    vector<int> spiralOrder(const vector<vector<int>>& matrix) {
        vector<int> answer;
        answer.reserve(matrix.size()*(matrix[0].size()));
        const size_t area{answer.capacity()};
        auto row{matrix.begin()}; 
        auto column{(*row).begin()};
        uint8_t shrinkCount{};
        while(answer.size()<area)
        {
            for(column; column<(*row).end()-shrinkCount; ++column)
                answer.push_back(*column);
            if(answer.size()==area)
                break;
            for(++row; row<matrix.end()-1-shrinkCount; ++row)
            {
                column=(*row).end()-1-shrinkCount;
                answer.push_back(*column);
            }
            if(answer.size()==area)
                break;
            for(column=(*row).end()-1-shrinkCount; column>=(*row).begin()+shrinkCount; --column)
                answer.push_back(*column);
            if(answer.size()==area)
                break;    
            for(--row; row>matrix.begin()+shrinkCount; --row)
            {
                column=(*row).begin()+shrinkCount;
                answer.push_back(*column);
            }
            ++shrinkCount;
            ++row;
            column=(*row).begin()+shrinkCount;
        }
        return answer;
    }
};
