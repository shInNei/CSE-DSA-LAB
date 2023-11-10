// You must use the nodes in the original list and must not modify ListNode's val attribute. 
// Hint: You should complete the function mergeLists first and validate it using our first testcase example

// Merge two sorted lists
ListNode* mergeLists(ListNode* a, ListNode* b) {
    if(!a) return b;
    if(!b) return a;
    if(a->val < b->val) {
        a->next = mergeLists(a->next, b);
        return a;
    }
    else {
        b->next = mergeLists(a, b->next);
        return b;
    }
}
ListNode* splitLists(ListNode* head) {
    if(!head || !head->next) return head;
    ListNode* slow = head;
    ListNode* fast = head->next;
    while(fast && fast->next) {
        slow = slow->next;
        fast = fast->next->next;
    }
    ListNode* SecondHead = slow->next;
    slow->next = nullptr;
    return SecondHead;
}
// Sort and unsorted list given its head pointer
ListNode* mergeSortList(ListNode* head) {
    if(!head || !head->next) return head;
    ListNode* SecondHead = splitLists(head);
    head = mergeSortList(head);
    SecondHead = mergeSortList(SecondHead);
    return mergeLists(head, SecondHead);
}