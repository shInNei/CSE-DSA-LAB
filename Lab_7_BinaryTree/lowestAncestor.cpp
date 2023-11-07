BTNode* rec(BTNode* root, int a, int b) {
    if(root == nullptr|| root->val == a || root->val == b) return root;
    BTNode* l = nullptr; BTNode* r = nullptr;
    if(root->left) l = rec(root->left, a, b);
    if(root->right) r = rec(root->right, a, b);
    if(l && r) return root;
    else if(l && !r) return l;
    else if(!l && r) return r;
    else return nullptr;
}
int lowestAncestor(BTNode* root, int a, int b) {
    return rec(root,a,b)->val;
}
