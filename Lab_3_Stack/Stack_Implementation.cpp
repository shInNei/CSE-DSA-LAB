void push(T item) {
    // TODO: Push new element into the top of the stack
    this->list.add(item);
}

T pop() {
    // TODO: Remove an element on top of the stack
    return this->list.removeAt(this->list.size() - 1);
}

T top() {
    // TODO: Get value of the element on top of the stack
    return this->list.get(this->list.size() - 1);    
}

bool empty() {
    // TODO: Determine if the stack is empty
    return this->list.empty();
}

int size() {
    // TODO: Get the size of the stack
    return this->list.size();    
}

void clear() {
    // TODO: Clear all elements of the stack
    this->list.clear();
}