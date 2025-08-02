//problem link: https://leetcode.com/problems/find-winner-on-a-tic-tac-toe-game/
#include<array>
#include<vector>
#include<string>
using std::array, std::vector, std::string;
//simple, readable, and efficient solution
class Solution {
public:
    string tictactoe(const vector<vector<int>>& moves) {
        //I use std::array because this problem can entirely be solved using fixed-size containers
        std::array<std::array<char, 3>, 3> grid{};//initialized with null character '\0'
        bool Aturn{1};
        for(const vector<int> &move : moves)
        {
            grid[move[0]][move[1]]=(Aturn) ? 'X' : 'O';
            Aturn=!Aturn;//X first, then O, then X, and so on.
        }
        constexpr std::array<char, 3> xs{'X','X','X'};
        constexpr std::array<char, 3> os{'O','O','O'};
        for(size_t i{}; i<3; ++i)
        {
            const std::array<char, 3> &row=grid[i];//a reference to the current row
            if(row==xs || row==os)
                return (row[0]=='X') ? "A" : "B";
        }
        for(size_t i{}; i<3; ++i)
        {
            const char top{grid[0][i]};//the top box of the current column
            //the first expression is necessary in case the column has three null characters
            if(top!='\0' && top==grid[1][i] && top==grid[2][i])
                return (top=='X') ? "A" : "B";
        }
        const char center{grid[1][1]};
        if(center!='\0' && ((center==grid[0][0] && center==grid[2][2]) || (center==grid[0][2] && center==grid[2][0])))//check two diagonals
            return (center=='X') ? "A" : "B";
        return (moves.size()==9) ? "Draw" : "Pending";
    }    
};
