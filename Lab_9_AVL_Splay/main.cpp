void traverseInOrder(Node* root) {
    if(!root) return;
    traverseInOrder(root->pLeft);
    cout << root->data << " ";
    traverseInOrder(root->pRight);
}
void printInorder(){
    //TODO
    traverseInOrder(root);
}
bool searchRec(Node* root, const T &value) {
    if(!root) return false;
    else if(root->data == value) return true;
    else if(root->data > value) return searchRec(root->pLeft, value);
    else return searchRec(root->pRight, value);
}
bool search(const T &value){
    //TODO
    return searchRec(root, value);
}