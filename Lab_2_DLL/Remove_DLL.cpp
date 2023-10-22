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
    bool    empty();
    T       get(int index);
    void    set(int index, const T &e);
    int     indexOf(const T &item);
    bool    contains(const T &item); 
    T       removeAt(int index);
    bool    removeItem(const T &item);
    void    clear();
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
T DLinkedList<T>::removeAt(int index)
{
    /* Remove element at index and return removed value */
    if(index < 0 || index >= count) throw std::out_of_range("Naruto");
    if(this->count == 1) {
        int save = head->data;
        delete head;
        head = nullptr;
        tail = nullptr;
        this->count = 0;
        return save;
    }
    if(index == 0) {
        Node* temp = head;
        head = head->next;
        head->previous = nullptr;
        temp->next = nullptr;
        int save = temp->data;
        delete temp;
        temp = nullptr;
        this->count--;
        return save;
    }
    else if(index == this->count - 1) {
        Node* temp = tail;
        tail = tail->previous;
        tail->next = nullptr;
        temp->previous = nullptr;
        int save = temp->data;
        delete temp;
        temp = nullptr;
        this->count--;
        return save;
    }
    else {
        Node* temp = head;
        for(int i = 0; i < index; i++) {
            temp = temp->next;
        }
        temp->previous->next = temp->next;
        temp->next->previous = temp->previous;
        temp->next = nullptr;
        temp->previous = nullptr;
        int save = temp->data;
        delete temp;
        temp = nullptr;
        this->count--;
        return save;
    }
}

template <class T>
bool DLinkedList<T>::removeItem(const T& item)
{
    /* Remove the first apperance of item in list and return true, otherwise return false */
    int index = indexOf(item);
    if(index != -1) {
        removeAt(index);
        return true;
    }
    return false;
}

template<class T>
void DLinkedList<T>::clear(){
    /* Remove all elements in list */
    while(this->count != 0) {
        removeAt(0);
    }
}
