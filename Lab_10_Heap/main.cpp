template<class T>
int Heap<T>::size(){
    return this->count;
}

template<class T>
bool Heap<T>::isEmpty(){
    return !this->count ? true : false;
}

template<class T>
T Heap<T>::peek(){
    if(this->isEmpty()) return -1;
    return elements[0];
}

template<class T>
bool Heap<T>::contains(T item){
    if(this->isEmpty()) return false;
    for(int i = 0; i < this->count; i++) {
        if(item == this->elements[i]) return true;
    }
    return false;
}

template<class T>
bool Heap<T>::pop(){
    if(this->isEmpty()) return false;
    this->elements[0] = this->elements[this->count - 1];
    this->count--;
    this->reheapDown(0);
    return true;
}