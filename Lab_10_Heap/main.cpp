int leastAfter(vector<int>& nums, int k) {
    // STUDENT ANSWER
    priority_queue<int,vector<int>,greater<int>> pq(nums.begin(), nums.end());
    for(int i = 0; i < k; i++) {
        int min = pq.top();
        pq.pop();
        pq.push(min*2);
    }
    return pq.top();
}