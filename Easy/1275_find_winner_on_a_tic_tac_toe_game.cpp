//problem link: https://leetcode.com/problems/find-winner-on-a-tic-tac-toe-game/
#include<array>
#include<vector>
#include<string>
#include<bitset>
using std::array, std::vector, std::string;
//simple, readable, and efficient solution
class Solution1 {
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
//Solution that uses std::bitset. Not very readable, but fun and decently efficient
class Solution2 {
public:
    string tictactoe(const vector<vector<int>>& moves) {
        std::bitset<18> grid{};
        bool bTurn{};
        /*
        00 means empty cell
        01 means O
        10 means X
        */
        for(const auto &move: moves)
        {
            grid.set(move[0]*6+move[1]*2+bTurn);
            bTurn=!bTurn;
        }
        //try to determine winner
        
        //check rows
        for(uint8_t i{}; i<3; ++i)
        {
            if(grid[i*6]!=grid[i*6+1] && grid[i*6]==grid[i*6+2] && grid[i*6]!=grid[i*6+3] && grid[i*6]==grid[i*6+4] && grid[i*6]!=grid[i*6+5])
                return (grid[i*6]==0b1) ? "A" : "B";
        }
        //check columns
        for(uint8_t i{}; i<3; ++i)
        {
            if(grid[i*2]!=grid[i*2+1] && grid[i*2]==grid[i*2+6] && grid[i*2]!=grid[i*2+7] && grid[i*2]==grid[i*2+12] && grid[i*2]!=grid[i*2+13])
                return (grid[i*2]==0b1) ? "A" : "B";
        }
        //check diagonals
        if(grid[8]!=grid[9] && ((grid[8]==grid[0] && grid[9]==grid[1] && grid[8]==grid[16] && grid[9]==grid[17]) || (grid[8]==grid[4] && grid[9]==grid[5] && grid[8]==grid[12] && grid[9]==grid[13])))
            return (grid[8]==0b1) ? "A" : "B";
        return (moves.size()==9) ? "Draw" : "Pending";    
    }
};
