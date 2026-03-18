#include <iostream>
#include <cmath>
using namespace std;

template <typename T>

class ArrayList{
    T* arr;
    int s;
    int cap;
    int max = 100;

    //resize 50% up
    bool resizeUp(){
        if(cap == max) return false;
        int newCap = ceil(cap*1.5);
        cap = newCap;
        arr = (T*) realloc(arr, cap*sizeof(T));
        return true;
    }

    void resizeDown(){
        int newCap = ceil(cap*0.75);
        if(newCap < 5) cap = 5;
        else cap = newCap;
        arr = (T*) realloc(arr, cap*sizeof(T));
    }

public:
    ArrayList(){
        cap = 5;
        arr = (T*)malloc(cap*sizeof(T));
        s = 0;
    }

    int getSize(){
        return s;
    }

    bool add(T elem){
        if(s==cap){
            if(resizeUp()){
                arr[s++] = elem;
                return true;
            } else {
                return false;
            }
        }
        arr[s++] = elem;
        return true;
    }

    int search(T elem){
        for(int i = 0; i<s; i++){
            if(arr[i]==elem){
                return i;
            }
        }
        return -1;
    }

    bool remove(T elem){
        int index = search(elem);
        if(index==-1) return false;

        for(int i = index; i<s-1; i++){
            arr[i] = arr[i+1];
        }

        s--;
        if(s==ceil(cap*0.75)){
            resizeDown();
        }
        return true;
    }

    void print(){
        for(int i = 0; i<s; i++){
            cout << arr[i] << "\t";
        }
    }
};