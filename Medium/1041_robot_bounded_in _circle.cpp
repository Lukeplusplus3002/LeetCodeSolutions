//problem link: https://leetcode.com/problems/robot-bounded-in-circle/
#include<string>
using std::string;
//simple solution using enum
class Solution1 {
public:
    bool isRobotBounded(const string instructions) {
        enum class Direction{
            North,
            East,
            South,
            West
        };
        Direction direction{Direction::North};
        int8_t xAxis{}, yAxis{};
        //the following structure is a solution that relies completely on program flow, very easy to follow
        for(const char instruction : instructions)
        {
            if(instruction=='G')
            {
                switch(direction)
                {
                    case Direction::North:
                        ++yAxis;
                        break;
                    case Direction::East:
                        ++xAxis;
                        break;
                    case Direction::West:
                        --xAxis;
                        break;
                    default:
                        --yAxis;            
                }
                continue;
            }
            if(instruction=='L')
            {
                if(direction==Direction::North)
                {
                    direction=Direction::West;
                    continue;
                }
                if(direction==Direction::West)
                {
                    direction=Direction::South;
                    continue;
                }
                if(direction==Direction::South)
                {
                    direction=Direction::East;  
                    continue;
                }  
                if(direction==Direction::East)
                    direction=Direction::North;           
            }else
            {
                if(direction==Direction::North)
                {
                    direction=Direction::East;
                    continue;
                }
                if(direction==Direction::West)
                {
                    direction=Direction::North;
                    continue;
                }
                if(direction==Direction::South)
                {
                    direction=Direction::West;  
                    continue;
                }  
                if(direction==Direction::East)
                    direction=Direction::South;   
            }    
        }
        return direction!=Direction::North || (xAxis==0 && yAxis==0);    
    }
};
//smarter solution using modulo
class Solution2 {
public:
    bool isRobotBounded(const string& instructions) {
        int8_t x{}, y{};
        //0 is south, 1 is west, 2 is north, and 3 is east
        uint8_t direction{2};//from 0 to 255
        /*
        An 8-bit integer works perfectly fine to control the direction of the robot. Notice that there are
        four states (north, east, south, and west) and that an 8-bit integer can have 256 values. 256 is
        a multiple of 4, so four states can fit. For example, consider east and an arithmetic progression:
            a_1=3, d=4, a_64=255
        Remember that d is the common difference. a_64 can be obtained by doing the following:
            a_64=a_1+d*63
            a_64=3+4*63
            a_64=255
        As you can see, the last value can also represent east.
        Another thing to consider is what properties a value has depending on what direction it represents:

        In the following expressions, k is any non-negative integer less or equal than 63.
            **Numbers that represent south are all multiples of 4 (0,4,8,12...,252). They all have the form
            4*k

            **Numbers that represent north are even but not multiples of 4 (2,6,10,14...,254). They all
            have the form 2+4*k, where k is any non-negative integer. Notice that the form can be
            rewritten as 2*(1+2*k); 2 is not a multiple of 4, nor is 1+2*k (it's odd).

            **Numbers that represent west have the form 1+4*k. Notice that if you add 1 to the form, it's
            still not a multiple of 4

            **Numbers that represent east have the form 3+4*k. Notice that if you add 1 to the form, it
            becomes a multiple of 4
        */
        for(const auto &ins : instructions)
        {
            if(ins=='G')
            {
                if(direction % 2!=0)//if this is true, then direction is east or west (odd)
                {
                    //+1 if the direction is east, -1 if it's west
                    x+=1-2*((direction+1) % 4 != 0);
                }else//direction is north or south (even)
                {
                    //+1 if the direction is north, -1 if it's south
                    y+=1-2*(direction % 4 ==0);
                }
                continue;
            }
            //A change of direction occurs here.
            direction+=1-2*(ins=='L');
        }

        return direction % 2!=0 || direction % 4==0 || (x==0 && y==0);
    }
};
//basically the same as solution 2, but using bitwise AND instead of modulo
class Solution3 {
public:
/*
To determine if a number is even or odd, it suffices to check the least significant bit: if it's set,
the number is odd; it's even otherwise. 
To determine if a number is a multiple of 4, it suffices to check the two least significant bits: if
they're both 0, the number is a multiple of 4; otherwise, it is not. Just remember the weight of each
bit if this is not clear: 2^0+2^1+2^2+2^3..., from least significant to most significant left-to-right.
Also, remember that the possible values of any number % 4 (modulo four)  is 0, 1, 2, and 3.
*/
    bool isRobotBounded(const string& instructions) {
        int8_t x{}, y{};
        //0 is south, 1 is west, 2 is north, and 3 is east
        uint8_t direction{2};//from 0 to 255
        for(const auto &ins : instructions)
        {
            if(ins=='G')
            {
                if(direction & 1)
                {
                    x+=1-2*(((direction+1) & 0b11) != 0);
                }else
                {
                    y+=1-2*((direction & 0b11) ==0);
                }
                continue;
            }
            direction+=1-2*(ins=='L');
        }

        return (direction & 1) || (direction & 0b11)==0 || (x==0 && y==0);
    }
};
