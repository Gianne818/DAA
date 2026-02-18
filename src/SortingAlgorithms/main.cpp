#include <iostream>
using namespace std;

void print(int* arr, int s){
    for(int i = 0; i<s; i++){
        cout << arr[i] << " ";
    }
    cout << endl;
}

//supa efficientized bubble sort (if you calculate actual running time, minus prints)
void bubbleSort(int* arr, int s){
    //printing initial arr
    cout << "Pass 0: ";
    print(arr, s);

    s-=1;
    for(int i = 0; i<s; i++){
        int tempSize = s-i;
        for(int j = 0; j<tempSize; j++){
            int incJ = j+1;
            if(arr[j]>arr[incJ]){
                int temp = arr[j];
                arr[j] = arr[incJ];
                arr[incJ] = temp;
            }

            //printing passes
            cout << "J-Pass " << j+1 << ": ";
            print(arr, s);
        }
        //printing passes
        cout << endl;
        cout << "Pass " << i+1 << ": ";
        print(arr, s+1);
    }
}

void insertionSort(int* arr, int s){
    //printing initial arr
    cout << "Pass 0: ";
    print(arr, s);

    for(int i = 1; i<s; i++){
        int current = arr[i];
        int j = i-1;

        int ctr = 1;
        while(j >= 0 && current < arr[j]){
            arr[j+1] = arr[j];
            j--;

            //printing passes
            cout << "J-Pass " << ctr << ": ";
            print(arr, s);
            ctr++;
        }
        ctr = 1;
        cout << endl;

        arr[j+1] = current;
        //printing passes
        cout << "Pass " << i << ": ";
        print(arr, s);
    }
}

void selectionSort(int* arr, int s){
    //printing initial arr
    cout << "Pass 0: ";
    print(arr, s);

    for(int i = 0; i<s; i++){
        int indexOfSmallest = i;
        for(int j = i+1; j<s; j++){
            if(arr[j] < arr[indexOfSmallest]){
                indexOfSmallest = j;
            }
        }

        if(i != indexOfSmallest){
            int temp = arr[indexOfSmallest];
            arr[indexOfSmallest] = arr[i];
            arr[i] = temp;
        }

        //printing passes
        cout << "Pass " << i+1 << ": ";
        print(arr, s);
    }
}

int main(){
    int s;
    cout << "Enter the number of elements: ";
    cin >> s;

    cout << "Enter the elements of the array: ";
    int*  arr = new int[s];
    for(int i = 0; i<s; i++){
        cin >> arr[i];
    }

    int* arrToPass = new int[s];
    for(int i = 0; i<s; i++){
        arrToPass[i] = arr[i];
    }
    cout << endl << "--------- Bubble sort ---------" << endl;
    bubbleSort(arrToPass, s);
    cout << "Result: " <<  endl;
    print(arrToPass, s);

    cout << endl << "--------- Insertion sort ---------" << endl;
    for(int i = 0; i<s; i++){
        arrToPass[i] = arr[i];
    }
    insertionSort(arrToPass, s);
    cout << "Result: " <<  endl;
    print(arrToPass, s);

    cout << endl << "--------- Selection sort ---------" << endl;
    for(int i = 0; i<s; i++){
        arrToPass[i] = arr[i];
    }
    selectionSort(arrToPass, s);
    cout << "Result: " <<  endl;
    print(arrToPass, s);
}