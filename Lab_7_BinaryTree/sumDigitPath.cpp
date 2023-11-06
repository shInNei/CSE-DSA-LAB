int sumDigitPath(BTNode* root) {
    if (root == nullptr) return 0;
    
    std::queue<std::pair<BTNode*, int>> q;
    q.push({root, root->val});
    
    int sum = 0;
    while (!q.empty()) {
        BTNode* node = q.front().first;
        int val = q.front().second;
        q.pop();
        
        if (node->left == nullptr && node->right == nullptr) {
            sum = (sum + val) % 27022001;
        }
        
        if (node->left != nullptr) {
            int left_val = ((10 * val) + node->left->val) % 27022001;
            q.push({node->left, left_val});
        }
        
        if (node->right != nullptr) {
            int right_val = ((10 * val) + node->right->val) % 27022001;
            q.push({node->right, right_val});
        }
    }
    
    return sum;
}
