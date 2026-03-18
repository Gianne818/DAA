#include <iostream>
using namespace std;

int findMax(int* arr, int s){
    int max = arr[0];
    for(int i = 0; i<s; i++){
        if(arr[i]>max) max = arr[i];
    }
    return max;
}


void countSortForRadix(int* arr, int s, int exp) {
    int output[s]; 
    int count[10] = {0};

    for (int i = 0; i < s; i++) {
        count[(arr[i] / exp) % 10]++;
    }

    for (int i = 1; i < 10; i++) {
        count[i] += count[i - 1];
    }

    for (int i = s - 1; i >= 0; i--) {
        int digit = (arr[i] / exp) % 10;
        output[count[digit] - 1] = arr[i];
        count[digit]--;
    }

    for (int i = 0; i < s; i++) {
        arr[i] = output[i];
    }
}

void radixSort(int* arr, int s) {
    int max = findMax(arr, s);

    for (int exp = 1; max / exp > 0; exp *= 10) {
        countSortForRadix(arr, s, exp);
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

    radixSort(arr, s);
    cout << "Final result:\n";
    for(int i = 0; i<s; i++){
        cout << arr[i] << " ";
    }

}