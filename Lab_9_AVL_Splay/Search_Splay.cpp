bool search(int val){
    //TODO
    Node* current = root;
    Node* last = nullptr;
    while(current) {
        last = current;
        if(val == current->val) break;
        else if (val < current->val) current = current->pLeft;
        else current = current->pRight;
    }
    if(last) {
        splay(last);
        return (last->val == val);
    }
    return false;
}
