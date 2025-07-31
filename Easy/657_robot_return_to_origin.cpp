//problem link: https://leetcode.com/problems/robot-return-to-origin/
#include<string>
using std::string;

//straightforward solution
class Solution1 {
public:
    bool judgeCircle(const string& moves) {
        if(moves.size()%2==0)
        /*
        If the number of moves is odd, it's impossible for the robot to return to the origin. 
        For the robot to return to the origin, the number of left moves must be equal to the number of
        right moves; same goes for the number of up moves and down moves. Knowing this, it's easy to tell
        the following:
            Assuming the robot returns to the origin, then the following is true:
                *If the number of left moves and right moves is odd, the number of moves on the x-axis
                is 2 times an odd number, which is even. If the number of both moves is even, then
                the number of moves on the x-axis is 2 times an even number, which is also even.
                This proposition proves that the number of moves on the x-axis must be even.

                *Using the same logic as the proposition above, it's clear that the number of moves on
                the y-axis must also be even
                
                *If you add both axes' moves to one another, you have 'even + even', which is also even.
        The three propositions prove that the number of moves must be even for the robot to return to
        the origin.        
        */
        {
            short X{}, Y{};
            for(const char& move : moves)
            {
                switch(move)
                {
                    case 'U':
                        ++Y;
                        break;
                    case 'D':
                        --Y;
                        break;
                    case 'L':
                        --X;
                        break;
                    default:
                        ++X;    
                }
            }
            return X==0 && Y==0;
        }else
        {
            return false;
        }        
    }
};
