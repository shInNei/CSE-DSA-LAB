#include <list>
#include <iostream>
using namespace std;

struct ListNode {
    int val;
    ListNode *left;
    ListNode *right;
    ListNode(int x = 0, ListNode *l = nullptr, ListNode* r = nullptr) : val(x), left(l), right(r) {}
};

/*
struct ListNode {
    int val;
    ListNode *left;
    ListNode *right;
    ListNode(int x = 0, ListNode *l = nullptr, ListNode* r = nullptr) : val(x), left(l), right(r) {}
};
*/
void swap(ListNode* a, ListNode* b) {
    ListNode* temp = b->left;
    if(a->left != nullptr) {
        a->left->right = b;
        b->left = a->left;
        a->left = temp;
        temp->right = a;
    }
    else {
        b->left = nullptr;
        a->left = temp;
        temp->right = a;
    }
    temp = a->right;
    if(b->right != nullptr) {
        b->right->left = a;
        a->right = b->right;
        b->right = temp;
         temp->left = b;
    }
    else {
        a->right = nullptr;
        b->right = temp;
        temp->left = b;
    }
}
ListNode* reverse(ListNode* head, int a, int b) {
    //To Do
    if(head == nullptr || (head->left == nullptr && head->right == nullptr))
    return head;
    if(a == b) return head;
        ListNode* p1 = head;
        ListNode* p2 = head;
        bool flag = false;
        for(int i = 0; i < a-1; i++) p1 = p1->right;
        for(int i = 0; i < b-1; i++) p2 = p2->right;
        while(p1 != p2 && p1->left != p2) {
            swap(p1, p2);
            ListNode* temp = p1;
            p1 = p2;
            p2 = temp;
            if(a == 1 && !flag) {
                head = p1;
                flag = true;
            }
            p1 = p1->right;
            p2 = p2->left;
    }
    return head;
    
}