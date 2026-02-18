// TODO entire implementation
#include <iostream>
#include "list.hpp"
#include <cmath>
#include <stdexcept>
#include <algorithm>
using namespace std;

class ArrayList: public List {
private:
    int* arr;
    int cap;
    int s;
    
    void resizeUp(){
        int newCap = ceil(cap*1.5);
        cap = newCap;
        arr = (int*) realloc(arr, cap*sizeof(int));
    }
    
    void resizeDown(){
        int newCap = ceil(cap*0.75);
        cap = max(newCap, 5);
        arr = (int*) realloc(arr, cap*sizeof(int));
    }
    
public:
    ArrayList(){
        arr = (int*)malloc(5*sizeof(int));
        cap = 5;
        s= 0;
    }
    
    void insert(int num){
        if(s == cap){
            resizeUp();
        }
        arr[s++] = num; 
    }
    
    int get(int pos){
        if(pos > s || pos < 1) throw invalid_argument("Invalid position");
        return arr[pos-1];
    }
    
    int remove(int num){
        for(int i = 0; i<s; i++){
            if(arr[i] == num){
                for(int j = i; j<s-1; j++){
                    arr[j] = arr[j+1];
                }
                s--;
                if(s <= floor(cap*(2.0/3.0))){
                    resizeDown();
                }
                return i+1;
            }
        }
        return 0;
    }
    
    int size(){
        return s;
    }
    
    bool isEmpty(){
        return s==0;
    }
    
    void addAt(int num, int pos){
        if(pos > s+1 || pos < 1) throw invalid_argument("Invalid position");
        if(s == cap){
            resizeUp();
        }
        for (int i = s; i>=pos; i--){
            arr[i] = arr[i-1];
        }
        
        arr[pos-1] = num;
        s++;
        
        return;
    }
    
    int removeAt(int pos){
        if(pos > s || pos < 1) throw invalid_argument("Invalid position");
        int temp = arr[pos-1];
        for(int i = pos-1; i<s-1; i++){
            arr[i] = arr[i+1];
        }
        s--;
        
        if(s <= floor(cap*(2.0/3.0))){
            resizeDown();
        }
        
        return temp;
    }
    
    void print(){
        for(int i = 0; i<s; i++){
            cout << arr[i] << " ";
        }
        
        for(int i = s; i<cap; i++){
            cout << "? ";
        }
        cout << endl;
    }
};