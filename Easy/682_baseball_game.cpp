#include<vector>
#include<string>
#include<stack>
using std::vector, std::string;
//O(n) space solution using a vector of integers
class Solution1 {
public:
    int calPoints(const vector<string>& operations) {
        int answer{};
        vector<int> scores;
        for(const string &op : operations)
        {
            const char first{op[0]};
            if((first>=48 && first<=57) || first=='-')
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
                default:
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
class Solution3 {
public:
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
                ++lastValidNumber;
                if(lastValidNumber!=i)
                    swap(operations[lastValidNumber], current);
                continue;
            }
            string &lastNumber{operations[lastValidNumber]};
            switch(first)
            {
                case 'C':
                {
                    answer-=stoi(lastNumber);
                    current.clear();
                    lastNumber.clear();
                    --lastValidNumber;
                    break;
                }    
                case 'D':
                {
                    const int doubled{2*stoi(lastNumber)};
                    answer+=doubled;
                    current=to_string(doubled);
                    ++lastValidNumber;
                    if(lastValidNumber!=i)
                        swap(operations[lastValidNumber], current);    
                    break;
                }    
                default:
                {
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
//O(1) space solution using leading empty strings logic
class Solution4 {
public:
    int calPoints(vector<string>& operations) {
        int answer{};
        for(string *operation=&operations[0]; operation!=&operations[0]+operations.size(); ++operation)
        {
            string &current{*operation};
            if(current=="C")
            {
                string &prev{(*(operation-1))};
                int append{};
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
            int add{};
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
