//Helping functions

int sumOfLeafs(){
    //TODO
    return rec(root, 0);
}
int rec(Node* root, int sum) {
    if(root == nullptr) return sum;
    if(!root->pLeft && !root-> pRight) sum += root->value;
    if(root->pLeft)  sum = rec(root->pLeft, sum);
    if(root->pRight) sum = rec(root->pRight, sum);
    return sum;
}