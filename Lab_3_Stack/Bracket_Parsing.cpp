#include <iostream>
#include <stack>
using namespace std;

bool isValidParentheses (string s){
    /*TODO*/
    stack<char> BracketPars;
    unsigned int i = 0;
    while(i != s.size()) {
        switch(s[i]) {
            case '(': {
                BracketPars.push(s[i]);
                break;
            }
            case '[': {
                BracketPars.push(s[i]);
                break;
            }
            case '{': {
                BracketPars.push(s[i]);
                break;
            }
            case ')': {
                if(BracketPars.empty()) return false;
                char check = BracketPars.top();
                if(check == '(') {
                    BracketPars.pop();
                    break;
                }
                else return false;
            }
            case ']': {
                if(BracketPars.empty()) return false;
                char check = BracketPars.top();
                if(check == '[') {
                    BracketPars.pop();
                    break;
                }
                else return false;
            }
            case '}': {
                if(BracketPars.empty()) return false;
                char check = BracketPars.top();
                if(check == '{') {
                    BracketPars.pop();
                    break;
                }
                else return false;
            }
        }
        i++;
    }
    if(BracketPars.empty()) return true;
    else return false;
}

int main() {
    cout << isValidParentheses("[]");
}