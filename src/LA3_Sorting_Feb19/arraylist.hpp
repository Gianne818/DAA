#include "list.hpp"
#include <cstdlib>
#include <cmath>

using namespace std;

class ArrayList : public List{
    int* array;
    int capacity;
    int index;

    void resizeUp(){
        int newCap = ceil(capacity*1.5);
        capacity = newCap;
        array = (int*) realloc(array, capacity*sizeof(int));
    }

    public:
    ArrayList(){
        capacity = 4;
        index = 0;
        array = (int*) malloc(capacity*sizeof(int)); 
    }

    int add(int num){
        if(index==capacity) resizeUp();
        array[index++] = num;
        return index;
    }

    int get(int pos){
        if(pos>=index || pos<0) return -1;
        return array[pos];
    }


    void swap(int pos1, int pos2){
        int temp = array[pos1];
        array[pos1] = array[pos2];
        array[pos2] = temp;
    }

    int size(){
        return index;
    }

    void print(){
        for(int i = 0; i<index; i++){
            cout << array[i] << " ";
        }
        cout << endl;
    }
};