// STUDENT ANSWER BEGIN
// You can define other functions here to help you.
T minRec(Node* root) {
    if(!root->pLeft) return root->value;
    else return minRec(root->pLeft);
}
T maxRec(Node* root) {
    if(!root->pRight) return root->value;
    else return maxRec(root->pRight);
}
T getMin() {
    //TODO: return the minimum values of nodes in the tree.
    return minRec(this->root);
}

T getMax() {
    //TODO: return the maximum values of nodes in the tree.
    return maxRec(this->root);
}

// STUDENT ANSWER END
