static void merge(T* left, T* middle, T* right){
    /*TODO*/
    T* subA1 = new T[middle - left + 1];
    T* subA2 = new T[right - middle];
    for(int i = 0; i < middle - left + 1; i++) subA1[i] = left[i];
    for(int i = 0; i < right-middle; i++) subA2[i] = middle[i+1];
      T k = 0;
      T j = 0;
      T p = 0;
      while (j < (middle - left + 1) && p < right - middle) {
          if(subA1[j] <= subA2[p]) {
              left[k] = subA1[j];
              j++;
          }
          else {
              left[k] = subA2[p];
              p++;
          }
          k++;
      }
      while(j < middle - left + 1) {
           left[k] = subA1[j];
           j++;
           k++;
      }
      while(p < right - middle) {
           left[k] = subA2[p];
           p++;
           k++;
      }
      Sorting::printArray(left, right);
}
static void mergeSort(T* start, T* end){
    /*TODO*/
    if(start >= end) return;
    T* mid = start + (end - start)/2;
    mergeSort(start, mid);
    mergeSort(mid+1, end);
    merge(start, mid, end);
}