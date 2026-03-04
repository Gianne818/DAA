#include <iostream>
using namespace std;


void printArray(int array[], int size){
    for(int i = 0; i < size; i++)
        cout << array[i] << ' ';
    cout << '\n';
}

// void mergeArrays(int array[], int left, int mid, int right){
//     int leftSize = mid - left + 1;
//     int rightSize = right - mid;

//     int leftArray[leftSize];
//     int rightArray[rightSize];
            
//     //temporarily store left and right subarray
//     for(int i = 0; i < leftSize; i++)
//         leftArray[i] = array[left + i];
//     for(int i = 0; i < rightSize; i++)
//         rightArray[i] = array[mid + 1 + i];

//     int leftIndex = 0;
//     int rightIndex = 0;
//     int arrayIndex = left;

//     //merge the two subarrays bacl, but this time, merge into array and is already sorted from arr[left..mid]
//     // or arr[mid+1, right]
//     while(leftIndex < leftSize && rightIndex < rightSize){
//         if(leftArray[leftIndex] <= rightArray[rightIndex])
//             array[arrayIndex++] = leftArray[leftIndex++];
//         else
//             array[arrayIndex++] = rightArray[rightIndex++];
//     }

//     //if there are remaining array values from left OR right parts, add them back.
//     //usually only one element left for either of them, or none.
//     while(leftIndex < leftSize)
//         array[arrayIndex++] = leftArray[leftIndex++];
//     while(rightIndex < rightSize)
//         array[arrayIndex++] = rightArray[rightIndex++];
// }

// void mergeSort(int array[], int left, int right){
//     if(left < right){
//         int mid = (left + right) / 2;
//         mergeSort(array, left, mid);
//         mergeSort(array, mid + 1, right);

//         mergeArrays(array, left, mid, right);
//     }
// }


void mergeArrays(int arr[], int left, int mid, int right){
    int leftArrSize = mid-left+1;
    int rightArrSize = right-mid;

    int leftArr[leftArrSize];
    int rightArr[rightArrSize];

    for(int i = 0; i<leftArrSize; i++){
        leftArr[i] = arr[left+i];
    }
    for(int i = 0; i<rightArrSize; i++){
        rightArr[i] = arr[mid+1+i];
    }

    int leftInd = 0;
    int rightInd =  0;
    int curArrIndex = left;

    while(leftInd < leftArrSize && rightInd < rightArrSize){
        if(leftArr[leftInd] <= rightArr[rightInd]){
            arr[curArrIndex++] = leftArr[leftInd++];
        } else {
            arr[curArrIndex++] = rightArr[rightInd++];
        }
    }

    while(leftInd < leftArrSize){
        arr[curArrIndex++] = leftArr[leftInd++];
    }

    while(rightInd < rightArrSize){
        arr[curArrIndex++] = rightArr[rightInd++];
    }
}

void mergeSort(int arr[], int left, int right){
    if(left<right){
        int mid = left+(right-left)/2;
        mergeSort(arr, left, mid);
        mergeSort(arr, mid+1, right);

        mergeArrays(arr, left, mid, right);
    }
}
