#include "main.h"
inline int MAXSIZE = 0;
/// Insert text here //
// Implement Huffman tree for customer encoding
class HuffNode {
public:
	virtual ~HuffNode() {}
	virtual int weight() = 0;
	virtual int hgt() = 0;
	virtual bool isLeaf() = 0;
};
class LeafNode : public HuffNode{ // Lưu kí tự
private:
	char key;
	int wgt;
	int height;
public:
	LeafNode(const char& key, int freq) { // Constructor Leaf Char
		this->key = key; this->wgt = freq; this->height = 0;
	}
	char getK() { return this->key;}
	int weight() { return this->wgt;}
	int hgt() {return this->height;}
	bool isLeaf() { return true;}
};
class IntlNode : public HuffNode {
private:
	HuffNode* lc;
	HuffNode* rc;
	int wgt;
	int height;
public:
	IntlNode(HuffNode* l, HuffNode* r) {
		this->wgt = l->weight() + r->weight();
		this->lc = l;
		this->rc = r;
		this->height = (l->hgt() > r->hgt())?l->hgt():r->hgt();
		++this->height; 
	}
	int weight() { return this->wgt;}
	int hgt() {return this->height;}
	void updateHgt() {
		this->height = (lc->hgt() > rc->hgt())?lc->hgt():rc->hgt();
		++this->height; 
	}
	bool isLeaf() { return false;}
	HuffNode * left() const { return this->lc;} // const?
	void setLeft(HuffNode* temp) {this->lc = temp;}
	HuffNode * right() const { return this->rc;}
	void setRight(HuffNode* temp) {this->rc = temp;}
};
class HuffTree { // Destructor không có xài clear
private:
	HuffNode* Root;
public:
	HuffTree(char& c, int freq) { // Leaf constructor
		Root = new LeafNode(c, freq);
	}
	// Internal node constructor
	HuffTree(HuffTree* l, HuffTree* r) {
		Root = new IntlNode(l->root(), r->root());
	}
	~HuffTree() {} // Destructor
	HuffNode* root() { return this->Root;} // Get root
	void setRoot(HuffNode* newRoot) {this->Root = newRoot;} // Set new root after rotate
	int weight() { return Root->weight();} // Root weight
	void clear(HuffNode* node) { // Chưa có set hgt = 0
		if(node == nullptr) return;
		if(!node->isLeaf()) {
			IntlNode* internal = static_cast<IntlNode*>(node);
			clear(internal->left()); // segment fault
			clear(internal->right());
		}
		delete node;
	}
	int getBalance(IntlNode* node) { // Chú ý hàm này
		if(!node || node->isLeaf()) return 0; // node->isLeaf() hơi vô nghĩa
		return node->left()->hgt() - node->right()->hgt();
	}
	IntlNode* rotateRight(IntlNode* root) {
		if(!root || root->isLeaf()) return root;
		IntlNode* newRoot = static_cast<IntlNode*>(root->left());
		// Xoay cây
		root->setLeft(newRoot->right());
		newRoot->setRight(root);
		// Update lại chiều cao của cây
		root->updateHgt();
		newRoot->updateHgt();
		return newRoot;
	}
	IntlNode* rotateLeft(IntlNode* root) {
		if(!root || root->isLeaf()) return root;
		IntlNode* newRoot = static_cast<IntlNode*>(root->right());
		// Xoay cây
		root->setRight(newRoot->left());
		newRoot->setLeft(root);
		// Update lại chiều cao của cây
		root->updateHgt();
		newRoot->updateHgt();
		return newRoot;
	}
};
struct Compare {
	bool operator() (pair<int, HuffTree*> a, pair<int, HuffTree*> b) {
		if(a.second->weight() != b.second->weight()) return a.second->weight() > b.second->weight();
		else return a.first > b.first;
	}
};
// Xây dựng cây Huff từ danh sách X
inline HuffTree* buildHuff(vector<pair<char,int>>& result) {
	priority_queue <pair<int, HuffTree*>, vector<pair<int, HuffTree*>>, Compare> forest; // create a min heap
	for(int i = 0; i < result.size(); i++) {
		HuffTree* tree = new HuffTree(result[i].first, result[i].second); 
		forest.push(make_pair(i, tree));
	}
	HuffTree* temp1 = nullptr, *temp2 = nullptr, *temp3 = nullptr;
	int size = forest.size();
	int k = 1, rotateCount = 0;
	stack <HuffNode*> nodeStack;
	while(forest.size() > 1) { // O(n)
		temp1 = forest.top().second;
		forest.pop();
		temp2 = forest.top().second;
		forest.pop();
		temp3 = new HuffTree(temp1, temp2);
		unordered_map<HuffNode*, HuffNode*> parentMap;
		HuffNode* root = temp3->root();
		nodeStack.push(temp3->root());
		while(!nodeStack.empty()) {
			if(rotateCount == 3) break;
			IntlNode* newNode = nullptr, *newNodeLeft = nullptr, *newNodeRight = nullptr;
			bool flag = false;
			HuffNode* node = nodeStack.top();
			if(node == temp3->root()) flag = true;
			nodeStack.pop();
			if(!node->isLeaf()) {
				newNode = static_cast<IntlNode*>(node);
				if(!newNode->left()->isLeaf()) newNodeLeft = static_cast<IntlNode*>(newNode->left());
				if(!newNode->right()->isLeaf()) newNodeRight = static_cast<IntlNode*>(newNode->right());
			}
			else continue;
			int balance = temp3->getBalance(newNode);
			if(balance > 1 && temp3->getBalance(newNodeLeft) >= 0) {
				++rotateCount;
				HuffNode* parent = parentMap[newNode];
				IntlNode* Rparent = static_cast<IntlNode*> (parent);
				IntlNode* temp = newNode;
				newNode = temp3->rotateRight(newNode);
				if(flag) {
					flag = false;
					temp3->setRoot(newNode);
				}
				else {
					if(Rparent->left() == temp) {
						Rparent->setLeft(newNode);
						parentMap[temp] = newNode;
						parentMap[newNode] = parent; 
						Rparent->updateHgt();
					}
					else if(Rparent->right() == temp) {
						Rparent->setRight(newNode);
						parentMap[temp] = newNode;
						parentMap[newNode] = parent; 
						Rparent->updateHgt();
					}
				}
			}
			else if(balance > 1 && temp3->getBalance(newNodeLeft) < 0) {
				++rotateCount;
				HuffNode* parent = parentMap[newNode];
				HuffNode* temp = newNode;
				IntlNode* Rparent = static_cast<IntlNode*> (parent);
				newNode->setLeft(temp3->rotateLeft(newNodeLeft));
				newNode->updateHgt();
				newNode = temp3->rotateRight(newNode);
				if(flag) {
					flag = false;
					temp3->setRoot(newNode);
				}
				else {
					if(Rparent->left() == temp) {
						Rparent->setLeft(newNode);
						parentMap[temp] = newNode;
						parentMap[newNode] = parent; 
						Rparent->updateHgt();
					}
					else if(Rparent->right() == temp) {
						Rparent->setRight(newNode);
						parentMap[temp] = newNode;
						parentMap[newNode] = parent; 
						Rparent->updateHgt();
					}
				}
			}
			else if(balance < -1 && temp3->getBalance(newNodeRight) <= 0) {
				++rotateCount;
				HuffNode* parent = parentMap[newNode];
				HuffNode* temp = newNode;
				IntlNode* Rparent = static_cast<IntlNode*> (parent);
				newNode = temp3->rotateLeft(newNode);
				if(flag) {
					flag = false;
					temp3->setRoot(newNode);
				}
				else {
					if(Rparent->left() && Rparent->left() == temp) {
						Rparent->setLeft(newNode);
						parentMap[temp] = newNode;
						parentMap[newNode] = parent; 
						Rparent->updateHgt();
					}
					else if(Rparent->right() == temp) {
						Rparent->setRight(newNode);
						parentMap[temp] = newNode;
						parentMap[newNode] = parent; 
						Rparent->updateHgt();
					}
				}
			}
			else if(balance < -1 && temp3->getBalance(newNodeRight) > 0){
				++rotateCount;
				HuffNode* parent = parentMap[newNode];
				HuffNode* temp = newNode;
				IntlNode* Rparent = static_cast<IntlNode*> (parent);
				newNode->setRight(temp3->rotateRight(newNodeRight));
				newNode->updateHgt();
				newNode = temp3->rotateLeft(newNode);
				if(flag) {
					flag = false;
					temp3->setRoot(newNode);
				}
				else {
					if(Rparent->left() == temp) {
						Rparent->setLeft(newNode);
						parentMap[temp] = newNode;
						parentMap[newNode] = parent; 
						Rparent->updateHgt();
					}
					else if(Rparent->right() == temp) {
						Rparent->setRight(newNode);
						parentMap[temp] = newNode;
						parentMap[newNode] = parent; 
						Rparent->updateHgt();
					}
				}
			}
			if(newNode->right()) {
				nodeStack.push(newNode->right());
				parentMap[newNode->right()] = newNode;
			}
			if(newNode->left()) {
				nodeStack.push(newNode->left());
				parentMap[newNode->left()] = newNode;
			}
		}
		forest.push(make_pair(size + k, temp3));
		rotateCount = 0;
		k++;
		delete temp1;
		delete temp2;
	}
	return temp3;
}
/// Insert text here ////
class Restaurant {
public:
	class BSTNode {
	public:
		int Key;
		int RESULT;
		BSTNode* lc;
		BSTNode* rc;
		friend class BST;
	public:
		BSTNode() {
			lc = rc = nullptr;
		}
		BSTNode(int RESULT, int Key, BSTNode* lc = nullptr, BSTNode* rc = nullptr) {
			this->RESULT = RESULT; // Biến Result, tương đương giá trị value của node
			this->Key = Key; // Copy biến key để phân biệt khách hàng
			this->lc = lc;
			this->rc = rc;
		}
		~BSTNode() {}
	};
	class BST {
	public:
		BSTNode* root;
		queue<pair<int,int>> FIFO;
		int nodeCount; // Số lượng Node có trong cây BST
	public:
		BST() {
			this->root = nullptr;
			this->nodeCount = 0;
		}
		~BST() {
			this->clear();
		}
		BSTNode* addHelp(BSTNode* root, int RESULT, int Key) {
			if(!root) root = new BSTNode (RESULT, Key);
			else if (RESULT < root->RESULT) {
				root->lc = addHelp(root->lc, RESULT, Key);
			}
			else if (RESULT >= root->RESULT) { //  Nếu giá trị bằng thì thêm vào bên phải của cây
				root->rc = addHelp(root->rc, RESULT, Key);
			}
			return root;
		}
		void add(int RESULT, int keyCount) {
			++this->nodeCount;
			FIFO.push(make_pair(RESULT, keyCount));
			this->root = addHelp(this->root, RESULT, keyCount); 
		}
		BSTNode* deleteHelp(BSTNode* root, int RESULT, int key) {
			if(!root) return root;
			if(root->RESULT > RESULT) {
				root->lc = deleteHelp(root->lc, RESULT, key);
				return root;	
			}
			else if (root->RESULT < RESULT) {
				root->rc = deleteHelp(root->rc, RESULT, key);
				return root;
			}
			else { // trường hợp 2 result bằng nhau
				if(root->Key != key) {
					root->rc = deleteHelp(root->rc, RESULT, key);
					return root;
				}
			}
				if(!root->lc) {
					BSTNode* temp = root->rc;
					delete root;
					return temp;
				}
				else if(!root->rc) {
					BSTNode* temp = root->lc;
					delete root;
					return temp;
				}
				else {
					BSTNode* temp = root;
					BSTNode* succ = root->rc;
					while(succ->lc != nullptr) { // Caution
						temp = succ;
						succ = succ->lc;
					}
					if(temp != root) {
						temp->lc = succ->rc;
					}
					else temp->rc = succ->rc;
					// Copy giá trị phần tử dưới lên phần tử trên
					root->RESULT = succ->RESULT;
					root->Key = succ->Key;
					delete succ;
					return root;
				}
		}
		void deleteNode(int RESULT, int key) {
			--this->nodeCount;
			this->root = deleteHelp(this->root, RESULT, key);
		}
		void clearHelp(BSTNode* root) {
			if(!root) return;
			clearHelp(root->lc);
			clearHelp(root->rc);
			delete root;
		}
		void clear() { // Đưa BST về lại vị trí ban đầu
			clearHelp(this->root);
			this->root = nullptr;
			this->nodeCount = 0;
			while(!FIFO.empty()) FIFO.pop();
		}
	};
	class Gojo {
	public:
		vector<BST*> HashTable;
		int capacity;
		int keyCount; // Chạy từ 0 -> inf
	public:
		Gojo() {
			this->capacity = MAXSIZE;
			this->HashTable.resize(capacity);
			for(int i = 0; i < this->capacity; ++i) {
				this->HashTable[i] = new BST();
			}
			this->keyCount = 0; // Set biến chạy bằng 0
		}
		~Gojo() {
			for(int i = 0; i < capacity; ++i) {
				delete HashTable[i];
			}
		}
		void insertCustomer(int ID, int RESULT) { // Thêm khách vào Hash Table
			this->HashTable[ID]->add(RESULT, this->keyCount);
			++this->keyCount; // Tăng biến chạy lên 1 đơn vị
		}
		void printInOrderG(BSTNode* root) {
			if(!root) return;
			printInOrderG(root->lc);
			cout << root->RESULT << "\n";
			printInOrderG(root->rc);
		}
		void LimitlessHelp(int& num) {
			// Nếu số khách tại vị trí num - 1 (nodecount) == 0 thì trả về
			// Không thì duyệt theo chiều Inorder rồi in "RESULT\n"
			if(this->HashTable[num-1]->nodeCount != 0) { 
				printInOrderG(this->HashTable[num-1]->root);
			} 
		}
	};
	class Sukuna {
	public:
		int enteringTime; // Thời gian đi vào min heap, càng nhỏ -> càng sớm  -> chưa được sử dụng lâu nhất
		int ID;
		int NUM;
		queue<int> area;
	public:
		Sukuna(int ID, int NUM, int RESULT): ID(ID), NUM(NUM), enteringTime(-1){
			this->area.push(RESULT);
		}
		~Sukuna() {
			this->clear();
		}
		bool isEmpty() {
			return this->NUM > 0 ? false : true;
		}
		void deleteNum(int num) {
			if(num >= NUM) {
				this->clear();
			}
			else {
				while(num > 0) {
					this->area.pop();
					--this->NUM;
					--num;
				}
			}
		}
		void clear() { // Xóa sạch mọi thứ tại khu vực Sukuna, đồng thời cập nhật lại thời gian
			while(!area.empty()) area.pop();
			this->NUM = 0;
			enteringTime = -1;
		}
	};
	class min_heap {
	public:
		int realtime; // Thời gian thực, chạy mỗi khi 1 phần tử được thêm vào min heap
		vector<Sukuna*> minheap;
		int capacity;
		int size;
	public:
		min_heap() {
			this->capacity = MAXSIZE;
			this->size = 0;
			this->minheap.resize(capacity);
			for(int i = 0; i < capacity; ++i) {
				this->minheap[i] = nullptr;
			}
			this->realtime = 0;
		}
		~min_heap() {
			for(int i = 0; i < this->capacity; ++i) {
				delete minheap[i];
				minheap[i] = nullptr;
			}
		}
		void push(Sukuna* item) {
			item->enteringTime = this->realtime; // Khởi trị thời gian đi vào =  thời gian thực
			this->minheap[this->size] = item; 
			++this->size;
			++this->realtime; // Tăng biến đếm thời gian thực
			this->reheapup(this->size - 1);
		}
		Sukuna* peek() { // Đảm bảo ko có empty mới xài nha
			return minheap[0];
		}
		bool isEmpty() {return !this->size ? true : false;}
		int getItem(int ID) { // Trả về index có chứa ID
			for(int i = 0; i < this->size; ++i) {
				if(ID == this->minheap[i]->ID) return i;
			}
			return -1;
		}
		Sukuna* pop() {
			if(this->isEmpty()) return nullptr;
			Sukuna* output = this->minheap[0];
			this->minheap[0] = this->minheap[this->size - 1];
			this->minheap[this->size-1] = nullptr;
			--this->size;
			this->reheapdown(0);
			return output;
		}
		void inviteCustomer(int index, int RESULT) {
			// Đưa customer vào queue
			// Tăng số lượng khách lên
			// Update thời gian đi vô
			this->minheap[index]->area.push(RESULT);
			++this->minheap[index]->NUM;
			this->minheap[index]->enteringTime = this->realtime; // Chỗ này không chắc
			++this->realtime; // Chỗ này không chắc nốt
			reheapdown(index);
		}
		void reheapup(int position) {
			if(position <= 0) return;
			int parent = (position - 1)/2;
			if((minheap[position]->NUM < minheap[parent]->NUM) 
			|| 
			(minheap[position]->NUM == minheap[parent]->NUM && minheap[position]->enteringTime < minheap[parent]->enteringTime) ) {
				// Time Complex: O(logn)
				// Num con < Num cha, hoán đổi vị trí của con và cha
				Sukuna* temp = minheap[parent];
				minheap[parent] = minheap[position];
				minheap[position] = temp;
				reheapup(parent);
			}
		}
		void reheapdown(int position) {
			// Time Complexity: O(logn)
			while(position < this->size) {
				int lc = 2 * position + 1;
				int rc = 2 * position + 2;
				// Khởi trị ví trị nhỏ nhất smllestP = vị trí của thằng cha
				int smllestP = position;

				// Nếu NUM con trái < NUM cha -> smllestP = con trái
				if(lc < this->size && minheap[lc]->NUM < minheap[smllestP]->NUM) smllestP = lc;
				// Nếu NUM con trái = NUM cha và con trái vô trễ hơn -> smllestP = con trái
				else if(lc < this->size 
				&& minheap[lc]->NUM == minheap[smllestP]->NUM 
				&& minheap[lc]->enteringTime < minheap[smllestP]->enteringTime) smllestP = lc;

				// Nếu NUM con phải < NUM smllestP (có thể cha hoặc con trái) -> smllestP = con phải
				if(rc < this->size && minheap[rc]->NUM < minheap[smllestP]->NUM) smllestP = rc;
				// Nếu Num con phải = NUM smllestP và con phải vô trễ hơn -> smllestP = con phải
				else if (rc < this->size
				&& minheap[rc]->NUM == minheap[smllestP]->NUM
				&& minheap[rc]->enteringTime < minheap[smllestP]->enteringTime) smllestP = rc;

				if(smllestP != position) { // Nếu smllestP không phải là cha
					// Thực hiện swap giữa smllestP và cha, tiếp tục reheapdown
					Sukuna* temp = minheap[smllestP];
					minheap[smllestP] = minheap[position];
					minheap[position] = temp;
					position = smllestP;
				} 
				else break; // Không break thì hết có thể reheapdown
			}
			
		}
	};
public: // My attributes go here
	min_heap* SukunaRestaurant;
	Gojo* GojoRestaurant;
	HuffTree* newestCustomer;
public:
	Restaurant() {
		this->SukunaRestaurant = new min_heap();
		this->GojoRestaurant = new Gojo();
		this->newestCustomer = nullptr;
	}
	~Restaurant() {
		delete SukunaRestaurant;
		delete GojoRestaurant;
		newestCustomer->clear(newestCustomer->root());
		delete newestCustomer;
	}
	static bool cmp(pair <char, int> a, pair <char, int> b) { 
		if(a.second == b.second) {
			if(islower(a.first) && islower(b.first)) {
				return a.first < b.first;
			} 
			else if (isupper(a.first) && isupper(b.first)) {
				return a.first < b.first;
			}
			else return islower(a.first);
		}
		return a.second < b.second;
	}
	vector<pair<char,int>> frequency_sort(string& name) {
		// Sort Frequency bằng map và pairs
		// Time complex: O(nlogn)
		// Space Aux: O(n)
		map <char, int> m;
		for(int i = 0; i < name.size(); i++) {
			m[name[i]] ++; // Giống key thì tăng value key đó lên 1
		}
		vector<pair<char, int>> result;
		for(map <char,int>::iterator it = m.begin(); it != m.end(); ++it) {
			result.push_back(*it);
		}
		caesar_encrypt(result, m, name);
		map<char, int> updated_m;
		for(int i = 0; i < result.size(); ++i) {
			updated_m[result[i].first] += result[i].second;
		}
		result.clear();
		m.clear();
		for(map <char,int>::iterator it = updated_m.begin(); it != updated_m.end(); ++it) {
			result.push_back(*it);
		}
		stable_sort(result.begin(), result.end(), cmp);
		return result;
	}
	void caesar_encrypt(vector<pair<char, int>>& result, map<char, int>& m, string& name) {
		//
		// Time complex: O(n)
		// Space Aux: O(1)
		int shift;
		for(int i = 0; i < name.size(); ++i) {
			shift = m[name[i]];
			if(isupper(name[i])) name[i] = (name[i] + shift - 'A') % 26 + 'A';
			else name[i] = (name[i] + shift - 'a') % 26 + 'a';
		}
		for(int i = 0; i < result.size(); ++i) {
			shift = result[i].second;
			if(isupper(result[i].first)) result[i].first = (result[i].first + shift - 'A') % 26 + 'A';
			else result[i].first = (result[i].first + shift - 'a') % 26 + 'a'; 
		}
	}
	bool checkValid(const string& name) { // Kiểm tra tên khách hàng có tối thiểu 3 kí tự khác nhau hay không
		unordered_set<char> checkList;
		for(int i = 0; i < name.size(); i++) {
			checkList.insert(name[i]);
		}
		return checkList.size() >= 3;
	}
	void generateHuffmanCodes(HuffNode* root, string str, unordered_map<char, string>& HuffCode) {
		if(!root) return;
		if(root->isLeaf()) {
			LeafNode* leaf = static_cast<LeafNode*>(root);
			HuffCode[leaf->getK()] = str;
			return;
		}
		IntlNode* internal = static_cast<IntlNode*>(root);
		generateHuffmanCodes(internal->left(), str + "0", HuffCode);
		generateHuffmanCodes(internal->right(), str + "1", HuffCode);
	}
	int binarytoDecimal(const string& temp) {
		// Time complex: O(n)
		int dec = 0;
		int base = 1; // 2^0
		for(int i = temp.size() - 1; i >= 0 ; --i) {
			if(temp[i] == '1') dec += base;
			base *= 2;
		}
		return dec;
	}
	void LAPSE(string name) {
		if(!checkValid(name)) return;
		vector<pair<char,int>> result = frequency_sort(name);
		int RESULT = 0;
		HuffTree* X = nullptr;
		if(result.size() > 1) {
			X = buildHuff(result);
			unordered_map<char, string> HuffCode;
			generateHuffmanCodes(X->root(), "", HuffCode);
			string temp = "";
			// Dịch tên sang mã nhị phân có tối đa 10 phần tử O(n)
			for(int i = 0; i < name.size(); ++i) {
				temp += HuffCode[name[i]];
			}
			cout << temp << "\n";
			if(temp.size() > 10) temp = temp.substr(temp.size() - 10);
			reverse(temp.begin(), temp.end());
			RESULT = binarytoDecimal(temp);
			cout << RESULT << "\n";
		}
		else { // Trường hợp cây có 1 nút
			RESULT = 0;
			X = new HuffTree(result[0].first, result[0].second);
		}
		int ID = RESULT % MAXSIZE + 1; // ID ứng với khu vực customer ngồi
		if(RESULT % 2 == 0) { // Sukuna
		int i = SukunaRestaurant->getItem(ID);
			if(i == -1) { // ID của khách không có trong nhà hàng của SUKUNA
				Sukuna* newArea = new Sukuna(ID, 1, RESULT);
				SukunaRestaurant->push(newArea);
			}
			else { // Nếu như đã tồn tại khu vực có ID tương tự với khách, i = ID
				SukunaRestaurant->inviteCustomer(i, RESULT);
			}
		}
		else { // GOJO
			this->GojoRestaurant->insertCustomer(ID - 1, RESULT); // Gojo nó lấy ID - 1 làm hash Table, muốn in ID thì lấy index + 1 
		}
		if(newestCustomer) { // Nếu có khách hàng vô từ trước, thì xóa cây của thằng đó đi
			newestCustomer->clear(newestCustomer->root());
			delete newestCustomer;
		}
		newestCustomer = X;
	} 
	void BSTtoArray(BSTNode* root, vector<pair<int,int>>& arr) {
		// Convert cây BST trở về thành mảng theo dạng preorder
		if(!root) return;
		arr.push_back({root->RESULT, root->Key});
		BSTtoArray(root->lc, arr);
		BSTtoArray(root->rc, arr);
	}
	bool isEqual(BSTNode* a, BSTNode* b) {
		// Dùng đệ quy, kiểm tra xem 2 cây có tương tự với nhau hay không?
		// Nếu cùng giá trị hoặc đều là null thì trả về true, else false
		if(!a && !b) return true;
		else if (a && b) {
			return a->RESULT == b->RESULT && a->Key == b->Key && isEqual(a->lc, b->lc) && isEqual(a->rc, b->rc);
		}
		else return false;
	}
	static bool compare(const pair<int,int>& a, const pair<int,int>& b) {
		if(a.first == b.first) return a.second < b.second;
		return a.first < b.first;
	}
	int countValidPermutations(BSTNode* root, vector<pair<int,int>> arr) {
		// Lưu ý mảng này cần phải được sort theo thứ tự ascending
		// Nếu ta có 2 giá trị result tương ứng, key của nó cũng phải được sorted theo ascending
		int count = 0;
		BST* newTree = new BST();
		do {
			if(root->Key != arr[0].second || root->RESULT != arr[0].first) continue;
			for(int i = 0; i < arr.size(); i++) {
				newTree->add(arr[i].first, arr[i].second);
			}
			if(isEqual(root, newTree->root)) ++count;
			newTree->clear(); // Xóa cây (khỏi cần lưu ý chỗ này nữa)
		} while(next_permutation(arr.begin(), arr.end()));
		delete newTree; newTree = nullptr;
		return count;
	}
	/* 				GIẢI THUẬT TÌM SỐ LÀN SẮP XẾP LẠI MẢNG ĐỂ RA CÂY FUCKING BST GOJO
	Tiền điều kiện: 1 mảng có thể sinh ra cây BST của Gojo (đi Preorder) với N phần tử
	Hậu điều kiện: Số cách Y
	Cơ sở: Dựa theo công thức đệ quy:
	// 			Số cách Y = 1, N <= 2 
	// 			Số cách Y = Số cách(Left)*Số cách(Right)* C(L)(L+R) 
	// * L + R  = N - 1
	// L: số phần tử của cây con bên trái
	// R: số phần tử của cây con bên phải
	Giải thuật:
	// B1:	sử dụng mảng 2 chiều để lưu tam giác pascal tối đa có N hàng (với N là size mảng), mục đích là để xác định combination nhanh sau mỗi lần gọi đệ quy
	// B2: sau đó sử dụng giải thuật DFS trong cây BST để chia ra thành 2 mảng chứa 2 cây con 
	// B3: dùng đệ quy cho công thức 
	*/
	void PascalTriangle(vector<vector<long long>>& pascalT, int N) {
		// i = số hàng
		for(int i = 0; i < N + 1; ++i) {
			pascalT[i] = vector<long long>(i + 1, 1); // hàng i có i+1 phần tử, khởi trị cho toàn bộ = 1
			for(int j = 1; j < i; ++j) {
				pascalT[i][j] = (pascalT[i - 1][j] + pascalT[i - 1][j - 1]); // Giá trị thằng hiện tại = 2 thằng trên cộng lại
			}
		}
	}
	long long int DFS(vector<pair<int,int>> arr, const vector<vector<long long>>& pascalT) {
		if(arr.size() <= 2) return 1 % MAXSIZE;
		vector<pair<int,int>> left, right;
		for(int i = 1; i < arr.size(); ++i) {
			if(arr[i].first < arr[0].first) left.push_back(arr[i]);
			else right.push_back(arr[i]);
		}
		return DFS(left, pascalT) * DFS(right, pascalT) * (pascalT[arr.size() - 1][left.size()] % MAXSIZE) % MAXSIZE; 
	}
	void KOKUSEN() {
		for(int i = 0; i < GojoRestaurant->capacity; ++i) {
			if(GojoRestaurant->HashTable[i]->nodeCount == 0 || GojoRestaurant->HashTable[i]->nodeCount == 1) continue;
			vector<pair<int,int>> arr;
			BSTtoArray(GojoRestaurant->HashTable[i]->root, arr);
			vector<vector<long long>> pascalT(arr.size() + 1);
			PascalTriangle(pascalT, arr.size());
			long long int Y = DFS(arr, pascalT);
			if(Y >= GojoRestaurant->HashTable[i]->nodeCount) {
				GojoRestaurant->HashTable[i]->clear();
			}
			else {
				while(Y > 0) {
					int result = GojoRestaurant->HashTable[i]->FIFO.front().first;
					int key = GojoRestaurant->HashTable[i]->FIFO.front().second;
					GojoRestaurant->HashTable[i]->FIFO.pop();
					GojoRestaurant->HashTable[i]->deleteNode(result, key);
					--Y;
				}
			}
		}
	}

