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
class Solution1 {//the first solution I came up with
public:
    int romanToInt(const string &s) {
        int answer{};
        const size_t lastIndex{s.size()-1};
        for(size_t i=0; i<=lastIndex; ++i)
        {
            const char current{s[i]};
            if(i==lastIndex)//if this is true, just add the last digit, as it won't be followed by any other digit
            {
                return answer+romanDigitToInt(current);
            }
            const char next{s[i+1]};
            if
            (//these are the only cases where we subtract the value of the current digit
                current=='C' && (next=='M' || next=='D') ||
                current=='X' && (next=='C' || next=='L') ||
                current=='I' && (next=='X' || next=='V')
            )
            {
                answer+=-romanDigitToInt(current)+romanDigitToInt(next);
                ++i;//skip the next digit, as it has already been processed
            }else
            {
                answer+=romanDigitToInt(current);
            }
        }
        return answer;
    }
};
class Solution2 {//this performed the best. Instead of checking the next digit, we check the previous one
public:
    int romanToInt(const string &s) {
        int answer{romanDigitToInt(s[0])};
        const size_t lastIndex{s.size()-1};
        size_t i{1};
        for(i; i<lastIndex; ++i)
        /*
        note that i can end up being equal to either lastIndex or lastIndex+1 after the loop, depending on whether the last operation was a subtraction (lastIndex+1) or a simple 
        addition (lastIndex).
        */
        {
            const int current{romanDigitToInt(s[i])}, previous{romanDigitToInt(s[i-1])};
            if(previous<current)//only occurs when the previous substracts the current digit
            {
                answer+=-2*previous+current+romanDigitToInt(s[i+1]);
                /*
                subtract the previous digit twice, as it was added once before. Subtract it once to undo the previous addition, and then add current - previous to answer.
                From there, you can add the next digit to answer, as it's impossible that the current digit subtracts the next one. Lastly, move the index two positions forward, as the next digit has already been processed.
                */
                ++i;
                continue;
            }
            answer+=current;//default case, just add the current digit
        }
        if(i==lastIndex)//if this is true, we have one last digit to process
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
