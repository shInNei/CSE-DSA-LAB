struct e {
    int index;
    int value;
    int frequenc;
};
bool cmp1(e a, e b){
    return a.value < b.value; 
}
bool cmp2(e a, e b) {
    if(a.frequenc != b.frequenc) return a.frequenc < b.frequenc;
    else return a.index > b.index;
}
void sortByFrequency(int arr[], int n){
    e element[n];
    for(int i = 0; i < n; i++) {
        element[i].index = i;
        element[i].value = arr[i];
        element[i].frequenc = 0;
    }
    stable_sort(element, element + n, cmp1);
    element[0].frequenc = 1;
    for(int i = 1; i < n; i++) {
        if(element[i].value == element[i-1].value) {
            element[i].frequenc += element[i-1].frequenc + 1;
            element[i-1].frequenc = -1;
            element[i].index = element[i-1].index; 
        }
        else element[i].frequenc = 1;
    }
    stable_sort(element, element + n, cmp2);
    for(int i = n - 1, index = 0; i >= 0; i--) {
        if(element[i].frequenc != -1) 
        for(int j = 0; j < element[i].frequenc; j++) arr[index++] = element[i].value;
    }
}
