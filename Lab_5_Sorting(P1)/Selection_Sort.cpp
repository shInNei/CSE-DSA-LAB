#include <iostream>
using namespace std;

template <class T>
class Sorting
{
public:
    /* Function to print an array */
    static void printArray(T *start, T *end)
    {
        int size = end - start;
        for (int i = 0; i < size - 1; i++)
            cout << start[i] << ", ";
        cout << start[size - 1];
        cout << endl;
    }

    static void selectionSort(T *start, T *end);
};
// Student Answer
template <class T>
void Sorting<T>::selectionSort(T *start, T *end)
{
    int length = end - start;
    for(int i = 0; i < length - 1; i++) {
        int smallest = i;
        for(int j = i+1; j < length; j++) {
            if(start[j] < start[smallest]) smallest = j;
        }
        swap(start[smallest], start[i]);
        Sorting<T>::printArray(start,end);
    }
}
//
int main() {
    int arr[] = {9, 2, 8, 1, 0, -2};
    Sorting<int>::selectionSort(&arr[0], &arr[6]);
}