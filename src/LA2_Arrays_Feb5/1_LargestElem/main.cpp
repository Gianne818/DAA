#include <iostream>
#include <climits>
using namespace std;

int findLargest(int arr[], int size) {
    int max = INT_MIN;
    for(int i = 0; i<size; i++){
        if(arr[i] > max){
            max = arr[i];
        }
    }
    return max;
}

// DO NOR MODIFY
int main() {
    cout << "Enter size: ";
    int size;
    cin >> size;
    cout << "Enter elements: ";
    int arr[size]; // Example array
    for (int i = 0; i < size; i++) {
        cin >> arr[i];
    }
    int largest = findLargest(arr, size); // Call function to find largest element
    cout << "The largest element is: " << largest;
    return 0;
}