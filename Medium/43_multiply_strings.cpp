// https://leetcode.com/problems/multiply-strings/
#include<string>
#include<string_view>
using std::string, std::string_view;
//I'd like to implement a Fast Fourier Transform algorithm in the future, which is, in theory, faster than
//Solution1 in terms of time complexity. It's overkill for LeetCode but worth knowing
class Solution1 {
public:
    string multiply(const string& num1, const string& num2) {
        if(num1=="0" || num2=="0")
            return "0";
        const size_t minSize{(num1.size()>num2.size()) ? num2.size() : num1.size()}, maxSize{(minSize==num2.size()) ? num1.size() : num2.size()};
        const string &longer{(maxSize==num1.size()) ? num1 : num2}, &shorter{(minSize==num2.size()) ? num2 : num1};
        //note that the answer has either maxSize+minSize or maxSize+minSize-1 digits, so I prealocate the largest case possible
        string answer(maxSize+minSize, '\0');
        unsigned int carry{};//this is used until the end of the algorithm
        /*
            The idea is to repeatedly extract two numbers from num1 and num2, starting from the end of both. For example, if the
            input numbers are 123456 and 789, the extraction is as follows:
                1-6 and 9
                2-56 and 89
                3-456 and 789
            Once the shorter number is completely extracted, continue extracting the longer number leftwards. Both extracted
            numbers' sizes must mach, so the extraction process goes on as follows:
                4-345 and 789
                5-234 and 789
                6-123 and 789
            Once the algorithm hits the start of the longer number, continue on as follows:
                7-12 and 78
                8-1 and 7
            For this example, those are all the extractions that must be performed. 
            Once we know how the extractions happen, we now need to know how the cross multiplication happens. Starting
            with the 0th digit of one extracted number and the last digit of the other, multiply both, then proceed to
            multiply the 1th digit and the second-to-last digit; this goes on until the last digit of the first number
            is multiplied with the first digit of the other number. All of this is done in such a way that the
            multiplications are added with one another. If there is carry, add it to the multiplications.
            Once the cross multiplication is complete, extract the carry and insert the least significant digit of the
            product into answer.
            The 0th digit of answer might be zero depending on the last carry.             
        */
        for(size_t c{1}; c<minSize; ++c)
        {
            const string_view lRow{longer.data()+maxSize-c, c}, sRow{shorter.data()+minSize-c, c};
            unsigned int crossProduct{carry};
            for(size_t i{}; i<c; ++i)
                crossProduct+=(lRow[i]-'0')*(sRow[c-1-i]-'0');
            carry=crossProduct/10;
            answer[maxSize+minSize-c]=crossProduct-carry*10+'0';
        }
        for(size_t digit{answer.size()-minSize+1}; digit-->minSize;)
        {
            const string_view lRow{longer.data()+digit-minSize, minSize};
            unsigned int crossProduct{carry};
            for(size_t i{}; i<minSize; ++i)
                crossProduct+=(lRow[i]-'0')*(shorter[minSize-1-i]-'0');
            carry=crossProduct/10;
            answer[digit]=crossProduct-carry*10+'0';    
        }
        for(size_t digit{minSize}; digit-->1;)
        {
            const string_view lRow{longer.data(), digit}, sRow{shorter.data(), digit};
            unsigned int crossProduct{carry};
            for(size_t i{}; i<digit; ++i)
                crossProduct+=(lRow[i]-'0')*(sRow[digit-1-i]-'0');
            carry=crossProduct/10;
            answer[digit]=crossProduct-carry*10+'0';    
        }
        if(carry==0)
            return answer.substr(1);
        else
            answer[0]=carry+'0';        
        return answer;
    }
};
