#include<string>
using std::string;
class Solution {
public:
    int romanDigitToInt(const char digit){
        switch(digit)
        {
            case 'I':
                return 1;
            case 'V':
                return 5;   
            case 'X':
                return 10;
            case 'L':
                return 50;
            case 'C':
                return 100;
            case 'D':
                return 500;                    
            case 'M':
                return 1000;
            default:
                return -1;                         
        }    
    }
    int romanToInt(const string &s) {
        int answer{};
        const size_t lastIndex{s.size()-1};
        for(size_t i=0; i<=lastIndex; ++i)
        {
            const char current{s[i]};
            if(i==lastIndex)
            {
                return answer+romanDigitToInt(current);
            }
            const char next{s[i+1]};
            if
            (
                current=='C' && (next=='M' || next=='D') ||
                current=='X' && (next=='C' || next=='L') ||
                current=='I' && (next=='X' || next=='V')
            )
            {
                answer+=-romanDigitToInt(current)+romanDigitToInt(next);
                ++i;
            }else
            {
                answer+=romanDigitToInt(current);
            }
        }
        return answer;
    }
};
