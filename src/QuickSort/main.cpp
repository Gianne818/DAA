#include <iostream>
#include "quicksort.hpp"
using namespace std;

int main(){
    int size;
    cout << "Enter size of the array: ";
    cin >> size;

    int array[size];
    cout << "Enter the elements of the array: ";
    for(int i = 0; i < size; i++)
        cin >> array[i];

    quickSort(array, 0, size - 1);

    cout << "Sorted array: ";
    for(int i = 0; i < size; i++)
        cout << array[i] << ' ';
    return 0;
}