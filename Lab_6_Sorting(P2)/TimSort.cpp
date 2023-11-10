static void merge(T* start, T* middle, T* end) {
    // TODO
    T* left = start;
    T* right = end;
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
}

static void InsertionSort(T* start, T* end) {
    // TODO
    int length = end - start;
    for(int i = 0; i < length - 1; i++) {
        int smallest = i;
        for(int j = i+1; j < length; j++) {
            if(start[j] < start[smallest]) smallest = j;
        }
        swap(start[smallest], start[i]);
    }
}

static void TimSort(T* start, T* end, int min_size) {
    // TODO
    // You must print out the array after using insertion sort and everytime calling method merge.
    int length = end - start;
    for(int i = 0; i < end - start; i += min_size) {
        if(start + i + min_size < end) InsertionSort(start + i, start + i + min_size);
        else InsertionSort(start + i, end);
    }
    cout << "Insertion Sort: ";
    Sorting<T>::printArray(start,end);
    int i = 1;
    for(int size = min_size; size < length; size = size * 2) {
        for(int left = 0; left < length; left += size * 2, i++) {
            cout << "Merge " << i << ": ";
            int mid = (left + size - 1) < (end - start - 1) ? (left + size - 1) : (end - start - 1); 
            int right = left + 2 * size - 1 < length -1 ? left + 2 * size - 1 : length -1;
            if(mid < right) merge(&start[left], &start[mid], &start[right]);
            printArray(start, end);
        }
    }
    
}
