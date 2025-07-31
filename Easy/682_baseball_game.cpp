//problem link: https://leetcode.com/problems/baseball-game/
#include<vector>
#include<string>
#include<stack>
using std::vector, std::string;
class Solution1 {
public:
    //O(n) space solution using a vector of integers
    /*
    This is the best linear space complexity solution I could come up with.
    Pretty straightforward and easy to understand, to the point that it became boring
    to me (you'll see why when you take a look at the last two solutions).
    */
    int calPoints(const vector<string>& operations) {
        int answer{};
        vector<int> scores;
        for(const string &op : operations)
        {
            //the first character can determine what the operation means
            const char first{op[0]};
            if((first>=48 && first<=57) || first=='-')//checks if the first character is a number or a minus sign
            //if true, then the operation is to add a score directly
            {
                const int score{stoi(op)};
                scores.push_back(score);
                answer+=score;
                continue;
            }
            switch(first)
            {
                case 'C':
                {
                    answer-=scores.back();
                    scores.pop_back();
                    break;
                }
                case 'D':
                {
                    const int doubled{2*scores.back()};
                    answer+=doubled;
                    scores.push_back(doubled);
                    break;
                }
                default://case '+':
                {
                    const int sum{scores.back()+scores[scores.size()-2]};
                    answer+=sum;
                    scores.push_back(sum);
                }
            }
        }
        return answer;
    }
};
using std::stack;
//O(n) space solution using a stack of integers
//The logic is mostly the same as solution 1
class Solution2 {
public:
    int calPoints(const vector<string>& operations) {
        int answer{};
        stack<int> scores;
        for(const string &operation : operations)
        {
            const char first{operation[0]};
            if((first>=48 && first<=57) || first=='-') 
            {
                const int score{stoi(operation)};
                answer+=score;
                scores.push(score);
                continue;
            }
            switch(first)
            {
                case 'C':
                {
                    answer-=scores.top();
                    scores.pop();
                    break;
                }
                case 'D':
                {
                    scores.push(2*scores.top());
                    answer+=scores.top();
                    break;
                }
                default:
                //this block is the reason why the stack approach performed worse than the vector approach
                {
                    const int top{scores.top()};
                    scores.pop();
                    const int newTop{top+scores.top()};
                    answer+=newTop;
                    scores.push(top);
                    scores.push(newTop);
                }
            }
        }
        return answer;
    }
};
using std::to_string;
//O(1) space solution using two pointers
/*
This is the best constant space solution I could come up with. It performed the same as solution 4,
but it's much simpler.

It's worth noting that linear space solutions perform better than constant space solutions for this specific problem
on LeetCode.

The two constant space solutions below modify the input string. Though that may seem unacceptable, it's easy to preserve
the order of the valid numbers and discard the invalid numbers if necessary. However, for the sake of LeetCode, that is
not necessary.
*/
//the structure of all solutions is the same when it comes to program flow.
class Solution3 {
public:
    /*
    The logic here is simple. One pointer (i) is to scan the input string linearly and the other pointer
    (lastValidNumber) points to the last valid number registered. All strings between i and lastValidNumber
    (exclusive) are invalid strings with no meaning (if no "C" is encountered in the input string yet, 
    there are no strings between i and lastValidNumber). As more Cs are encountered, the distance between
    i and lastValidNumber increases (two at a time; one is the string "C" and the other is the discarded
    value in the input string).
    The group of valid scores are registered at the beginning of the input string
    */
    int calPoints(vector<string>& operations) {
        int answer{};
        int lastValidNumber{-1};
        for(size_t i{}; i<operations.size(); ++i)
        {
            string &current{operations[i]};
            const char first{current[0]};
            if((first>=48 && first<=57) || first=='-')
            {
                answer+=stoi(current);
                ++lastValidNumber;//it now points to where the new value must go
                if(lastValidNumber!=i)//to avoid self-swaps
                    /*
                    Place the score next to the previous valid score.
                    The distance between i and lastValidNumber is unchanged, but
                    the number of valid scores increases by one.
                    */
                    swap(operations[lastValidNumber], current);
                continue;
            }
            //a reference to the last score registered
            string &lastNumber{operations[lastValidNumber]};//used in the three remaining cases
            switch(first)
            {
                case 'C':
                {
                    answer-=stoi(lastNumber);
                    //the two clear() calls below are to save space, as the current C and the last score are no longer needed
                    current.clear();
                    lastNumber.clear();
                    /*
                    The distance between i and lastValidNumber increases by two, while the number of valid
                    scores decreases by one
                    */
                    --lastValidNumber;
                    break;
                }    
                case 'D':
                {
                    const int doubled{2*stoi(lastNumber)};
                    answer+=doubled;
                    current=to_string(doubled);//replace the "D" with the new score and then swap
                    ++lastValidNumber;
                    if(lastValidNumber!=i)
                        swap(operations[lastValidNumber], current);
                    /*
                    The distance between i and lastValidNumber remains unchanged, but the number of
                    valid scores increases by one
                    */        
                    break;
                }    
                default:
                {
                    //same logic as case 'D' above
                    const int sum{stoi(lastNumber)+stoi(operations[lastValidNumber-1])};
                    answer+=sum;
                    current=to_string(sum);
                    ++lastValidNumber;
                    if(lastValidNumber!=i)
                        swap(operations[lastValidNumber], current);
                }        
            }
        }
        return answer;
    }
};
//O(1) space solution using leading empty strings logic.
/*
The most complicated solution I came up with, as it was the first algorithm that crossed my mind when trying to create 
an in-place solution. It was a pain and definitely overkill, but taught me a lot. 
*/
class Solution4 {
public:
    /*
    The idea behind this solution is to group invalid strings within the input vector as follows:
        "","","" ... ,"","Cn"
    where "n" is the substring that holds the number of empty strings of the group PLUS one (to account for "Cn"). The
    substring mentioned will be used to indicate where the last valid score is when traveling through the input vector
    right-to-left, which is the only way the last valid score (and the second-to-last valid score for "+") can be found
    for this solution.
    An empty string is created at the position of the last valid score when it is removed by a "C" operation, resulting in its value becoming empty.
    Groups of empty strings can be separated at first and merge afterwards depending on the order of Cs in the input vector. This
    process creates an empty string where a "Cn" was, like this:
            BEFORE                                              AFTER
        
            last valid score removed
                       |
                       |
                       V
     ..."","","","C4","","C2"...                               ..."","","","","","C6"...
    Any time a number from the vector is emptied, two groups of empty strings must merge if next to one another like shown above.

    In this solution, no swapping occurs. I maintain all strings' positions and only modify them in the following cases:

    1-If the operation is "C", then there are two possible courses of action:
        1.1-If what precedes the current "C" is a number, discard it, which results in a group of two invalid strings.
            ... ,"number","C", ...        -->      ... ,"","C2", ... 
        Consequently, if what precedes "number" is another group of empty strings, the 
        newly created group and the second-to-last empty strings group must combine into a single one.
        ... ,"Cx","","C2", ...            -->      ... ,"","","C2+x", ...
        Note that "2+x" is a number indicating the number of leading empty strings from the group PLUS one.

        1.2-If what precedes the current "C" is a "Cn", append "n+2" to the current "C" and make "Cn" empty. Then find the 
        last valid score based on "n+2" and make it empty. If the newly created group of empty strings is next to the
        second-to-last group of empty strings, merge them.

        Regardless of what happens, subtract the invalid score from the answer (which is stored in an int variable).

    2-If the operation is "D", find the last valid score, double it, assign its value to the current "D", and 
    add it to the answer.

    3-If the operation is a number, simply add it to the answer and continue.

    4-If the operation is "+", find the last valid score, save it in a variable, find the second-to-last valid score,
    add it to the last valid score, add the sum to the answer, and assign the value of sum to the current "+".
    This is where indicating the number of invalid strings in a group is crucial, as the following scenario might happen:
        ..."-10","","","","C4","4","+",...
    Thanks to "C4", it's possible to locate "-10".
    Another scenario is this:
        ..."-10","","","","C4","4","","","","","","C6","+"...
    Locating both numbers is only possible by reading how many invalid strings are in each group.        
    */
    int calPoints(vector<string>& operations) {
        int answer{};
        //note that this solution relies heavily on pointer arithmetic. This was just a choice of mine.
        for(string *operation=&operations[0]; operation!=&operations[0]+operations.size(); ++operation)
        {
            string &current{*operation};//I create references to avoid dereferencing pointers too often
            if(current=="C")
            {
                string &prev{(*(operation-1))};
                int append{};//this is where the value that'll be appended to the current "C" is stored
                if(prev[0]!='C')
                {
                    append=2;
                    answer-=stoi(prev);
                    prev.clear();
                    string &secondToLast{*(&prev-1)};
                    if(&prev != &operations[0] && secondToLast[0]=='C')
                    {
                        append+=stoi(secondToLast.substr(1));
                        secondToLast.clear();
                    }
                    current.append(to_string(append));
                    continue;
                }else
                {
                    append=stoi(prev.substr(1))+2;
                    prev.clear();
                    string *const lastNumber{operation-append+1};
                    answer-=stoi(*lastNumber);
                    (*lastNumber).clear();
                    if(lastNumber!=&operations[0] && (*(lastNumber-1))[0]=='C')
                    {
                        append+=stoi((*(lastNumber-1)).substr(1));
                        (*(lastNumber-1)).clear();
                    }
                    current.append(to_string(append));
                }    
                continue;
            }
            int add{};//this is where the value that'll be added to answer is stored. Crucial for all operations except "C"
            if(current=="D")
            {
                string &prev{(*(operation-1))};
                add=(prev[0]=='C') 
                    ? 2*stoi(*(operation-(stoi(prev.substr(1))+1))) 
                    : 2*stoi(prev);
            }else if(current=="+")
            {
                string &prev{(*(operation-1))};
                const string *lastValidNumber{
                    (prev[0]=='C')
                        ? operation-(stoi(prev.substr(1))+1)
                        : &prev
                };
                add=stoi(*lastValidNumber);
                add+=((*(lastValidNumber-1))[0]=='C') 
                    ? stoi(*(lastValidNumber-(stoi((*(lastValidNumber-1)).substr(1))+1))) 
                    : stoi(*(lastValidNumber-1));
            }else
            {
                add=stoi(current);
                answer+=add;
                continue;
            }
            answer+=add;
            current=to_string(add);
        }
        return answer;
    }
};
