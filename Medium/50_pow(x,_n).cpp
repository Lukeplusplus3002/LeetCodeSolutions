//problem link: https://leetcode.com/problems/powx-n/
#include <cstdint>
//short and standard solution. I came up with it in my second try (once I understood the logic behind the standard solution)
class Solution1 {
public:
/*
    This solution is about treating the exponent as the sum of powers of two (2^0 + 2^1 + 2^2...).
    For example, x^13 can be interpreted as (x^8)(x^4)(x^1). To do that, you need to take into account the 
    exponent in its binary form; 13, for example, is 100010001. So, what this algorithm does is traveling the
    individual bits of the exponent from least significant bit to most significant bit. Regardless of the
    state of the current bit, x is always multiplied by itself on each iteration, so it starts being x^1 and
    then x^2, x^4, x^8, etc. This maps the binary representation of the exponent perfectly. Only when the
    current bit of the exponent is set do you multiply answer by x to the power of whatever exponent it
    currently has.
*/
    double myPow(double x, const int& n) {
        unsigned int exp{static_cast<unsigned int>((n<0) ? ((n==-2147483648) ? 2147483648 : -n) : n)};
        if(n<0)
            x=1/x;
        double answer{1.0};    
        while(exp>0)
        {
            if(exp & 1)
                answer*=x;
            x*=x;
            exp>>=1;
        }
        return answer;    
    }
};
class Solution2 {
public:
//This is the first algorithm I came up with. It's less readable but still does the job well.
    double myPow(double x, const int& n) {    
        if(n==1)
            return x;
        else if(n==-1)
            return 1/x;
        else if(n==0)
            return 1;
        //N takes the unsigned version of n. Notice that -1 times n is invalid if n is INT_MIN            
        const unsigned int N{static_cast<unsigned int>((n<0) ? ((n==-2147483648) ? 2147483648 : -n) : n)};
        if(n<0)//to avoid creating separate code when n<0
            x=1/x;
        const double square{x*x};
        double answer{square};
        uint64_t answerExp{2};//uint64_t to avoid integer overflow when adding it to another integer
        if(N % 2 == 1)//start with x^3 if the exponent is odd
        {
            answer=answer*x;
            ++answerExp;
        }
        while(true)
        {
            double power{square};//this is what multiplies answer
            uint64_t powerExp{2};//the exponent of the variable power
            //since answer is itself times power, its resulting exponent is its initial exponent plus the exponent of
            //the variable power. The resulting exponent can never exceed N
            while(answerExp+powerExp<=N)
            {
                answer=answer*power;
                answerExp+=powerExp;
                power=power*power;
                powerExp=powerExp*2;
            }
            //if the condition below is false, start again by multiplying answer with the square of x, then x^4, x^8, and so on
            if(answerExp==N)
                break;
        }
        return answer;    
    }
};
