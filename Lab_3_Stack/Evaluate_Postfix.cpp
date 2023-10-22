#include <iostream>
#include <stack>

using namespace std;
// iostream, stack and vector are included
int evaluatePostfix(string expr){
    /*TODO*/
    stack<string> Postfix;
    int b = 0, c = 0;
    string a = "";
    unsigned int i = 0;
    while(i != expr.size()) {
        if(expr[i] == ' ') i++;
        else if(expr[i] >= '0' && expr[i] <= '9') {
            while(expr[i] != ' ') {
                a += expr[i];
                i++;
            }
            Postfix.push(a);
            a = "";
            i++;
        }
        else {
            b = stoi(Postfix.top());
            Postfix.pop();
            c = stoi(Postfix.top());
            Postfix.pop();
            switch(expr[i]) {
                case '+': {
                b = b + c;
                break;
                }
                case '-': {
                b = c - b;
                break;    
                }
                case '*': {
                b = b * c;
                break;
                }
                case '/': {
                b = c / b;
                break;
                }
            }
            a = std::to_string(b);
            Postfix.push(a);
            a = "";
            i++;
        }
    }
    a = Postfix.top();
    Postfix.pop();
    return stoi(a);
}
int main() {
    cout << evaluatePostfix("2 3 1 * + 9 -");
}