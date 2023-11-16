// write your helper functions here
// Helper function for splay operation
void zig(Node* x) {
    Node* p = x->pParent;
    if (x == p->pLeft) {
        p->pLeft = x->pRight;
        if (x->pRight) x->pRight->pParent = p;
        x->pRight = p;
    } 
    else {
        p->pRight = x->pLeft;
        if (x->pLeft) x->pLeft->pParent = p;
        x->pLeft = p;
    }
        x->pParent = p->pParent;
        p->pParent = x;
        if (x->pParent) {
            if (p == x->pParent->pLeft) x->pParent->pLeft = x;
            else x->pParent->pRight = x;
        } 
        else root = x;
}
void zigZig(Node* x) {
    zig(x->pParent);
    zig(x);
}
void zigZag(Node* x) {
    zig(x);
    zig(x);
}
void splay(Node* p) {
    while (p->pParent) {
        Node* parent = p->pParent;
        Node* grandparent = parent->pParent;
        if (!grandparent) {
            zig(p);
        } 
        else if ((parent == grandparent->pLeft && p == parent->pLeft) || (parent == grandparent->pRight && p == parent->pRight)) {
            zigZig(p);
        } 
        else {
            zigZag(p);
        }
    }
}
void insert(int val) {
    if (!root) {
        root = new Node(val);
        return;
    }

    Node* currentNode = root;
    Node* parent = nullptr;
    while (currentNode) {
        parent = currentNode;
        if (val < currentNode->val) {
            currentNode = currentNode->pLeft;
            } 
        else {
            currentNode = currentNode->pRight;
        }
}
    Node* newNode = new Node(val, nullptr, nullptr, parent);
    if (val < parent->val) {
        parent->pLeft = newNode;
    } 
    else {
        parent->pRight = newNode;
}
    splay(newNode);
}
