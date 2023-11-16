//Helping functions
Node* maxValueNode(Node* root) {
    Node* temp = root;
    while(temp->pRight) {
        temp = temp->pRight;
    }
    return temp;
}
int getBalance(Node* root) {
    if(!root) return 0;
    return getHeightRec(root->pLeft) - getHeightRec(root->pRight);
    
}
Node* removeNodeRec(Node* root, const T &value) {
    if(!root) return root;
    if(root->data > value ) root->pLeft = removeNodeRec(root->pLeft, value);
    else if(root->data < value) root->pRight = removeNodeRec(root->pRight, value);
    else {
        if(!root->pLeft || !root->pRight) {
            Node *temp = root->pLeft? root->pLeft : root->pRight;
            if(!temp) {
                temp = root;
                root = nullptr;
            }
            else *root = *temp;
            delete temp;
        }
        else {
            Node* temp = maxValueNode(root->pLeft);
            root->data = temp->data;
            root->pLeft = removeNodeRec(root->pLeft, temp->data);
        }
    }
    int balance = getBalance(root);
    
    if (balance > 1 && getBalance(root->pLeft) >= 0)
        return rotateRight(root);

    if (balance > 1 && getBalance(root->pLeft) < 0) {
        root->pLeft = rotateLeft(root->pLeft);
        return rotateRight(root);
    }

    if (balance < -1 && getBalance(root->pRight) <= 0)
        return rotateLeft(root);

    if (balance < -1 && getBalance(root->pRight) > 0)
    {
        root->pRight = rotateRight(root->pRight);
        return rotateLeft(root);
    }
    return root;
}
void remove(const T &value){
    //TODO
    root = removeNodeRec(root, value);
}
