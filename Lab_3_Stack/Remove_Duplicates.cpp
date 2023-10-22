#include <iostream>
#include <list>
#include <stack>
using namespace std;

string reverse(string S) {
    for(unsigned int i = 0; i < S.length()/2; i++) {
        swap(S[i], S[S.length() - i - 1]);
    }
    return S;
}
string removeDuplicates(string S){
    /*TODO*/
    stack<char> checkDup;
    unsigned int i = 0;
    while(i != S.size()) {
        if(!checkDup.empty() && checkDup.top() == S[i]) checkDup.pop();
        else checkDup.push(S[i]);
        i++;
    }
    S = "";
    while(!checkDup.empty()) {
        S += checkDup.top();
        checkDup.pop();
    }
    return reverse(S);
}

int main() {
    cout << removeDuplicates("abbaca");
}