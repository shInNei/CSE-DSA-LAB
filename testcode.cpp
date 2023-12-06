#include "main.h"
inline int MAXSIZE;
/// Insert text here //
// Implement Huffman tree for customer encoding
class HuffNode {
public:
	virtual ~HuffNode() {}
	virtual char getK() = 0;
	virtual int weight() = 0;
	virtual HuffNode* left() const = 0;
	virtual void setLeft(HuffNode*) = 0;
	virtual HuffNode* right() const = 0;
	virtual void setRight(HuffNode*) = 0;
	virtual bool isLeaf() = 0;
};
class LeafNode : public HuffNode{ // Lưu kí tự
private:
	char key;
	int wgt;
	int height;
public:
	LeafNode(const char& key, int freq) { // Constructor Leaf Char
		this->key = key; this->wgt = freq;
	}
	char getK() { return this->key;}
	int weight() { return this->wgt;}
	HuffNode* left() const { return nullptr;}
	void setLeft(HuffNode*) {} void setRight(HuffNode*) {} // Do nothing here
	HuffNode* right() const { return nullptr;}
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
	}
	char getK() {return '\0';}
	int weight() { return this->wgt;}
	bool isLeaf() { return false;}
	HuffNode * left() const { return this->lc;} // const?
	void setLeft(HuffNode* temp) {this->lc = temp;}
	HuffNode * right() const { return this->rc;}
	void setRight(HuffNode* temp) {this->rc = temp;}
};
class HuffTree {
private:
	HuffNode* Root;
	int hgt;
public:
	HuffTree(char& c, int freq) { // Leaf constructor
		Root = new LeafNode(c, freq);
		this->hgt = 1;
	}
	// Internal node constructor
	HuffTree(HuffTree* l, HuffTree* r) {
		Root = new IntlNode(l->root(), r->root());
		this->hgt = (l->getHeight() > r->getHeight())?l->getHeight():r->getHeight();
		this->hgt += 1; // H new = max(Hleft, Hright) + 1;
	}
	~HuffTree() { // Destructor
		this->hgt = 0;
		clear(this->Root);
	} 
	HuffNode* root() { return this->Root;} // Get root
	void setRoot(HuffNode* newRoot) {this->Root = newRoot;} // Set new root after rotate
	int weight() { return Root->weight();} // Root weight
	void clear(HuffNode* node) { // Chưa có set hgt = 0
		if(node == nullptr) return;
		clear(node->left()); // segment fault
		clear(node->right());
		delete node;
	}
	int getHeight() {return this->hgt;}
	HuffNode* rotateRight(HuffNode* root) {
		if(!root || root->isLeaf()) return root;
		HuffNode* newRoot = root->left();
		root->setLeft(newRoot->right());
		newRoot->setRight(root);
		return newRoot;
	}
	HuffNode* rotateLeft(HuffNode* root) {
		if(!root || root->isLeaf()) return root;
		HuffNode* newRoot = root->right();
		root->setRight(newRoot->left());
		newRoot->setLeft(root);
		return newRoot;
	}
	bool checkLeftofRight(HuffNode* root, int count) {
		// Sau khi root chạm lá ngoài cùng bên phải, nếu chiều cao chưa bằng count + 1 là left of right
		// Không thì right of right
		if(root->isLeaf()) { 
			if(this->hgt == count + 1) return false;
			else if(this->hgt != count + 1) return true;
		}
		return checkLeftofRight(root->right(), ++count);
	}
	bool checkRightofLeft(HuffNode* root, int count) {
		// Sau khi root chạm lá ngoài cùng bên phải, nếu chiều cao chưa bằng count + 1 là right of left
		// Không thì left of left 
		if(root->isLeaf()) { 
			if(this->hgt == count + 1) return false;
			else if(this->hgt != count + 1) return true;
		}
		return checkRightofLeft(root->left(), ++count);
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
	int k = 1;
	while(forest.size() > 1) { // O(n)
		temp1 = forest.top().second;
		forest.pop();
		temp2 = forest.top().second;
		forest.pop();
		temp3 = new HuffTree(temp1, temp2);
		if(temp1->getHeight() - temp2->getHeight() <= -2) { // Cây con bên phải bị lệch
			if(temp3->checkLeftofRight(temp3->root(), 0)) {
				temp3->root()->setRight(temp3->rotateRight(temp3->root()->right()));
				temp3->setRoot(temp3->rotateLeft(temp3->root()));
			}
			else {
				temp3->setRoot(temp3->rotateLeft(temp3->root()));
			}
		}
		else if(temp1->getHeight() - temp2->getHeight() >= 2) { // Cây con bên trái bị lệch
			if(temp3->checkRightofLeft(temp3->root(), 0)) {
				temp3->root()->setLeft(temp3->rotateLeft(temp3->root()->left()));
				temp3->setRoot(temp3->rotateRight(temp3->root()));
			}
			else {
				temp3->setRoot(temp3->rotateRight(temp3->root()));
			}
		}
		forest.push(make_pair(size + k, temp3));
		k++;
		delete temp1;
		delete temp2;
	}
	return temp3;
}
/// Insert text here ////
class Restaurant {
public:
	class customer {
	public:
		HuffTree* Htree; // Không biết có nên bỏ không nha?
		unordered_map<char,string> Hcode;
		int result;
	public:
		customer(HuffTree* Htree, unordered_map<char,string> Hcode, int result) {
			this->Htree = Htree;
			this->Hcode = Hcode;
			this->result = result;
		}
		~customer() {

		}
	};
	class BSTNode {
	public:
		int RESULT;
		BSTNode* lc;
		BSTNode* rc;
		friend class BST;
	public:
		BSTNode() {
			lc = rc = nullptr;
		}
		BSTNode(int RESULT, BSTNode* lc = nullptr, BSTNode* rc = nullptr) {
			this->RESULT = RESULT;
			this->lc = lc;
			this->rc = rc;
		}
		~BSTNode() {

		}
	};
	class BST {
	public:
		BSTNode* root;
		queue<int> FIFO;
		int nodeCount; // Số lượng Node có trong cây BST
	public:
		BST() {
			this->root = nullptr;
			this->nodeCount = 0;
		}
		~BST() {}
		BSTNode* addHelp(BSTNode* root, int RESULT) {
			if(!root) root = new BSTNode (RESULT);
			else if (RESULT < root->RESULT) {
				root->lc = addHelp(root->lc, RESULT);
			}
			else if (RESULT >= root->RESULT) {
				root->rc = addHelp(root->rc, RESULT);
			}
			return root;
		}
		void add(int RESULT) {
			++this->nodeCount;
			this->root = addHelp(this->root, RESULT);
		}
		BSTNode* deleteHelp(BSTNode* root, int RESULT) {
			if(!root) return root;
			if(root->RESULT > RESULT) {
				root->lc = deleteHelp(root->lc, RESULT);
				return root;	
			}
			else if (root->RESULT < RESULT) {
				root->rc = deleteHelp(root->rc, RESULT);
				return root;
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
					root->RESULT = succ->RESULT;
					delete succ;
					return root;
				}
		}
		void deleteNode(int RESULT) {
			--this->nodeCount;
			this->root = deleteHelp(this->root, RESULT);
		}
	};
	class Gojo {
	public:
		BST** HashTable;
		int capacity;
	public:
		Gojo() {
			this->capacity = MAXSIZE;
			this->HashTable = new BST*[capacity]; // MaxSize
		}
		~Gojo() {
			
		}
		void insertCustomer(int& ID, int& RESULT) { // Thêm khách vào Hash Table
			this->HashTable[ID]->add(RESULT);
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
		int enteringTime; // Thời gian đi vào min heap, càng nhỏ -> càng sớm -> càng lớn hơn
		int ID;
		int NUM;
		queue<customer*> area;
	public:
		Sukuna(): ID(0), NUM(0), enteringTime(-1){}
		Sukuna(int ID, int NUM, customer* r): ID(ID), NUM(NUM), enteringTime(-1){
			this->area.push(r);
		}
		~Sukuna() {}
	};
	class min_heap {
	public:
		int realtime; // Thời gian thực, chạy mỗi khi 1 phần tử được thêm vào min heap
		Sukuna* minheap;
		int capacity;
		int size;
	public:
		min_heap() {
			this->capacity = MAXSIZE;
			this->size = 0;
			this->minheap = new Sukuna[capacity];
			this->realtime = 0;
		}
		~min_heap() {
			delete [] minheap;
		}
		void push(Sukuna item) {
			item.enteringTime = this->realtime; // Khởi trị thời gian đi vào =  thời gian thực
			this->minheap[this->size] = item; 
			++this->size;
			++this->realtime; // Tăng biến đếm thời gian thực
			this->reheapup(this->size - 1);
		}
		Sukuna peek() { // Đảm bảo ko có empty mới xài nha
			return minheap[0];
		}
		bool isEmpty() {return !this->size ? true : false;}
		int getItem(int ID) { // Trả về index có chứa ID
			for(int i = 0; i < this->size; ++i) {
				if(ID == this->minheap[i].ID) return i;
			}
			return -1;
		}
		void inviteCustomer(int index, customer* r) {
			// Đưa customer vào queue
			// Tăng số lượng khách lên
			// Update thời gian đi vô
			this->minheap[index].area.push(r);
			++this->minheap[index].NUM;
			this->minheap[index].enteringTime = this->realtime; // Chỗ này không chắc
			++this->realtime; // Chỗ này không chắc nốt
			reheapdown(index);
		}
		void reheapup(int position) {
			if(position <= 0) return;
			int parent = (position - 1)/2;
			if((minheap[position].NUM < minheap[parent].NUM) 
			|| 
			(minheap[position].NUM == minheap[parent].NUM && minheap[position].enteringTime > minheap[parent].enteringTime) ) {
				// Time Complex: O(logn)
				// Num con < Num cha, hoán đổi vị trí của con và cha
				Sukuna temp = minheap[parent];
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
				if(lc < this->size && minheap[lc].NUM < minheap[smllestP].NUM) smllestP = lc;
				// Nếu NUM con trái = NUM cha và con trái vô trễ hơn -> smllestP = con trái
				else if(lc < this->size 
				&& minheap[lc].NUM == minheap[smllestP].NUM 
				&& minheap[lc].enteringTime > minheap[smllestP].enteringTime) smllestP = lc;

				// Nếu NUM con phải < NUM smllestP (có thể cha hoặc con trái) -> smllestP = con phải
				if(rc < this->size && minheap[rc].NUM < minheap[smllestP].NUM) smllestP = rc;
				// Nếu Num con phải = NUM smllestP và con phải vô trễ hơn -> smllestP = con phải
				else if (rc < this->size
				&& minheap[rc].NUM == minheap[smllestP].NUM
				&& minheap[rc].enteringTime > minheap[smllestP].enteringTime) smllestP = rc;

				if(smllestP != position) { // Nếu smllestP không phải là cha
					// Thực hiện swap giữa smllestP và cha, tiếp tục reheapdown
					Sukuna temp = minheap[smllestP];
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
	vector<pair<char,int>> frequency_sort(string name) {
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
		result = caesar_encrypt(result);
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
		for(int i = 0; i < result.size(); i++) {
			cout << result[i]. first << ": " << result[i].second << endl;
		}
		return result;
	}
	vector<pair<char,int>> caesar_encrypt(vector<pair<char, int>>& result) {
		//
		// Time complex: O(n)
		// Space Aux: O(1)
		int shift;
		for(int i = 0; i < result.size(); i++) {
			shift = result[i].second;
			if(isupper(result[i].first)) result[i].first = (result[i].first + shift - 'A') % 26 + 'A';
			else result[i].first = (result[i].first + shift - 'a') % 26 + 'a'; 
		}
		return result;
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
		if(root->isLeaf()) HuffCode[root->getK()] = str;
		generateHuffmanCodes(root->left(), str + "0", HuffCode);
		generateHuffmanCodes(root->right(), str + "1", HuffCode);
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
		HuffTree* X = buildHuff(result);
		unordered_map<char, string> HuffCode;
		generateHuffmanCodes(X->root(), "", HuffCode);
		string temp = "";
		// Dịch tên sang mã nhị phân có tối đa 10 phần tử O(n)
		for(int i = 0; i < name.size(); ++i) {
			temp += HuffCode[name[i]];
			if(temp.size() > 10) {
				temp = temp.substr(0,10);
				break;
			}
		}
		int RESULT = binarytoDecimal(temp);
		int ID = RESULT % MAXSIZE + 1; // ID ứng với khu vực customer ngồi
		customer* r = new customer(X, HuffCode, RESULT);
		if(RESULT % 2 == 0) { // Sukuna
		int i = SukunaRestaurant->getItem(ID);
			if(i == -1) { // ID của khách không có trong nhà hàng của SUKUNA
				Sukuna newArea = Sukuna(ID, 1, r);
				SukunaRestaurant->push(newArea);
			}
			else { // Nếu như đã tồn tại khu vực có ID tương tự với khách, i = ID
				SukunaRestaurant->inviteCustomer(i, r);
			}
		}
		else { // GOJO
			this->GojoRestaurant->insertCustomer(ID, RESULT);
		}

	}

	void KOKUSEN() {

	}
	void KEITEIKEN(int num) {

	}
	void printInOrder(HuffNode* root) {
		if (!root) return;
		printInOrder(root->left());
		if(!root->isLeaf()) {
			cout << root->weight() << "\n" ;
		}
		else {
			cout << root->getK() << "\n";
		}
		printInOrder(root->right());
	}
	void HAND() {
		this->printInOrder(this->newestCustomer->root());
	}
	void LIMITLESS(int num) {
		if(num > MAXSIZE || num < 1) return; // Num không phải là valid ID
		this->GojoRestaurant->LimitlessHelp(num);
	}
	void CLEAVE(int num) {
		
	}
};
inline void simulate(string filename)
{
	Restaurant* r = new Restaurant();
	ifstream ss(filename);
	string str, maxsize, name, num;
	while(ss >> str) {
		if(str == "MAXSIZE") {
			ss >> maxsize;
			MAXSIZE = stoi(maxsize);
		}
		else if(str == "LAPSE") {
			ss >> name;
			r->LAPSE(name);
		}
		else if(str == "KOKUSEN") {
			r->KOKUSEN();
		}
		else if(str == "KEITEIKEN") {
			ss >> num;
			r->KEITEIKEN(stoi(num));
		}
		else if(str == "HAND") {
			r->HAND();
		}
		else if(str == "LIMITLESS") {
			ss >> num;
			r->LIMITLESS(stoi(num));
		}
		else { // CLEAVE
			ss >> num;
			r->CLEAVE(stoi(num));
		}
	}
	delete r;
	return;
}
