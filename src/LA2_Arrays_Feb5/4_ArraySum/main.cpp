#include <iostream>
using namespace std;

int arraySum(int* arr, int s){
    int sum = 0;
    for(int i = 0; i<s; i++){
        sum+=arr[i];
    }
    return sum;
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
    cout << "Sum is " << arraySum(arr, s);
}