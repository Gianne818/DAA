#include <iostream>
#include "arraylist.hpp"
#include "linkedlist.hpp"
using namespace std;

void bubbleSort(List* list);
void selectionSort(List* list);
void insertionSort(List* list);

int main(){
    int s;
    cout << "Enter the number of elements: ";
    cin >> s;
    
    char choice;
    cout << "Enter A for arraylist, L for linkedlist: ";
    cin >> choice;
    
    List* list = nullptr;
    switch(choice){
        case 'A':
            list = new ArrayList();
            break;
        case 'L':
            list = new LinkedList();
            break;
        default:
            cout << "Error choice. Exiting...";
            return 0;
    }
    cout << "Enter the elements of the array: ";

    int temp;
    for(int i = 0; i<s; i++){
        cin >> temp;
        list->add(temp);
    }

    cout << "Enter sorting choice (B - bubble, S - selection, I - insertion, M - merge, Q - quick): ";
    char sortChoice;
    cin >> sortChoice;

    switch(sortChoice){
        case 'B':
            bubbleSort(list);
            break;
        case 'S':
            selectionSort(list);
            break;
        case 'I':
            insertionSort(list);
            break;
        case 'M':
            mergeSort(list, 0, list->size() - 1);
            break;
        case 'Q':
            quickSort(list, 0, list->size() - 1);
            break;
        default:
            cout << "Error choice. Exiting...";
            return 0;
    }

    cout << "Final result: ";
    list->print();
}

void bubbleSort(List* list){ //Best case if naay swapped flag, n, worst case n^2, n^2 swaps
    int s = list->size();
    for(int i = 0; i<s-1; i++){
        bool swapped = false;
        for(int j = 0; j<s-i-1; j++){
            if(list->get(j) > list->get(j+1)){
                list->swap(j, j+1);
                list->print();
                swapped = true;
            }
        }
        if(!swapped) break;
    }
}

void selectionSort(List* list){ //redeeming feature is that it has the least amount of swaps, n swaps
    int s = list->size();
    for(int i = 0; i<s-1; i++){
        int smallest = i;
        for(int j = i+1; j<s; j++){
            if(list->get(j) < list->get(smallest)){
                smallest = j;
            }
        }
        if(i!=smallest){
            list->swap(i, smallest);
            list->print();
        }
    }
}

void insertionSort(List* list){ //Best case is n, worst case is n^2, n^2 swaps
    int s = list->size();
    for(int i = 1; i<s; i++){
        int j = i;
        while(j>0 && list->get(j-1) > list->get(j)){
            list->swap(j, j-1);
            list->print();
            j--;
        }
    }
}

//==================== MERGE SORT ====================
/*
* VERY Inefficient for LinkedList, up to O(n^3logn) since we dont have a set(ind, val) function
 * for ArrayList, up tp O(n^2logn). 
 * swap() for ll is O(n), and get for ll is O(n)
 * 
 * * RUNTIME ANALYSIS (ArrayList):
 * - Overall: O(n^2 log n)
 * - Detail: The recursion depth is O(log n). However, because we lack a set() 
 * method, mergeArrays must "search and swap" to place values, making the 
 * merge step O(n^2) instead of O(n).
 *
 * RUNTIME ANALYSIS (LinkedList):
 * - Overall: O(n^3 log n)
 * - Detail: This is the "Worst Case" for this interface.
 * 1. get() takes O(n) to find values for temp arrays.
 * 2. The workaround search loop takes O(n).
 * 3. swap() takes O(n) to move nodes.
 * Since these are nested inside the merge loop, the merge step becomes O(n^3).
*/

void mergeArrays(List* list, int left, int mid, int right) {
    int leftSize = mid - left + 1;
    int rightSize = right - mid;

    // Temporary arrays to hold values
    int leftArr[leftSize];
    int rightArr[rightSize];

    // Copy data to temp arrays
    for (int i = 0; i < leftSize; i++) {
        leftArr[i] = list->get(left + i);
    }
    for (int i = 0; i < rightSize; i++) {
        rightArr[i] = list->get(mid + 1 + i);
    }

    int leftInd = 0;
    int rightInd = 0;
    int curArrIndex = left;

    // Merge back into the List using swap() as a workaround for set()
    while (leftInd < leftSize && rightInd < rightSize) {
        int targetVal;
        if (leftArr[leftInd] <= rightArr[rightInd]) {
            targetVal = leftArr[leftInd++];
        } else {
            targetVal = rightArr[rightInd++];
        }

        // Search for the targetVal in the unsorted portion of the list
        for (int k = curArrIndex; k <= right; k++) {
            if (list->get(k) == targetVal) {
                list->swap(curArrIndex, k);
                break;
            }
        }
        curArrIndex++;
    }

    //if there are remaining array values from left OR right parts, add them back.
    //usually only one element left for either of them, or none.
    while (leftInd < leftSize) {
        int targetVal = leftArr[leftInd++];
        for (int k = curArrIndex; k <= right; k++) {
            if (list->get(k) == targetVal) {
                list->swap(curArrIndex, k);
                break;
            }
        }
        curArrIndex++;
    }

    while (rightInd < rightSize) {
        int targetVal = rightArr[rightInd++];
        for (int k = curArrIndex; k <= right; k++) {
            if (list->get(k) == targetVal) {
                list->swap(curArrIndex, k);
                break;
            }
        }
        curArrIndex++;
    }
}

void mergeSort(List* list, int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;

        // Recursive split
        mergeSort(list, left, mid);
        mergeSort(list, mid + 1, right);

        // Merge the sorted halves
        mergeArrays(list, left, mid, right);
    }
}


//==================== QUICK SORT ====================
/*
* get() and swap() is still O(n) for linked list
* RUNTIME ANALYSIS (ArrayList):
* - Average/Best: O(n log n)
* - Worst: O(n^2) [Occurs with sorted/reverse-sorted data]
* - Efficiency: High, as get() and swap() are O(1).
* RUNTIME ANALYSIS (LinkedList):
* - Average/Best: O(n^2 log n) 
* - Worst: O(n^3)
* - Note: The O(n^2 log n) is because the partition loop runs 'n' times, 
* and inside it, get(i) and swap(i, low) each take O(n) to walk the nodes.
*/


int partition(List* list, int left, int right) {
    int pivot = list->get(right); 
    int low = left;

    for (int i = left; i < right; i++) {
        if (pivot > list->get(i)) { 
            if (i != low) {
                list->swap(i, low); 
            }
            low++;
        }
    }
    list->swap(right, low);
    return low;
}

void quickSort(List* list, int left, int right) {
    if (left < right) {
        int partitionIndex = partition(list, left, right);
        quickSort(list, left, partitionIndex - 1);
        quickSort(list, partitionIndex + 1, right);
    }
}
