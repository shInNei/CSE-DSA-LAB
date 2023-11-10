BSTNode* subtreeWithRange(BSTNode* root, int lo, int hi) {
    // STUDENT ANSWER
    if(!root) return root;
    root->left = subtreeWithRange(root->left, lo, hi);
    root->right = subtreeWithRange(root->right, lo, hi);
    if(root->val < lo) {
        BSTNode* temp = root->right;
        delete root;
        return temp;
    }
    if(root->val > hi) {
        BSTNode* temp = root->left;
        delete root;
        return temp;
    }
    return root;
}