#include <iostream>
using namespace std;

int *findTwoNumbers(int arr[], int s, int target) {
    int* twoNums = (int*)malloc(2*sizeof(int));
    for(int i = 0; i<s; i++){
        for (int j = 0; j<s; j++){
            if(arr[i]+arr[j] == target && i!=j){
                twoNums[0] = arr[i];
                twoNums[1] = arr[j];
                return twoNums;
            }
        }
    }
    
    return nullptr;
}

// DO NOT MODIFY below -------- modified to get rid of hidden.hpp
// #include "hidden.hpp"

int main() {
    int size;
    cout << "Enter the size of the array: ";
    cin >> size;

    int* arr = new int[size];
    cout << "Enter the sorted list of numbers: ";
    for (int i = 0; i < size; ++i) {
        cin >> arr[i];
    }

    int target;
    cout << "Enter the target value: ";
    cin >> target;

    int* result = findTwoNumbers(arr, size, target);
    // if (result != nullptr) {
    //     if (find(arr, size, result[0]) + find(arr,size,result[1]) == 2 && result[0] + result[1] == target) {
    //         cout << "Two numbers found." << endl;
    //     } else {
    //         cout << "Either the numbers do not exist or " << result[0] << " and " << result[1] << " do not add to " << target << endl;
    //     }
    //     delete[] result;

    // } else {
    //     cout << "No two numbers found that sum to the target." << endl;
    // }

    delete[] arr;
    return 0;
}