int interpolationSearch(int arr[], int left, int right, int x)
{
    if(left > right || arr[left] > x || arr[right] < x) return -1;
    int pos = left + ((x - arr[left])*(right - left)) / (arr[right] - arr[left]);
    if(pos < left) return -1;
    if(pos > right) return -1;
    cout << "We traverse on index: " << pos << endl;
    if(arr[pos] == x) return pos;
    else {
        if(x >= arr[pos]) return interpolationSearch(arr, pos + 1, right, x);
        else return interpolationSearch(arr, left, pos - 1, x);
    }
}