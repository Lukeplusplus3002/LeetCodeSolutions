//https://leetcode.com/problems/add-two-numbers-ii/
struct ListNode {
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};
class Solution {
public:
/*
    This is basically a combination of the problem 206 (reverse linked list) and problem 2 (Add Two Numbers)
    If you don't understand this algorithm, check problem 2 included in this folder (medium problems).
    This is an O(1) space complexity and O(m+n) time complexity solution. It reverses both lists, perform 
    the addition (storing the result in list 1), and then reverses the answer.

    Note that for the three reversals, node1 represents the previous node, node2 the current node, and next
    the node after node2.
*/
    ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
        {//reverse list 1
            ListNode* node1{nullptr}, *node2{l1};
            while(node2!=nullptr)
            {
                ListNode* const next{node2->next};
                node2->next=node1;
                l1=node2;
                node1=node2;
                node2=next;
            }
        }
        {//reverse list 2
            ListNode* node1{nullptr}, *node2{l2};
            while(node2!=nullptr)
            {
                ListNode* const next{node2->next};
                node2->next=node1;
                l2=node2;
                node1=node2;
                node2=next;
            }
        }
        {//add the two lists
            bool carry{};
            ListNode* l1Copy{l1};
            ListNode* l1Tail{nullptr};
            while(l1Copy!=nullptr && l2!=nullptr)
            {
                const int sum{l1Copy->val + l2->val + carry};
                carry=sum/10;
                l1Copy->val=sum-carry*10;
                l1Tail=l1Copy;
                l1Copy=l1Copy->next;
                l2=l2->next;
            }
            if(l1Copy==nullptr && l2!=nullptr)
            {
                l1Tail->next=l2;
                l1Copy=l2;
            }
            while(carry)
            {
                if(l1Copy==nullptr)
                {
                    l1Tail->next=new ListNode(1, nullptr);
                    carry=false;
                }else
                {
                    if(l1Copy->val==9)
                    {
                        l1Copy->val=0;
                        l1Tail=l1Copy;
                        l1Copy=l1Copy->next;
                    }else
                    {
                        ++(l1Copy->val);
                        carry=false;
                    }
                }
            }    
        }
        {//reverse the answer
            ListNode* node1{nullptr}, *node2{l1};
            while(node2!=nullptr)
            {
                ListNode* const next{node2->next};
                node2->next=node1;
                l1=node2;
                node1=node2;
                node2=next;
            }
        }
        return l1;
    }
};
