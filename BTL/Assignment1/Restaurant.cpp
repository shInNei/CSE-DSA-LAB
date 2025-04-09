#include "main.h"
class imp_res : public Restaurant
{
	public:
	class OrderList { // Class dùng để lưu trữ địa chỉ khách hàng vào nhà hàng theo thứ tự sớm nhất -> gần nhất
	public:
	    class Node {
        public:
			customer* address;
			bool inTable;
			Node* next;
            Node* prev;
		    Node(customer*address = nullptr, Node* prev = nullptr, bool inTable = 0, Node* next = nullptr): address(address), prev(prev), inTable(inTable) , next(next){}
			~Node() {}
		};
    private:
	Node* head;
	Node* tail;
	int size;
	friend imp_res;
	public:
    OrderList(): head(nullptr), tail(nullptr), size(0) {}
	~OrderList() {
		this->clear();
	}
    void add(customer* address) { // Add address to the tail of the List
        if(size == 0) {
			head = tail = new Node(address);
			this->size++;
			return;
		}
		Node* pNew = new Node(address,tail);
		tail->next = pNew;
		tail = pNew;
		this->size++;
	}
	void swapAddress(customer* a, customer* b) {
		Node* temp1 = head;
		Node* temp2 = head;
		while(temp1->address != a || temp2->address != b) {
			if(temp1->address != a) temp1 = temp1->next;
			if(temp2->address != b)temp2 = temp2->next;
		}
		temp1->address = b;
		temp2->address = a;
	}
	void removeAt(int index) { // Xóa địa chỉ sau khi đuổi khách (Chỉ xóa ở đầu hoặc đuôi)
        if(head == nullptr) return; // Bàn ăn không có ai
		if(this->size == 1) {
			this->tail = nullptr;
			delete this->head;
			this->head = nullptr;
			this->size = 0;
			return;
		}
		if(index == 0) { // Xóa ở đầu
			head = head->next;
			Node* temp = head->prev;
			head->prev = nullptr;
			temp->next = nullptr;
			delete temp;
			temp = nullptr;
			this->size--;
			return;
		}
		else if(index == size - 1) { // Xóa ở đuôi
            tail = tail->prev;
			Node* temp = tail->next;
			tail->next = nullptr;
			temp->prev = nullptr;
			delete temp;
			temp = nullptr;
			this->size--;
			return;
		}
	}
	Node* removeAt_DM(int index, Node* cur) { // Xóa dành riêng cho Domain Expansion, xóa được ở một vị trí bất kì
	    if(head == nullptr) return nullptr;
		if(this->size == 1) {
			removeAt(0);
			return nullptr;
		}
		else if(index == 0) {
			removeAt(0);
			return head; // Kết thúc luôn khỏi cần check head làm gì
		}
		else if(index == this->size - 1) {
			removeAt(index);
			return nullptr;
		}
		else { // Xóa Node cur
		    cur->prev->next = cur->next;
			cur->next->prev = cur->prev;
			Node* temp = cur;
			cur = cur->next;
			temp->next = nullptr;
			temp->prev = nullptr;
			delete temp;
			temp = nullptr;
			this->size--;
			return cur;
		}
	}
	bool check(customer*a, customer* b) {
		if(abs(a->energy) != abs(b->energy)) return true;
		Node* temp = head;
		while(temp != nullptr) {
			if(temp->address == a) return true;
			if(temp->address == b) return false;
			temp = temp->next;
		}
		return false;
	}
	void print_Domain_Expansion(bool flag) {
		Node* temp = tail;
		if(flag) { // In thông tin oán linh bị đuổi
		    while(temp != nullptr) {
				if(temp->address->energy < 0) temp->address->print();
				temp = temp->prev;
			}	
		}
		else {
			while(temp != nullptr) { // In thông tin chú thuật sư bị đuổi
				if(temp->address->energy > 0) temp->address->print();
				temp = temp->prev;
			}
		}
	}
	Node* search(customer* target) { // Check coi add ở ngoài hay add từ queue vô
		if(this->size == 0) return nullptr;
		Node* temp = this->head;
		while(temp != nullptr) {
			if(temp->address->name == target->name) return temp;
			temp = temp->next;
		}
		return nullptr;
	}
	void blueClear(int count) {
		if(count == 0) return;
		else {
			Node* temp = this->head;
			int index = 0;
			while(temp != nullptr) {
				if(temp->inTable ) {
					temp = removeAt_DM(index, temp);
					continue;
				}
				temp = temp->next;
				index++;
			}
		}
			
	}
	void clear() {
		if(this->size == 0) return;
		else {
			while(this->size != 0) {
				removeAt(0);
			}
		}
	}

};
    public:
    class Queue { // Hàng Đợi của nhà hàng
    private:
        int size; // Number of customers in this queue
		customer* front; // The first customer come to the queue (and the first to move to Restaurant)
		customer* rear; // The latest customer come to the queue
		friend imp_res;
    public:
        Queue(customer* Frear) {
		    size = 1;
			Frear->next = Frear;
			Frear->prev = Frear;
		    this->rear = Frear;
		    this->front = Frear;
	    }
	    ~Queue() {
            this->clear();
	    }
		void enqueue(customer* cus) { // Đưa khách vào hàng đợi
		    if(size == 0) {
				this->size++;
				cus->next = cus;
				cus->prev = cus;
				this->rear = cus;
				this->front = cus;
				return;
			}
			else {
                this->rear->prev = cus;
			    cus->next = this->rear; // Add new customer to queue
                cus->prev = front;
                front->next = cus; // Update circular
		     	rear = cus; // Update Rear
		     	this->size++;
			}
		}
		customer* newdequeue(customer* address) { // Đưa khách ra khỏi hàng đợi (New)
			if(this->size == 0) return nullptr;
			if(this->size == 1) { // front = rear
			    front->next = nullptr;
				front->prev = nullptr;
				customer* temp = front;
				front = nullptr;
				rear = nullptr;
				this->size--;
				return temp;
			}
			else {
				if(address == front) front = front->prev;
				else if(address == rear) rear = rear->next;
				address->prev->next = address->next;
				address->next->prev = address->prev; 
				address->next = nullptr;
				address->prev = nullptr;
				this->size--;
				return address;
			}
		}
		customer* dequeue() { // Đưa khách ra khỏi hàng đợi (Old)
		    if(size == 0) return nullptr;
		    else if(front == rear) {
				front->next = nullptr;
				front->prev = nullptr;
				customer* temp = front;
				front = nullptr;
				rear = nullptr;
				this->size--;
				return temp;
			}
			else {
				customer* temp = front;
                front = front->prev;
			    front->next = rear;
			    rear->prev = front;
			    temp->prev = nullptr;
			    temp->next = nullptr;
			    this->size--;
			    return temp;
			}
		} 
		customer* mostEnergy() { //O(n)
		    if(rear == nullptr) return nullptr;
			if(this->size == 1) return rear;
			customer* output = rear;
			int mostEnergy = abs(rear->energy);
			for(int i = 0; i < this->size; i++) {
				if(mostEnergy < abs(rear->energy)) {
					mostEnergy = abs(rear->energy);
					output = rear;
				}
				rear = rear->next;
			}
			return output;
		}
		int sumSub() { // Tính tổng Energy cho Bành trướng lãnh địa
			int sumSub = 0;
			for(int i = 0; i < this->size; i++) {
				sumSub += front->energy;
				front = front->prev;
			}
			return sumSub;
		}
		void clear() {
			if(this->size == 0) return;
			else {
				customer* temp = nullptr;
				while(this->size != 0) {
					temp = dequeue();
					delete temp;
					temp = nullptr;
				}
			}
		}

};
	private:
		customer* x; // x position
		int count; // Number of customers in this res
		Queue* queue; // a queue
		OrderList* list; // Danh sách chứa địa chỉ các khách hàng theo thứ tự đi vô
	public:	
		imp_res() { 
			list = new OrderList();
			x = nullptr;
			count = 0;
			queue = nullptr;
		};
		~imp_res() {
			delete this->list;
			this->clear();
			delete this->queue;
		}
		void swap(customer* a, customer* b) { // Đổi chỗ 2 vị khách
		    if(this->x == a) this->x = b;
			else if(this->x == b) this->x = a;
			string tempName = a->name;
			int tempEnergy = a->energy;
			a->name = b->name;
			b->name = tempName;
            a->energy = b->energy;
			b->energy = tempEnergy;
		}
		bool compare(customer* a, customer* b) { // Check if a > b or not (Kiểm tra thằng đằng trước có lớn hơn hay không)
			if(abs(a->energy) >= abs(b->energy)) return true;
			else return false; // (Nhỏ hơn hoặc bằng thì không cần swap vi b đến trước)
		}
		void add(customer* cus) { //Add Clockwise
		    if(this->count == 1) { // There is only 1 customer
				this->x->next = cus;
				this->x->prev = cus;
				cus->prev = this->x;
				cus->next = this->x;
				x = cus;
				this->count++;
				return;	
			}
			else { // More than 2 customers
                cus->next = this->x->next;
			    this->x->next->prev = cus;
			    cus->prev = this->x;
			    this->x->next = cus;
			    this->count++;
			    this->x = cus;
			}
		}	
		void addAnti(customer* cus) { // Add AntiClockWise
		    if(this->count == 1) { // There is only 1 customer
                this->x->prev = cus;
				this->x->next = cus;
				cus->next = this->x;
				cus->prev = this->x;
				x = cus;
				this->count++;
				return;
			}
			else { // More than 2 customers
				cus->prev = this->x->prev;
			    this->x->prev->next = cus;
                cus->next = this->x;
			    this->x->prev = cus;
			    this->count++;
			    this->x = cus;
			}
		}
        bool ONLY(string name) { // 天上天下
		customer* fake = x;
            for(int i = 0; i < count; i++) { // Check name in Res
				if(fake->name == name) return false;
				fake = fake->next;
			}
			if(queue != nullptr) {
			customer* temp = this->queue->rear;
            for(int j = 0; j < this->queue->size; j++) { // Check name in queue
                if(temp->name == name) return false;
				temp = temp->next;
			}
			}
			return true;
		}
		void RED(string name, int energy)
		{
			if(energy == 0) return; // Decline customer with energy = 0
			if(!ONLY(name)) return; // THIÊN THƯỢNG THIÊN HẠ DUY NGÃ ĐỘC TÔN 
			if(this->count == MAXSIZE) {
				if(this->queue == nullptr) {
					customer *cus = new customer (name, energy, nullptr, nullptr);        
					queue = new Queue(cus); // create a queue
					list->add(cus);
					return;
				}
				if(this->queue->size == MAXSIZE) return; // Restaurant full and queue full
				else {
					customer *cus = new customer (name, energy, nullptr, nullptr); 
                    queue->enqueue(cus);
					list->add(cus);
					return;
				}
			}
			customer *cus = new customer (name, energy, nullptr, nullptr);    
			OrderList::Node* temp = this->list->search(cus);
			if(temp == nullptr) {
				this->list->add(cus);
				this->list->tail->inTable = 1;
			}
			else {
				temp->address = cus;
				temp->inTable = 1;
			}
			if(this->x == nullptr) { // First customer can sit anywhere 
				this->x = cus; 
			    this->x->next = x;
				this->x->prev = x;
				this->count++;
				return;
			}
			if(count < MAXSIZE/2) {
				if(energy >= x->energy) add(cus);
				else addAnti(cus);
				return;
			}
			else { // count >= MAXSIZE/2
			    int RES = energy - this->x->energy; // |e new customer - e old customer|
			    bool sign = 0; // flag for sign of RES, if RES < 0 -> sign = 1, else sign = 0
				if(RES < 0) { // remove negative
                    sign = 1;
					RES *= -1;
				}
				customer* temp = this->x->next;
                for(int i = 1; i < count; i++) { // Find the largest unsigned RES
					if(energy - temp->energy >= 0 && RES < energy - temp->energy) {
						sign = 0;
						RES = energy - temp->energy;
						this->x = temp;
					}
					else if(energy - temp->energy < 0 && RES < (energy - temp->energy)*(-1)) {
                        sign = 1;
                        RES = (energy - temp->energy)*(-1);
						this->x = temp;
					}
					temp = temp->next;
				}
				if(sign) { // Add anti-clockWise
                    addAnti(cus);
					return;
				}
                else { // Add ClockWise
				    add(cus);
                    return;
				}
			}
		}
		void isolate(customer* target) { // Cô lập customer trước khi delete
                target->prev->next = target->next;
			    target->next->prev = target->prev;
			    target->next = nullptr;
			    target->prev = nullptr;
		}
		void clear() { // delete mọi phần tử, từ từ giảm count xuống 0
			customer* temp = x;
			while(x != nullptr) {
                if(this->count == 1) {
					this->x->next = nullptr;
					this->x->prev = nullptr;
					delete x;
					temp = nullptr;
					x = nullptr;
					this->count--;
				}
				else {
                    temp = temp->next;
                    isolate(x);
				    delete x;
				    x = temp;
			     	this->count--;
				}
			}
		}
		void remove(customer* address) { // Phương thức dùng để xóa 1 phần tử
			if(count == 1) clear();
			else if(count == 2) { //  Chỉ có 2 khách, đuổi xong x giữ nguyên.
				x = address->next;
                isolate(address);
				delete address;
				address = nullptr;
				this->count--;
			}
			else { // Đuổi khách có số lượng lớn hơn 2
			    if(address->energy > 0) x = address->next;
                else x = address->prev;
				isolate(address);
				delete address;
				address = nullptr;
				this->count--;
			}
		}
		void inviteQueue() { // O(n^2) worst case
		    if(this->queue == nullptr) return;
			while(queue->size > 0 && this->count < MAXSIZE) {
				customer* wait = queue->dequeue();
				RED(wait->name, wait->energy);
				delete wait;
			}
		}
		void BLUE(int num)
		{
			if(num == 0) return;
			if(num >= count || num > MAXSIZE) {
				this->list->blueClear(this->count);
				clear(); // Đuổi Khách
			}
			else {
				OrderList::Node* temp = this->list->head;
				int index  = 0;
                while(num != 0) {
					if(temp->inTable) {
						remove(temp->address); //O(1)
						temp = list->removeAt_DM(index, temp);
						num--;
						continue;
					}
					temp = temp->next;
					index++;
				}
			}
			inviteQueue();
		}
		void insertionSort(OrderList* sublist, int& n, int incr, int k, int size) {
			OrderList::Node* temp = sublist->head;
			int step = 1;
			int i = step;
			while(temp != nullptr) {
				if(temp == sublist->head) {
					temp = temp->next;
				}
				else {
					OrderList::Node* save = temp;
					while(i != 0) {
						if(compare(temp->prev->address, temp->address) && this->list->check(temp->prev->address,temp->address)) {
						swap(temp->prev->address,temp->address);
						this->list->swapAddress(temp->prev->address, temp->address);
						i -= 1;
						n++;
						temp = temp->prev;
						if(temp->prev == nullptr) break;
					}	
					    else break;
					}		
					temp = save->next;
					step++;
					i = step;		
				}
			}
		}
		void shellSort(customer* mEnergy, int size, int& n) {
			if(mEnergy == nullptr || this->queue->size == 1) return;
			customer* first = mEnergy;
			customer* cur = mEnergy;
			int k = size/2;
			while(k >= 1) { // Sort với từng increment
			   if(k == 2) {
					k = k/2;
					continue;
				}
				int segment = 0;
				first = mEnergy;
				while(segment < k) { // Sort với từng Sublist
					cur = first;
					first = first->next;
					OrderList* subList = new OrderList();
					while(cur != this->queue->front) { // Tìm Sublist
						subList->add(cur);
						for(int i = 0; i < k; i++) {
							cur = cur->next;
							if(cur == this->queue->front && i == k-1) {
								subList->add(cur);
								break;
							}
							else if(cur == this->queue->front && i != k-1) break;
						}
					}
					insertionSort(subList, n, segment, k, size);
					delete subList;
					segment++;
				}
				k = k/2;
			}
		}
		int findingN(customer* temp) {
			int size = 0;
			if(temp == this->queue->rear) return this->queue->size;
			customer* cur = this->queue->front;
			while(cur != temp->prev) {
				size++;
				cur = cur->prev;
			}
			return size;
		}
		void PURPLE()
		{
			//cout << "purple"<< endl;
			if(this->queue == nullptr ) return;
			int n = 0; // Số lần swap, đừng có đụng vô
			customer* temp = this->queue->mostEnergy();
			int size = findingN(temp);
			shellSort(temp, size, n); //  Chỉnh rear là làm từ đầu đến cuối
			BLUE(n % MAXSIZE);
		}
		void REVERSAL() // O(n)
		{ // 2 - pointers
		  // Vấn đề cập nhật X chưa được GIẢI QUYẾT
			if(this->count == 0 || this->count == 1) return; // Số khách 0 hoặc 1 thì khỏi đổi
			customer* gojou1 = this->x; // Energ > 0
			customer* gojou2 = this->x->next;
			customer* sukuna1 = this->x; // Energy < 0
			customer* sukuna2 = this->x->next;
            while((sukuna1 != sukuna2 && sukuna2->next != sukuna1) || (gojou1 != gojou2 && gojou2->next != gojou1)) {
				// Swap for negative
				if(sukuna1 != sukuna2 && sukuna2->next != sukuna1) {
					if(sukuna1->energy < 0 && sukuna2->energy < 0) {
					    swap(sukuna1, sukuna2);
						this->list->swapAddress(sukuna1,sukuna2);
					    sukuna1 = sukuna1->prev;
					    sukuna2 = sukuna2->next;
				    }
				    else {
                        if(sukuna1->energy > 0) sukuna1 =  sukuna1->prev;
				        if(sukuna2->energy  > 0) sukuna2 = sukuna2->next;
					}
				}
				// Swap for positive
                if(gojou1 != gojou2 && gojou2->next != gojou1) {
					if(gojou1->energy > 0 && gojou2->energy > 0) {
					    swap(gojou1, gojou2);
						this->list->swapAddress(gojou1,gojou2);
					    gojou1 = gojou1->prev;
					    gojou2 = gojou2->next;
				    }
				    else {
                        if(gojou1->energy < 0) gojou1 =  gojou1->prev;
				        if(gojou2->energy  < 0) gojou2 = gojou2->next;
					}
				}
			}
			if(sukuna2->next == sukuna1 && (sukuna1->energy < 0 && sukuna2->energy < 0)) {
				swap(sukuna1, sukuna2);
				this->list->swapAddress(sukuna1,sukuna2);
			}
			if(gojou2->next == gojou1 && (gojou1->energy > 0 && gojou2->energy > 0)) {
				swap(gojou1, gojou2);
				this->list->swapAddress(gojou1,gojou2);
			}
  		}
		customer* findMin(customer* start, customer* end) { // Tìm phần tử Min trong dãy con
			int minEnergy = start->energy;
			customer* temp = start;
			customer* min = start;
			do {
				temp = temp->next;
				if(minEnergy > temp->energy) {
					minEnergy = temp->energy;
					min = temp;
				}
			}
			while(temp != end);
			return min;
		}
		bool AllNegative() {
			customer* temp = this->x;
			for(int i = 0; i < this->count ; i++) {
				if(temp->energy > 0) return false;
				temp = temp->next;
			}
			return true;
		}
		void UNLIMITED_VOID()
		{
			if(this->count < 4) return;
			if(this->count == 4) {
				customer* min = findMin(x->prev,x->prev->prev);
				for(int i = 0; i < 4; i++) {
					min->print();
					min = min->next;
				}
			}
			else { 
				//TH1: Tìm dãy con nhỏ nhất có 4 phần tử bên trong dãy
				customer* temp = x->next->next->next; 
				customer* start = x;
				customer* tempS = x;
				customer* save = x;
				customer* end = temp;
				int mnum = 0;
				int num = 4; // Số phần tử của window
				int numT = 1; // Số phần tử con quá 4 (Nếu discard phần dương thì lấy phần này để giảm num)
				int curSum = x->energy
				+ x->next->energy
				+ x->next->next->energy
				+ x->next->next->next->energy; // Tổng 4 số đầu tiên
				int checkSum = x->energy; // Biến dùng để loại bỏ đi những phần tử không phù hợp
				int minSum = curSum;
				while(temp != x->prev) { // Start?
				    //if(temp == x->prev) flag = true;
					if(num >= 4) {
						if(checkSum > 0) { // Nếu có tổng dương trong dãy cần tìm
							curSum -= checkSum; // Discard phần dương
							tempS = save->next;
							num -= numT; // Điều chỉnh số phần tử dãy con
						    checkSum = 0; // Reset tổng check
						    numT = 0; // Reset phần tử con tạm
						}
						save = save->next;
						checkSum += save->energy;
						numT++;
					}
					temp = temp->next;
					curSum += temp->energy;
					num++;
					if(curSum < minSum || (curSum == minSum && mnum <= num)) {
						minSum = curSum;
						start = tempS; // Thay đổi phần tử đầu tiên dãy con (save = cái chỗ cần discard => save->next mới đúng)
						end = temp;
						mnum = num;
					}
					//if(flag && minSum > 0) break;
				}
				//TH2: Tìm dãy con nhỏ nhất nằm 2 bên của dãy
				// Tìm dãy con lớn nhất có số phần tử <= size - 4, ưu tiên lớn nhất
				// Sau đó lấy tổng các giá trị trừ đi phần min
				// Đem so sánh với phần min bên kia, thằng nào min hơn lấy thằng đó
				int totalSum = sum(), maxSum = INT32_MIN, Mcsum = 0, n = 0, Mnum = 0, b = 0;
				checkSum = 0;
				bool flag = true;
				temp = x->next; save = x->next;
				customer* mStart = x->next, *mEnd = x->next, *fake = x->next;
				for(int i = 1; i < this->count - 1; i++) {
					if(Mcsum <= 0) { // Bỏ phần âm
						Mcsum = temp->energy;
						n = 1;
						if(temp->energy > 0) {
							save = temp; // Save luôn là start của Mcsum
							checkSum = 0;
							fake = save;
							flag = true;
						}
					}
					else { 
						if(n < this->count - 4) {
							flag = true;
                            Mcsum += temp->energy;
					        n++;				
						}
						else {
							if(flag) {
								b = 0;
								fake = save;
								checkSum = 0;
								while(fake->energy > 0 && fake != temp) {
									b++;
									checkSum += fake->energy;
									fake = fake->next;
								}
								while ( fake->energy < 0 && fake != temp) {
									b++;
									checkSum += fake->energy;
									fake = fake->next;
								}
								if(fake == temp) {
									flag = false;
								}	
							}
							if(checkSum <= temp->energy && flag) {
									Mcsum += temp->energy - checkSum;
									n -= b;
							     	save = fake;
									flag = false;
								}
								else {
									Mcsum += temp->energy - save->energy; // Sliding window
						        	save = save->next;
								}
							if(Mcsum <= temp->energy) {
								flag = true;
								checkSum = 0;
								Mcsum = temp->energy;
								n = 1;
								save = temp;
								fake = save;
							}
						}
					}
					if((Mcsum > maxSum && n <= this->count - 4) || (Mcsum == maxSum && n <= this->count - 4 && n <= Mnum)) {
						maxSum = Mcsum;
						Mnum = n;
						mStart = save;
						mEnd = temp;
					}
					temp = temp->next;
				}
				Mnum = this->count - Mnum;
				int fSum = min(minSum, totalSum - maxSum); 
				if((fSum == totalSum - maxSum && (minSum != fSum)) || ((fSum == totalSum - maxSum) && (minSum == fSum) && Mnum >= mnum)) {
					start = mEnd->next;
					end = mStart->prev;
				}
				if(AllNegative()) {
					start = x->prev;
					end = start->prev;
				}
				// Tìm giá trị nhỏ nhất trong dãy con xong in từ đó
				customer* min = findMin(start, end);
				if(min == start) { // In khi vị trí min là start
				    if(end->next == start) {
						min->print();
						min = min->next;
					}
					while(min != end->next) {
						min->print();
						min = min->next;
					}
				}
				else { //  In khi vị trí min không là start
					bool flag = false;
					if(min == end) flag = true;
					customer* stop = min;
					min->print();
					min = min->next;
					while(min != stop) {
						if(min == end) {
							min->print();
							flag = true;
						}
						if(min == start) {
							flag = false;
						}
						if(!flag) min->print();
						min = min->next;
					}
				}
			}
		}
		int sum() { // Chỗ Chú linh chưa rõ
			int sumR = 0;
			for(int i = 0; i < this->count; i++) {
				sumR += this->x->energy;
				this->x = this->x->next;
			}
			return sumR;
		}
		void domainExpainsionDel1() { // Tiến hành đuổi oán linh trong nhà hàng	
			OrderList::Node* temp = this->list->head; // Đang đuổi theo chiều từ gần -> sớm
			int index = 0; // chỉnh luôn này
			while(temp != nullptr) {
				if(temp->address->energy < 0) {
					if(temp->inTable) {
						remove(temp->address);
					}
					else if(!temp->inTable && queue != nullptr){
						delete this->queue->newdequeue(temp->address);
					}
					temp = list->removeAt_DM(index, temp);
					continue;
				}
				temp = temp->next; // Chỉnh này để đổi chiều
				index++; // chỉnh luôn này
			}
		}
		void domainExpainsionDel2() { // Đuổi chú thuật sư
			OrderList::Node* temp = this->list->head; // Đang đuổi theo chiều từ gần -> sớm
			int index = 0; // chỉnh luôn này
			while(temp != nullptr) {
				if(temp->address->energy > 0) {
					if(temp->inTable) {
						remove(temp->address);
					}
					else if(!temp->inTable && queue != nullptr){
						delete this->queue->newdequeue(temp->address);
					}
					temp = list->removeAt_DM(index, temp);
					continue;
				}
				temp = temp->next; // Chỉnh này để đổi chiều
				index++; // chỉnh luôn này
			}
		}
		void DOMAIN_EXPANSION() //O(n)
		{
			if(this->count == 0) {
				if(this->queue == nullptr) return;
				if(this->queue->size == 0) return;
			}
			int total = sum();
			if(this->queue != nullptr) {
				total += this->queue->sumSub();
			}
			if(total >= 0) { // Đuổi oán linh
			    list->print_Domain_Expansion(1);
				domainExpainsionDel1(); 
			}
			else { // Đuổi chú thuật sư
			    list->print_Domain_Expansion(0);
				domainExpainsionDel2();
			}
			inviteQueue();
		}
		void LIGHT(int num) //O(n)
		{
			//cout << "light " << num << endl;
			if(num == 0) { // Print customers in queue
			    if(this->queue == nullptr) return;
			    customer* temp = this->queue->front;
				if(this->queue->size == 0) return;
				else if(this->queue->size == 1) {
					temp->print();
					return;
				}
				else {
					while(temp != queue->rear) {
						temp->print();
						temp = temp->prev;
					}
					temp->print(); // REAR
				}
			}
			else if(num < 0) {
				for(int i = 0; i < this->count; i++) {
					x->print();
					x = x->prev;
				}
			}
			else {
				for(int i = 0; i < this->count; i++) {
					x->print();
					x = x->next;
				}
			}
		}
};