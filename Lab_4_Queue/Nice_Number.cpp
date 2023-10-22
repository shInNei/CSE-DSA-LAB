#include <iostream>
#include <vector>
#include <queue>
using namespace std;

long long nthNiceNumber(int n) {
    string nice = "";
    queue<string> q;
    q.push("2");
    q.push("5");
    while(n) {
        nice = q.front();
        q.pop();
        q.push(nice + "2");
        q.push(nice + "5");
        n--;
    }
    return stol(nice);
}
int main() {
    int n;
    cin >> n;
    cout << nthNiceNumber(n) << endl;
}