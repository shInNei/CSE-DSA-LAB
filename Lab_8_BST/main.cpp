int kthSmallest(BSTNode* root, int k) {
    // STUDENT ANSWER
    queue<BSTNode*> q;
    vector<int> arr;
    q.push(root);
    BSTNode* temp = root;
    while(!q.empty()) {
        temp = q.front();
        q.pop();
        if(temp->left) q.push(temp->left);
        if(temp->right) q.push(temp->right);
        arr.push_back(temp->val);
    }
    sort(arr.begin(), arr.end());
    return arr[k-1];
}