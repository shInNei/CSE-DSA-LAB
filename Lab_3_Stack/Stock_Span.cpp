#include <iostream>
#include <vector>
#include <stack>
using namespace std;

vector<int> stock_span(const vector<int>& ns) {
    vector<int> output;
    stack<int> stockSpan;
    int n = ns.size();
    
    for (int i = 0; i < n; i++) {
        while (!stockSpan.empty() && ns[stockSpan.top()] < ns[i]) {
            stockSpan.pop();
        }
        if (stockSpan.empty()) {
            output.push_back(i + 1);
        } else {
            output.push_back(i - stockSpan.top());
        }
        stockSpan.push(i);
    }
    return output;
}
