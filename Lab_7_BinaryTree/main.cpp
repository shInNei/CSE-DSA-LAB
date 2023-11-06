// STUDENT ANSWER BEGIN
// You can define other functions here to help you.

void BFS()
{
    queue<Node*> q;
    q.push(root);
    while(!q.empty()) {
        Node* temp = q.front();
        q.pop();
        cout << temp->value;
        if(temp->pLeft != nullptr) q.push(temp->pLeft);
        if(temp->pRight != nullptr) q.push(temp->pRight);
        if(!q.empty()) cout << " ";
    }
}
// STUDENT ANSWER END