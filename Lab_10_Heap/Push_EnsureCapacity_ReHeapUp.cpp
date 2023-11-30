template<class T>
void Heap<T>::push(T item){
    if(this->count >= this->capacity) this->ensureCapacity(this->count);
    this->elements[this->count] = item;
    this->count++;
    this->reheapUp(this->count-1);
}

template<class T>
void Heap<T>::ensureCapacity(int minCapacity){
    this->capacity = minCapacity *2;
    T* newCapacity = new T[capacity];
    for(int i = 0; i < this->count; i++) newCapacity[i] = this->elements[i];
    delete [] elements;
    this->elements = newCapacity;
}

template<class T>
void Heap<T>::reheapUp(int position){
    if(position <= 0) return;
    int parent = (position - 1)/2;
    if(elements[position] >= elements[parent]) {
        int temp = elements[parent];
        elements[parent] = elements[position];
        elements[position] = temp;
        reheapUp(parent);
    }
}
