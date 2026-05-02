#include "node.hpp"
#include <iostream>
#include <climits>
#include <algorithm>
using namespace std;

class Heap {
    
    node** arr;
    int s;
    
	public:
	
	void bubbleDown(){
	    int i = 0;
	    while(true){
	        int l = left(i);
	        int r = right(i);
	        int smallest = i;
	        
	        if(l < s && arr[l]->weight < arr[smallest]->weight) smallest = l;
	        if(r < s && arr[r]->weight < arr[smallest]->weight) smallest = r;
	        
	        if(i==smallest) break;
	        swap(arr[i], arr[smallest]);
	        i = smallest;
	        
	    }
	}
	
	Heap(){
	    arr = (node**)calloc(26, sizeof(node*));
	    s = 0;
	}
	
	int left(int i ){
	    return 2 * i + 1;
	}
	
	int right(int i){
	    return 2 * i + 2;
	}
	
    // TODO insert
	void insert(node* n) {
        arr[s++] = n;
	    
	    int i = s-1;
	    int parent = (i-1)/2;
	    
	    while(i > 0 && arr[parent]->weight > arr[i]->weight){
	        swap(arr[parent], arr[i]);
	        i = parent;
	        parent = (i-1)/2;
	    }
	    
	}

    // TODO removeMin
	node* removeMin() {
	    if(s == 0) return nullptr;
	    
	    node* temp = arr[0];
	    arr[0] = arr[s-1];
	    s--;
	    
	    bubbleDown();
		return temp;
	}

    // TODO size
	int size() {
		return s;
	}
};