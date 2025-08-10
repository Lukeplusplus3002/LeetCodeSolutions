//problem link: https://leetcode.com/problems/robot-bounded-in-circle/
#include<string>
using std::string;
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
class Solution2 {
public:
    bool isRobotBounded(const string& instructions) {
        int8_t x{}, y{};
        //0 is south, 1 is west, 2 is north, and 3 is east
        uint8_t direction{2};//from 0 to 255
        for(const auto &ins : instructions)
        {
            if(ins=='G')
            {
                if(direction % 2!=0)
                {
                    x+=1-2*((direction+1) % 4 != 0);
                }else
                {
                    y+=1-2*(direction % 4 ==0);
                }
                continue;
            }
            direction+=1-2*static_cast<bool>((ins-'R'));
        }

        return direction % 2!=0 || direction % 4==0 || (x==0 && y==0);
    }
};
