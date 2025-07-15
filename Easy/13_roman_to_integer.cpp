#include<string>
using std::string;
int romanDigitToInt(const char digit){//helper function
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
class Solution {//the first solution I came up with
public:
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
class Solution {//this performed the best
public:
    int romanToInt(const string &s) {
        int answer{romanDigitToInt(s[0])};
        const size_t lastIndex{s.size()-1};
        size_t i{1};
        for(i; i<lastIndex; ++i)
        {
            const int current{romanDigitToInt(s[i])}, previous{romanDigitToInt(s[i-1])};
            if(previous<current)
            {
                answer+=-2*previous+current+romanDigitToInt(s[i+1]);
                ++i;
                continue;
            }
            answer+=current;
        }
        if(i==lastIndex)
        {
            const int lastDigit{romanDigitToInt(s[lastIndex])}, secondToLastDigit{romanDigitToInt(s[lastIndex-1])};
            if(secondToLastDigit<lastDigit)
            {
                answer+=-2*secondToLastDigit+lastDigit;
            }else
            {
                answer+=lastDigit;
            }
        }
        return answer;
    }
};
