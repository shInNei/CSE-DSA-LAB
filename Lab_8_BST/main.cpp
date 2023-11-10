// STUDENT ANSWER BEGIN
// You can define other functions here to help you.
bool find(T i) {
    // TODO: return true if value i is in the tree; otherwise, return false.
    Node* temp = root;
    while(temp) {
        if(temp->value == i) return true;
        else if(temp->value > i) temp = temp->pLeft;
        else if(temp->value < i) temp = temp->pRight;
    }
    return false;
}
T sumRec(Node* root, T l, T r) {
    if(!root) return 0;
    else if(root->value < l) return sumRec(root->pRight, l, r);
    else if(root->value > r) return sumRec(root->pLeft, l, r);
    else return root->value + sumRec(root->pLeft, l, r) + sumRec(root->pRight, l, r);
}
T sum(T l, T r) {
    // TODO: return the sum of all element in the tree has value in range [l,r].
    return sumRec(this->root, l, r);
}

// STUDENT ANSWER END
