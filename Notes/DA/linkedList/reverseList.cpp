struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(nullptr) {}
};
class Solution {
public:
    // 双指针法
    ListNode* reverseList(ListNode* head) {
        ListNode* tmp;
        ListNode* cur = head;
        ListNode* pre = nullptr;
        while (cur) {
            tmp = cur->next;
            cur -> next = pre;
            pre = cur;
            cur = tmp;
        }
        return pre;
    }
    // 递归法
    ListNode* reverse(ListNode* pre, ListNode* cur) {
        if (cur == nullptr) return pre;
        ListNode* tmp = cur->next;
        return reverse(cur, tmp);
    }
    ListNode* reverseList(ListNode* head) {
        return reverse(nullptr, head);
    }
    // 从后往前翻转
    ListNode* reverseList(ListNode* head) {
        // 边缘条件判断
        if (head == nullptr) return nullptr;
        if (head->next == nullptr) return head;
        ListNode* last = reverseList(head->next);
        head->next->next = head;
        return last;
    }
};