//problem link: https://leetcode.com/problems/can-make-arithmetic-progression-from-sequence/
#include<vector>
#include <algorithm>
using std::vector, std::sort;
//the solution below has O(n*log(n)) time complexity due to sorting. Not the best solution 
//performance-wise, but very readable
class Solution {
public:
    bool canMakeArithmeticProgression(vector<int>& arr) {
        sort(arr.begin(), arr.end());
        const int r{arr[1]-arr[0]};
        const size_t lastIndex{arr.size()-1};
        for(size_t i=2; i<=lastIndex; ++i)
        {
            if(arr[i]-arr[i-1]!=r)
            {
                return false;
            }
        }
        return true;
    }
};
//the solution below has O(n) time complexity. Performs the best, but a bit hard to read
using std::swap;
class Solution {
public:
/*
    FORMULA USED
    a_i=a_0+diff*i, where a_i is the ith term of the progression, diff is the common difference, 
    a_0 is the first term, and i is the index of a_i
*/
    bool canMakeArithmeticProgression(vector<int>& arr) {
        const size_t lastIndex{arr.size()-1};
        int &min{arr[0]}, &max{arr[lastIndex]};//the lowest term is meant to be in index 0, while 
        //the greatest term is meant to be in the last index
        
        for(int &current : arr)
        {
            if(current<min)
            {
                swap(current, min);
            }else if(current>max)
            {
                swap(current, max);
            }
        }
        //by this point, min actually holds the lowest value, while max actually holds the greatest value
        if((max-min) % lastIndex !=0)
        //if diff isn't a whole number, an arithmetic progression is impossible 
        //see diff declaration below if the comment above is confusing
        {
            return false;
        }
        const int diff{static_cast<int>((max-min)/lastIndex)};
        if(diff==0)//this means all elements of the array are the same
        {
            return true;
        }
        size_t i{1};
        while(i<lastIndex)
        /*
            I decided not to use a for loop because I just want to 
            increment i when it becomes the index of a number that's 
            in its correct position
        */
        {
            int &current{arr[i]};
            /*
            All operations in this loop are just derived from the formula 
            I wrote at the beginning of the program (a_i=a_0+diff*i). 
            Keep in mind: the reference "current" represents a_i and the reference 
            "min" represents a_0
            */
            if((current-min) % diff != 0)//this is true when you try to find the index of 
            //a number that can't mathematically fit in the progression
            {
                return false;
            }
            const size_t actualIndex{static_cast<size_t>((current-min)/diff)};
            //actualIndex is the position in which "current" must sit within the progression, 
            //while "i" is where "current" is currrently sitting
            if(i != actualIndex)
            {
                if((arr[actualIndex]-min)/diff != actualIndex)
                /*
                by this point, "current" needs to be in position "actualIndex", but if 
                the number that's in actualIndex is already in its correct position, 
                you can't swap. If you can't swap, it means you have two numbers that 
                must sit in the same position, so the array is not an arithmetic 
                progression
                */
                {
                    swap(current, arr[actualIndex]);
                }else
                {
                    return false;
                }
            }else
            {
                ++i;
            }
        }
        return true;
    }
};
