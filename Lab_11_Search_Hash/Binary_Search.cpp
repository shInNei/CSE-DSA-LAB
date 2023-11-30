int binarySearch(int arr[], int left, int right, int x)
{
    if(left > right) return -1;
    int middle = left + (right - left)/2;
    cout << "We traverse on index: " << middle << endl;
    if(arr[middle] == x) return middle;
    else {
        if(x >= arr[middle]) return binarySearch(arr, middle + 1, right, x);
        else return binarySearch (arr, left, middle - 1, x);
    }
}
