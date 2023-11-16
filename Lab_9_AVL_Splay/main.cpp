//Helping functions
Node* rotateRight(Node* root) {
    //TODO: Rotate and return new root after rotate
    
    // Chỉnh root, lấy con bên phải của root mới ra
    Node* newRoot = root->pLeft;
    Node* childNewRoot = newRoot->pRight;
    
    // Đưa root cũ xuống làm con bên phải, gắn con cũ sang bên trái
    newRoot->pRight = root;
    root->pLeft = childNewRoot;
    
    return newRoot;
}

Node* rotateLeft(Node* root) {
    //TODO: Rotate and return new root after rotate
    
    // Chỉnh root, lấy con bên trái của root mới ra
    Node* newRoot = root->pRight;
    Node* childNewRoot = newRoot->pLeft;
    
    // Đưa root cũ xuống làm con bên trái, gắn con cũ sang bên phải
    newRoot->pLeft = root;
    root->pRight = childNewRoot;
    
    return newRoot;
}
int getBalance(Node* temp) {
    if(!temp) return 0;
    return getHeightRec(temp->pLeft) - getHeightRec(temp->pRight);
}
Node* insertRec(Node* temp, const T &value) {
    if(!temp) return new Node(value);
    if(value < temp->data) temp->pLeft = insertRec(temp->pLeft, value);
    else if(value >= temp->data) temp->pRight = insertRec(temp->pRight, value);
  
    int balance = getBalance(temp);
    
    // Left Left Case
    if (balance > 1 && value < temp->pLeft->data)
        return rotateRight(temp);

    // Right Right Case
    if (balance < -1 && value >= temp->pRight->data)
        return rotateLeft(temp);

    // Left Right Case
    if (balance > 1 && value >= temp->pLeft->data)
    {
        temp->pLeft = rotateLeft(temp->pLeft);
        return rotateRight(temp);
    }

    // Right Left Case
    if (balance < -1 && value < temp->pRight->data)
    {
        temp->pRight = rotateRight(temp->pRight);
        return rotateLeft(temp);
    }
    return temp;
}
void insert(const T &value){
    //TODO
    root = insertRec(root, value);
}