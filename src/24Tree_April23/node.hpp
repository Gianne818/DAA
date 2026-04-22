#include <iostream>
using namespace std;

struct node {
	node* parent;
	int keys[4];
	node** children;
	int size = 0;
	
	void insertKeyAt(int key, int index){
	   // cout << "key: " << key << " index: " << index << endl;
	    for(int i = 3; i > index; i--){
	       // cout << "inserting...\n";
	        keys[i] = keys[i-1];
	    }
	    keys[index] = key;
	    size++;
	}
	
    bool contains(int num){
        for(int i = 0; i<size; i++){
            if(keys[i] == num){
                return true;
            }
        }
        return false;
    }
    
    node(node* par, int num){
        parent = par;
        insertKeyAt(num, 0);
        // cout << "reached here\n";
        // cout << "parent: " << this->parent << endl;
        // cout << keys[0] << endl;
        children = (node**)calloc(4, sizeof(node*));
    }
    
    node(){
        
    }
    
    // int getKey(int index){
    //     return keys[index];
    // }

};