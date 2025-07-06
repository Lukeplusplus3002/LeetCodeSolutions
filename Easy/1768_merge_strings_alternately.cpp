//problem link: https://leetcode.com/problems/merge-strings-alternately/
#include<string>
using std::string;
class Solution {
public:
    string mergeAlternately(const string &word1, const string &word2) {
        const size_t word1Size{word1.size()}, word2Size{word2.size()};
        string merged(word1Size+word2Size, '\0');//the size of the merged string must be equal to the sum of both words' sizes
        size_t wordIndex{}, mergedIndex{};//wordIndex to access each character of word1 and word2, mergedIndex to access each character of the merged string
        while(wordIndex<word1Size || wordIndex<word2Size)
        {
            if(wordIndex<word1Size)
            {
                merged[mergedIndex++]=word1[wordIndex];
            }
            if(wordIndex<word2Size)
            {
                merged[mergedIndex++]=word2[wordIndex];
            }
            ++wordIndex;
        }
        return merged;
    }
};
