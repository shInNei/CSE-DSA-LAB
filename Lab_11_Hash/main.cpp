int pairMatching(vector<int>& nums, int target) {
    unordered_map<int, int> m;
    int pairs = 0;
    for(int i = 0; i < int(nums.size()); ++i) {
        if(m[target - nums[i]] > 0) {
            ++pairs;
            --m[target - nums[i]];
        }
        else {
            ++m[nums[i]];
        }
    }
    return pairs;
}