	void KEITEIKEN(int num) {
		// Pop các node cần xóa tại root ra. Node tại root luôn có thời gian đi vào và NUM là nhỏ nhất
		// Sau đó tiến hành xóa tại các khu vực, sau khi xóa tại các khu vực, nếu khu vực vẫn còn thì tiến hành gắn vào lại
		queue<Sukuna*> order; 
		int loopCount = num >= SukunaRestaurant->size ? SukunaRestaurant->size : num;
		for(int i = 0; i < loopCount ; ++i) {
			order.push(SukunaRestaurant->pop());
		}
		while(!order.empty()) {
			Sukuna* area = order.front();
			order.pop();
			area->deleteNum(num);
			if(!area->isEmpty()) SukunaRestaurant->push(area);
			else {
				delete area;
				area = nullptr;
			}
		}
	}
	void printInOrder(HuffNode* root) {
		if (!root) return;
		if(!root->isLeaf()) {
			IntlNode* internal = static_cast<IntlNode*>(root);
			printInOrder(internal->left());
			cout << internal->weight() << "\n";
			printInOrder(internal->right());
		}
		else {
			LeafNode* leaf = static_cast<LeafNode*>(root);
			cout << leaf->getK() << "\n";
		}
	}
	void HAND() {
		this->printInOrder(this->newestCustomer->root());
	}
	void LIMITLESS(int num) {
		if(num > MAXSIZE || num < 1) return; // Num không phải là valid ID
		this->GojoRestaurant->LimitlessHelp(num);
	}
	
