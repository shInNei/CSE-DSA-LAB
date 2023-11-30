int jumpSearch(int arr[], int x, int n) {
    // TODO: print the traversed indexes and return the index of value x in array if x is found, otherwise, return -1.
   int i = 0;
   int step = sqrt(n);
   int last = 0;
   for(i = 0; i < n; i += step) {
	   if(arr[i] <= x) last = i;
	   if(x == arr[i]) {
		cout << i;
		return i;
	   }
	   cout << i << " ";
       if(x < arr[i] ) break;
   }
   if(n-1 < last) return -1;
   for(int k = last; k < i; k++) {
       if(arr[k] == x) {
           cout << k;
           return k;
       }
       if(k != last) cout << k << " ";
       if(arr[k] > x) break;
   }
   return -1;
}