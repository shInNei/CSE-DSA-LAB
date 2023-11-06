void longestPSumRec(BTNode* root, int sum, int len , int& maxSum, int& maxLen) {
    if(!root) {
        if(maxLen < len) {
            maxLen = len;
            maxSum = sum;
        }
        else if(maxLen == len && maxSum < sum) maxSum = sum;
        return;
    }
    longestPSumRec(root->left, sum + root->val, len+1, maxSum, maxLen);
    longestPSumRec(root->right, sum + root->val, len+1, maxSum, maxLen);
}
int longestPathSum(BTNode* root) {
    if(!root) return 0;
    int maxSum = INT32_MIN; int maxLen = 0;
    longestPSumRec(root, 0, 0, maxSum, maxLen);
    return maxSum;
}
