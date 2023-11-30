#include <queue>
class PrinterQueue
{
private:
    // your attributes
    struct Req {
        int priority;
        string fileName;
        int order;
        bool operator < (const Req& r) const {
            if(priority != r.priority) return priority < r.priority;
            return order > r.order;
        }
    };
    priority_queue<Req> pq;
    int order = 0;
public:
    // your methods
    void addNewRequest(int priority, string fileName)
    {
        // your code here
        pq.push({priority, fileName, order++});
    }
    void print()
    {
        // your code here
        // After some logic code, you have to print fileName with endline 
        if (pq.empty()) cout << "No file to print\n";
        else {
            cout << pq.top().fileName << "\n";
            pq.pop();
        }
    }
};