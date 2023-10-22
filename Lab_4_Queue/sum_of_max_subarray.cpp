#include <iostream>
#include <vector>
#include <queue>
#include <deque>
using namespace std;
int sumOfMaxSubarray(vector<int>& nums, int k) {
    deque<int> q(k); // Mảng lưu index của giá trị lớn nhất mỗi mảng con
    int i;
    // Tìm phần tử lớn nhất trong mảng con đầu tiên (Sliding Window)
    for (i = 0; i < k; ++i) { 
        while ((!q.empty()) && nums[i] >= nums[q.back()])  q.pop_back();
        q.push_back(i);
    }
    int sum = 0; // Tổng trả zề
    for (; i < nums.size(); ++i) {
        sum += nums[q.front()];
        // Xóa phần tử trong q, đã ngoài tầm của window
        while ((!q.empty()) && q.front() <= i - k) q.pop_front(); 
        // Nếu phần tử hiện tại lớn hơn cái trong kia, cái đó cút 
        while ((!q.empty()) && nums[i] >= nums[q.back()]) q.pop_back();
        // Đưa index hiện tại vô cuối q
        q.push_back(i);
    }
    sum += nums[q.front()];
    return sum;
}
int main() {
    vector<int> nums {1, 2, 4, 3, 6};
    int k = 3;
    cout << sumOfMaxSubarray(nums, k);
}