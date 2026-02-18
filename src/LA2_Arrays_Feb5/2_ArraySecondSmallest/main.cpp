#include <iostream>
#include <climits>
using namespace std;

int arraySecondSmallest(int* arr, int s){
    int smallest = INT_MAX;
    int secondSmallest = INT_MAX;
    for(int i = 0; i<s; i++){
        if(arr[i] < smallest){
            secondSmallest = smallest;
            smallest = arr[i];
        } else if (arr[i]!=smallest && arr[i] < secondSmallest){
            secondSmallest = arr[i];
        }
    }
    return secondSmallest;
}

int main (){
    int s;
    cout << "Enter number of elements: ";
    cin >> s;
    
    int* arr = new int[s];
    for(int i = 0; i<s; i++){
        cout << "Enter element " << i+1 << ": ";
        cin >> arr[i];
    }
    
    cout << "The second smallest element is " << arraySecondSmallest(arr, s);
}