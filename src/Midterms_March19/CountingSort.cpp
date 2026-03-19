#include <iostream>
using namespace std;

int findMax(int* arr, int s){
    int max = arr[0];
    for(int i = 0; i<s; i++){
        if(arr[i]>max) max = arr[i];
    }
    return max;
}

int findMin(int* arr, int s){
    int min = arr[0];
    for(int i = 0; i<s; i++){
        if(arr[i]<min) min = arr[i];
    }
    return min;
}

int* countingSort(int* arr, int s){
    int max = findMax(arr, s);
    int min = findMin(arr, s);

    int countSize = max-min+1;
    int* count = new int[countSize]{0};

    for(int i = 0; i<s; i++){
        count[arr[i]-min]++;
    }

    //print
    cout << "FREQUENCY = ";
    for(int i = 0; i<countSize; i++){
        cout << count[i] << " ";
    }
    cout << endl;

    for(int i = 1; i<countSize; i++){
        count[i] += count[i-1];
    }

    //print cumulative frequency
    cout << "CUMU FREQ = ";
    for(int i = 0; i<countSize; i++){
        cout << count[i] << " ";
    }
    cout << endl;

    int* results = new int[s];
    for(int i = s-1; i>=0; i--){
        results[count[arr[i]-min]-1] = arr[i];
        count[arr[i]-min]--;
    }

    return results;

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

    int* res = countingSort(arr, s);
    cout << "Final result:\n";
    for(int i = 0; i<s; i++){
        cout << res[i] << " ";
    }

}