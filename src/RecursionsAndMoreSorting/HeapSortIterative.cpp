#include <algorithm>
#include <iostream>
using namespace std;

void heapify(int arr[], int n, int i) {
    int largest = i, 
    left = 2 * i + 1, 
    right = 2 * i + 2;

    if (left < n && arr[left] > arr[largest])
        largest = left;

    if (right < n && arr[right] > arr[largest])
        largest = right;

    if (largest != i) {
        swap(arr[i], arr[largest]);
        heapify(arr, n, largest);
    }
}

void buildHeap(int arr[], int n) {
    for (int i = n / 2 - 1; i >= 0; i--)
        heapify(arr, n, i);

}
void heapSort(int arr[], int n) {
    buildHeap(arr, n);
    for (int i = n - 1; i >= 0; i--) {
        swap(arr[0], arr[i]);
        heapify(arr, i, 0);
    }
}

int main(){
    int s;
    cout << "Enter the size of the array: ";
    cin >> s;

    int* arr = new int[s];
    cout << "Enter array values:" << endl;

    for(int i = 0; i<s; i++){
        cin >> arr[i];
    }

    heapSort(arr, s);
    cout << "Final result:\n";
    for(int i = 0; i<s; i++){
        cout << arr[i] << " ";
    }

}