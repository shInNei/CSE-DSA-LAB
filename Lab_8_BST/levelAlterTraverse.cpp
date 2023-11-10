vector<int> levelAlterTraverse(BSTNode* root) {
    // STUDENT ANSWER
    vector<int> result;
    if(!root) return result;
    stack<BSTNode*> curLevel;
    stack<BSTNode*> nextLevel;
    curLevel.push(root);
    bool lefttoRight = true;
    while(!curLevel.empty()) {
        BSTNode* temp = curLevel.top();
        curLevel.pop();
        if(temp) {
            result.push_back(temp->val);
            if(lefttoRight) {
                if(temp->left) nextLevel.push(temp->left);
                if(temp->right) nextLevel.push(temp->right);
            }
            else {
                if(temp->right) nextLevel.push(temp->right);
                if(temp->left) nextLevel.push(temp->left);
            }
        }
        if(curLevel.empty()) {
            lefttoRight = !lefttoRight;
            swap(curLevel, nextLevel);
        }
    }
    return result;
}
