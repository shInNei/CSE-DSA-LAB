#include <iostream>
#include <stack>
#include <vector>
using namespace std;
// iostream, stack and vector are included
vector<int> nextGreater(vector<int>& arr){
    for(int i = 0; i < arr.size() - 1; i++) {
        for(int j = i+1; j < arr.size(); j++) {
            if(arr[j] >= arr[i]) {
                arr[i] = arr[j];
                break;
            }
            if(j == arr.size() - 1) arr[i] = -1;
        }
    }
    arr[arr.size() - 1] = -1;
    return arr;
}
int main() {
    int N;
    cin >> N;
    vector<int> nums(N);
    for(int i = 0; i < N; i++) cin >> nums[i];
    vector<int> greaterNums = nextGreater(nums);
    for(int i : greaterNums) 
        cout << i << ' ';
    cout << '\n';
}