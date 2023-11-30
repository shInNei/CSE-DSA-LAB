template<class T>
int Heap<T>::getItem(T item) {
    // TODO: return the index of item in heap
    for(int i = 0; i < this->count ; i++) {
        if(this->elements[i] == item) return i;
    }
    return -1;
}

template<class T>
void Heap<T>::remove(T item) {
    // TODO: remove the element with value equal to item
    int index = this->getItem(item);
    if(index == -1) return;
    else {
        this->elements[index] = this->elements[this->count - 1];
        --this->count;
        this->reheapDown(index);
        this->reheapUp(index);
    }
}

template<class T>
void Heap<T>::clear() {
    // TODO: delete all elements in heap
    //    then reallocate memory as initial state
    delete[] this->elements;
    this->capacity = 10;
    this->elements = new T[capacity];
    this->count = 0;
}
