#include <iostream>
#include <stack>

using namespace std;
//sử dụng hàm isdigit
int baseballScore(string ops){
/*TODO*/
stack<int> stack;
for(unsigned int i = 0; i < ops.size(); i++) {
    if(isdigit(ops[i])) stack.push(ops[i] -'0');
    if(ops[i] == 'D' && !stack.empty()) {
        int num = stack.top();
        num *= 2;
        stack.push(num);
    }
    if(ops[i] == 'C' && !stack.empty()) {
        stack.pop();
    }
    if(ops[i] == '+') {
        int num1 = stack.top();
        stack.pop();
        int num2 = stack.top();
        stack.push(num1);
        stack.push(num1+num2);
    }
}
int sum = 0;
while (!stack.empty()) {
    sum += stack.top();
    stack.pop();
}
return sum;
} 
int main()
{
    cout << baseballScore("52CD+");
}