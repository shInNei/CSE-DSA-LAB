template <class T>
class DLinkedList {
public:
    class Node; // Forward declaration
protected:
    Node* head;
    Node* tail;
    int count;
public:
    DLinkedList();
    ~DLinkedList();
    void    add(const T &e);
    void    add(int index, const T &e);
    int     size();
public:
    class Node
    {
    private:
        T data;
        Node *next;
        Node *previous;
        friend class DLinkedList<T>;

    public:
        Node()
        {
            this->previous = NULL;
            this->next = NULL;
        }

        Node(const T &data)
        {
            this->data = data;
            this->previous = NULL;
            this->next = NULL;
        }
    };
};
template <class T>
void DLinkedList<T>::add(const T& e) {
    /* Insert an element into the end of the list. */
    if(this->count == 0) {
        this->head = this->tail = new Node(e);
        this->count++;
        return;
    }
    Node* pNew = new Node(e);
    tail->next = pNew;
    pNew->previous = tail;
    tail = tail->next;
    this->count++;
}

template<class T>
void DLinkedList<T>::add(int index, const T& e) {
    /* Insert an element into the list at given index. */ 
    if(index < 0 || index > this->count) throw std::out_of_range("Naruto");
    if(index == this->count) {
        add(e);
        return;
    }
    else if(index == 0) {
        Node* pNew = new Node(e);
        pNew->next = head;
        head->previous = pNew;
        head = head->previous;
        this->count++;
        return;
    }
    else {
        Node* pNew = new Node(e);
        Node* temp = head;
        for(int i = 0; i < index-1; i++) temp = temp->next;
        pNew->previous = temp;
        pNew->next = temp->next;
        temp->next = pNew;
        pNew->next->previous = pNew;
        this->count++;
    }
}

template<class T>
int DLinkedList<T>::size() {
    /* Return the length (size) of list */ 
    return this->count;
}