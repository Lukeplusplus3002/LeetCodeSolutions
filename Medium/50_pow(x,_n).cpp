//problem link: https://leetcode.com/problems/powx-n/
#include <cstdint>
class Solution {
public:
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
