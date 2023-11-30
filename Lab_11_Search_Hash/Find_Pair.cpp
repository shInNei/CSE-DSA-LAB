bool findPairs(int arr[], int n, pair<int,int>& pair1, pair<int, int>& pair2)
{
   // TODO: If there are two pairs satisfy the condition, assign their values to pair1, pair2 and return true. Otherwise, return false.
   map<int, pair<int,int>> m;
   for(int i = 0; i < n - 1; ++i) {
       for(int j = i + 1; j < n; ++j) {
           int sum = arr[i] + arr[j];
           if(m.find(sum) == m.end()) m[sum] = make_pair(i,j);
           else {
               pair<int,int> p = m[sum];
               if(p.first != i && p.first != j && p.second != i && p.second != j) {
                   pair1 = make_pair(arr[p.first], arr[p.second]);
                   pair2 = make_pair(arr[i], arr[j]);
                   return true;
               }
           }
       }
   }
   return false;
}
