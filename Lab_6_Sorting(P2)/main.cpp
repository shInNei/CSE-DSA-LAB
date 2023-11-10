string minDiffPairs(int* arr, int n){
    // STUDENT ANSWER
    sort(arr, arr + n);
    int minDiff = INT32_MAX;
    for(int i = 1; i < n; i++) {
        minDiff = min(minDiff, arr[i] - arr[i-1]);
    }
    stringstream ss;
    for(int i = 1; i < n; i++) {
        if(arr[i] - arr[i-1] == minDiff) ss << "(" << arr[i-1] << ", " << arr[i] << "), ";
    }
    string result = ss.str();
    result = result.substr(0, result.length() - 2);
    return result;
}