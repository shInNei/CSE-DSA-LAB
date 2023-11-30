void reheapDown(int maxHeap[], int numberOfElements, int index)
{
    int lc = 2*index + 1;
    int rc = 2*index + 2;
    while(index < numberOfElements && lc < numberOfElements && rc < numberOfElements) {
        if(maxHeap[index] < maxHeap[lc] || maxHeap[index] < maxHeap[rc]) {
            int temp = maxHeap[index];
            if(maxHeap[lc] > maxHeap[rc]) {
                maxHeap[index] = maxHeap[lc];
                maxHeap[lc] = temp; 
                index = lc;
                lc = 2*index + 1;rc = 2*index + 2;
            }
            else {
                maxHeap[index] = maxHeap[rc];
                maxHeap[rc] = temp;
                index = rc;
                lc = 2*index + 1; rc = 2*index + 2;
            }
        }
        else return;
    }
}

void reheapUp(int maxHeap[], int numberOfElements, int index)
{
    if(index <= 0) return;
    int parent = (index - 1)/2;
    if(maxHeap[index] >= maxHeap[parent]) {
        int temp = maxHeap[parent];
        maxHeap[parent] = maxHeap[index];
        maxHeap[index] = temp;
        reheapUp(maxHeap, numberOfElements, parent);
    }
}