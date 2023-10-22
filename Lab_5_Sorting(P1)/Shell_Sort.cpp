#ifndef SORTING_H
#define SORTING_H

#include <sstream>
#include <iostream>
#include <type_traits>
using namespace std;

template <class T>
class Sorting
{
private:
    static void printArray(T *start, T *end)
    {
        int size = end - start;
        for (int i = 0; i < size; i++)
            cout << start[i] << " ";
        cout << endl;
    }

public:
    // TODO: Write your code here
    static void sortSegment(T *start, T *end, int segment_idx, int cur_segment_total)
    {
        // TODO
        int current = segment_idx + cur_segment_total;
        while (current < end - start)
        {
            T key = start[current];
            int step = current - cur_segment_total;
            while (step >= 0 && key < start[step])
            {
                start[step + cur_segment_total] = start[step];
                step = step - cur_segment_total;
            }
            start[step + cur_segment_total] = key;
            current += cur_segment_total;
        }
    }
    static void ShellSort(T *start, T *end, int *num_segment_list, int num_phases)
    {
        // TODO
        // Note: You must print out the array after sorting segments to check whether your algorithm is true.
        if (start - end == 1)
        {
            Sorting<T>::printArray(start, end);
            return;
        }
        for (int i = num_phases - 1; i >= 0; i--)
        {
            int segment = 0;
            while (segment < num_segment_list[i])
            {
                sortSegment(start, end, segment, num_segment_list[i]);
                segment += 1;
            }
            cout << num_segment_list[i] << " segments: ";
            Sorting<T>::printArray(start, end);
        }
    }
};
#endif /* SORTING_H */
int main()
{
    int num_segment_list[] = {1, 3, 5};
    int num_phases = 3;
    int array[] = {10, 9, 8, 7, 6, 5, 4, 3, 2, 1};

    Sorting<int>::ShellSort(&array[0], &array[10], &num_segment_list[0], num_phases);
}