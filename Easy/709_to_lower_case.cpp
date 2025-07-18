//problem link: https://leetcode.com/problems/to-lower-case/
#include<string>
using std::string;
class Solution {
public:
    string toLowerCase(string s) {
        for(char& letter : s)
        {
            if(letter>=65 && letter<=90)//use ASCII values directly
                letter+=32;
        }
        return s;
    }
};
