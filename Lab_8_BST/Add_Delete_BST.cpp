//Helping functions
Node* addRec(Node* root, T value) {
    if(!root) root = new Node(value);
    else if(value <= root->value) {
        root->pLeft = addRec(root->pLeft, value);
    } 
    else if(value >= root->value){
        root->pRight = addRec(root->pRight, value);
    }
    return root;
}
void add(T value) {
    //TODO
    this->root = addRec(this->root, value);
}
Node* deleteNodeRec(Node*root, T value) {
    if(!root) return root;
    if(root->value > value) {
        root->pLeft = deleteNodeRec(root->pLeft, value);
        return root;
    }
    else if(root->value < value) {
        root->pRight = deleteNodeRec(root->pRight, value);
        return root;
    }
        if(!root->pLeft) {
            Node* temp = root->pRight; 
            delete root;
            return temp;
        }
        else if(!root->pRight) {
            Node* temp = root->pLeft;
            delete root;
            return temp;
        }
        else {
            Node* temp = root;
            Node* succ = root->pRight;
            while(succ->pLeft != nullptr) {
                temp = succ;
                succ = succ->pLeft;
            }
            if(temp != root) {
                temp->pLeft = succ->pRight;
            }
            else temp->pRight = succ->pRight;
            root->value = succ->value;
            delete succ;
            return root;
        }
}

void deleteNode(T value){
    //TODO
    this->root = deleteNodeRec(this->root, value);
}
