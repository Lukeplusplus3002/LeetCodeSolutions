//problem link: https://leetcode.com/problems/add-two-numbers/
struct ListNode {
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};
class Solution {
public:
//This is the first algorithm that came up to me. I think it's good enough
/*
    This is an in-place solution that uses the first list to store the result. It's a pretty straightforward
    algorithm. l1 and l2 are the two pointers that are used to travel through their two respective lists
*/
    ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
        bool carry{};
        ListNode* const head{l1};
        ListNode* prev{nullptr};//digit previous to l1
        while(l1!=nullptr && l2!=nullptr)
        {
            const int sum{l1->val + l2->val + carry};
            carry=sum/10;
            l1->val=sum-carry*10;
            prev=l1;
            l1=l1->next;
            l2=l2->next;
        }
        if(l1==nullptr && l2==nullptr)
        {
            if(carry)
                prev->next=new ListNode(1, nullptr);
        }else
        {
            if(l1==nullptr)
            {
                prev->next=l2;//link the first list with what remains of the second list
                l1=l2;//update l1 to add the first list with carry
            }
            while(carry && l1->next!=nullptr)//travel until the last digit
            {
                if(l1->val!=9)
                {
                    ++(l1->val);
                    carry=false;
                    break;
                }else
                    l1->val=0;
                l1=l1->next;        
            }
            if(carry)
            {
                if(l1->val!=9)
                    ++(l1->val);
                else
                {
                    l1->val=0;
                    l1->next=new ListNode(1, nullptr);
                }    
            }        
        }
        return head;
    }
};
