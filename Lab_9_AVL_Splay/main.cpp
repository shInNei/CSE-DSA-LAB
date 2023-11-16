// Write your helper functions here
Node* searchNode(Node*root, int val) {
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
    }
    return last;
}
Node* remove(int val) {
    if (!root) return nullptr;
    Node* node = searchNode(root, val);

    if (!node || node->val != val) return nullptr;  // Value not found
    splay(node);

    Node* removeNode = root;
    Node* tree1 = removeNode->pLeft;
    Node* tree2 = removeNode->pRight;

    // Disconnect the removed node from its subtrees
    if (tree1) tree1->pParent = nullptr;
    if (tree2) tree2->pParent = nullptr;
    removeNode->pLeft = removeNode->pRight = nullptr;

    if (!tree1) {
        root = tree2;
    } else {
        Node* maxNode = tree1;
        while (maxNode->pRight) {
            maxNode = maxNode->pRight;
        }
        splay(maxNode);
        maxNode->pRight = tree2;
        if (tree2) tree2->pParent = maxNode;
        root = maxNode;
    }

    return removeNode;
}
