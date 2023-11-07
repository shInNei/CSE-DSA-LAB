// STUDENT ANSWER BEGIN
// You can define other functions here to help you.
int rHeight(Node* root) {
    if(root == nullptr) return 0;
    else {
        int l = rHeight(root->pLeft);
        int r = rHeight(root->pRight);
        return max(l,r) + 1;
    }
}
int getHeight() {
    // TODO: return height of the binary tree.
    return rHeight(root);
}
string pre(Node* root, string order) {
    if(root == nullptr) return order;
    order += to_string(root->value) + " ";
    if(root->pLeft) order = pre(root->pLeft, order);
    if(root->pRight) order = pre(root->pRight, order);
    return order;
}
string preOrder() {
    // TODO: return the sequence of values of nodes in pre-order.
    return pre(root,"");
}
string in(Node* root, string order) {
    if(root == nullptr) return order;
    if(root->pLeft) order = in(root->pLeft, order);
    order += to_string(root->value) + " ";
    if(root->pRight) order = in(root->pRight, order);
    return order;
}
string inOrder() {
    // TODO: return the sequence of values of nodes in in-order.
    return in(root,"");
}
string post(Node* root, string order) {
    if(root == nullptr) return order;
    if(root->pLeft) order = post(root->pLeft, order);
    if(root->pRight) order = post(root->pRight, order);
    order += to_string(root->value) + " ";
    return order;
}
string postOrder() {
    // TODO: return the sequence of values of nodes in post-order.
    return post(root, "");
}

// STUDENT ANSWER END