#include <iostream>
#include <vector>
#include <queue>
using namespace std;

//Tạo 2 queue
void interleaveQueue(queue<int>& q){
    queue<int> odd;
    queue<int> even;
    unsigned int x, n = q.size();
    while(!q.empty()) {
        x = q.front();
        q.pop();
        if(q.size() >= n/2) odd.push(x);
        else even.push(x);
    }
    while(!odd.empty()) {
        q.push(odd.front());
        odd.pop();
        q.push(even.front());
        even.pop();
    }
}

int main() {
    queue<int> q;
    int n; cin >> n;
    for (int i = 0; i < n; i++){
        int element; cin >> element;
        q.push(element);
    }
    interleaveQueue(q);
    while (!q.empty()){
        cout << q.front() << ' ';
        q.pop();
    }   
}