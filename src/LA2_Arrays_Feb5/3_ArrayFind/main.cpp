#include <iostream>
using namespace std;

int arrayFind(int* arr, int n, int s){
    int res = -1;
    for(int i = 0; i<s; i++){
        if(arr[i] == n){
            res = i+1;
            break;
        }
    }
    return res;
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
    
    int n;
    cout << "Number to find: ";
    cin >> n;
    
    int res = arrayFind(arr, n, s);
    if(res == -1){
        cout << n << " is not there";
    } else {
        cout << n << " is at position " << arrayFind(arr, n, s);
    }
    
}