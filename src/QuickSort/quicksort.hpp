#include <algorithm>
using namespace std;

// void printArray(int array[], int size){
//     for(int i = 0; i < size; i++)
//         cout << array[i] << ' ';
//     cout << '\n';
// }

// int partition(int array[], int left, int right, int size){
//     int pivot = array[right], low = left;

//     for(int i = left; i < right; i++)
//         if(pivot > array[i]){
//             if(i!=low) swap(array[i], array[low]);
//             low++;
//         }
            
//     swap(array[right], array[low]);
    
//     cout << "Current array after partition: " << endl;
//     printArray(array, size);
//     cout << "Current low and pivot: " << low << " " << pivot << endl << endl;

//     return low;
// }

// void quickSort(int array[], int left, int right, int size){
//     if(left < right){
//         int partitionIndex = partition(array, left, right, size);

//         quickSort(array, left, partitionIndex - 1, size);
//         quickSort(array, partitionIndex + 1, right, size);
//     }
// }


int partition(int arr[], int left, int right){
    int pivot = arr[right];
    int low = left;

    for(int i = left; i<right; i++){
        if(pivot > arr[i]){
            if(i!=low) swap(arr[i], arr[low]);
            low++;
        }
    }

    swap(arr[right], arr[low]);
    return low;
}

void quickSort(int array[], int left, int right){
    if(left < right){
        int partitionIndex = partition(array, left, right);

        quickSort(array, left, partitionIndex-1);
        quickSort(array, partitionIndex+1, right);
    }
}