	void preOrderCleave(int index, int num) {
		stack<int> preorderlist;
		stack<int> printResult;
		preorderlist.push(index); // đưa index đầu tiên vào để duyệt
		while(!preorderlist.empty()) { // Duyệt preorder minheap
			index = preorderlist.top();
			queue<int> q = SukunaRestaurant->minheap[index]->area;
			preorderlist.pop();
			int left = 2*index+1;
			int right = 2*index+1;
			if(num >= SukunaRestaurant->minheap[index]->NUM) {
				while(!q.empty()) { // copy gia tri tu queue khu vuc cua Sukuna vao stack
					printResult.push(q.front());
					q.pop();
				}
			}
			else {
				int i = num;
				while(i > 0) {
					printResult.push(q.front());
					q.pop();
					--i;
				}
			}
			while(!printResult.empty()) {
				cout << SukunaRestaurant->minheap[index]->ID <<"-" << printResult.top();
				printResult.pop();
			}
			if(right < SukunaRestaurant->size) preorderlist.push(right);
			if(left < SukunaRestaurant->size) preorderlist.push(left);
		}
	}
	void CLEAVE(int num) { // Hàm có thể sửa lại
		this->preOrderCleave(0, num);
	}
};
inline void simulate(string filename)
{
	bool flag = false;
	Restaurant* r;
	ifstream ss(filename);
	string str, maxsize, name, num;
	while(ss >> str) {
		if(str == "MAXSIZE") {
			ss >> maxsize;
			MAXSIZE = stoi(maxsize);
			r = new Restaurant();
			flag = true;
		}
		else if(str == "LAPSE") {
			if(!flag) {
				throw "THERE IS NO MAXSIZE";
			}
			ss >> name;
			r->LAPSE(name);
		}
		else if(str == "KOKUSEN") {
			if(!flag) {
				throw "THERE IS NO MAXSIZE";
			}
			r->KOKUSEN();
		}
		else if(str == "KEITEIKEN") {
			if(!flag) {
				throw "THERE IS NO MAXSIZE";
			}
			ss >> num;
			r->KEITEIKEN(stoi(num));
		}
		else if(str == "HAND") {
			if(!flag) {
				throw "THERE IS NO MAXSIZE";
			}
			r->HAND();
		}
		else if(str == "LIMITLESS") {
			if(!flag) {
				throw "THERE IS NO MAXSIZE";
			}
			ss >> num;
			r->LIMITLESS(stoi(num));
		}
		else { // CLEAVE
			if(!flag) {
				throw "THERE IS NO MAXSIZE";
			}
			ss >> num;
			r->CLEAVE(stoi(num));
		}
	}
	delete r;
	return;
}
