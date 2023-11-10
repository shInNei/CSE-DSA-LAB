int countSingleChild(BSTNode* root, int count) {
    if(!root) return 0;
    if(!root->left && root->right) count++;
    else if(!root->right && root->left) count++;
    if(root->left) count = countSingleChild(root->left, count);
    if(root->right) count = countSingleChild(root->right, count);
    return count;
}
int singleChild(BSTNode* root) {
    // STUDENT ANSWER
    return countSingleChild(root, 0);
}