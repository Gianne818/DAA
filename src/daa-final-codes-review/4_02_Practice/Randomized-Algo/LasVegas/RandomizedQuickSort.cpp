#include <bits/stdc++.h>
using namespace std;

int partition(vector<int>& arr, int low, int high) {
    int pivot = arr[high];
    int i = low - 1;
    
    for (int j = low; j < high; j++) {
        if (arr[j] <= pivot) {
            i++;
            swap(arr[i], arr[j]);
        }
    }
    swap(arr[i + 1], arr[high]);
    return i + 1;
}

int randomPartition(vector<int>& arr, int low, int high) {
    int randomIndex = low + rand() % (high - low + 1);
    swap(arr[randomIndex], arr[high]);
    return partition(arr, low, high);
}

void randomizedQuickSort(vector<int>& arr, int low, int high) {
    if (low < high) {
        int pi = randomPartition(arr, low, high);
        randomizedQuickSort(arr, low, pi - 1);
        randomizedQuickSort(arr, pi + 1, high);
    }
}

int main() {
    srand(time(0));
    
    vector<int> arr = {10, 7, 8, 9, 1, 5};
    int n = arr.size();
    
    randomizedQuickSort(arr, 0, n - 1);
    
    cout << "Sorted array: ";
    for (int x : arr)
        cout << x << " ";
    cout << endl;
    
    return 0;
}

/*
AVERAGE TIME: O(n log n)
    worst-case O(n²) (extremely rare, probability ~0)
SPACE: O(n) worst-case (recursion stack)

*/