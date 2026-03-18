#include <iostream>
using namespace std;

int findMax(int* arr, int s){
    int max = arr[0];
    for(int i = 0; i<s; i++){
        if(arr[i]>max) max = arr[i];
    }
    return max;
}

void countingSortIterVer2(int* arr, int s){
    int max = findMax(arr, s);

    int* countArr = new int[max+1]{0};

    for(int i = 0; i<s; i++){
        countArr[arr[i]]++;
    }

    int index = 0;
    for(int i = 0; i<max+1; i++){
        while(countArr[i]>0){
            arr[index++] = i;
            countArr[i]--;;
        }
    }
}

void countingSortIterVer1(int* arr, int s){
    int max = findMax(arr, s);

    int* countArr = new int[max+1]{0};

    for(int i = 0; i<s; i++){
        countArr[arr[i]]++;
    }

    //prefix sum
    for(int i = 1; i<=max; i++){
        countArr[i] += countArr[i-1];
    }

    int* res =  new int[s];
    for(int i = s-1; i>=0; i--){
        res[countArr[arr[i]]-1] = arr[i];
        countArr[arr[i]]--;
    }
    
    for(int i = 0; i<s; i++){
        arr[i] = res[i];
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

    countingSortIterVer2(arr, s);
    cout << "Final result:\n";
    for(int i = 0; i<s; i++){
        cout << arr[i] << " ";
    }

}