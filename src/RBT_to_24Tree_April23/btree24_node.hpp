#pragma once
#include <cstdlib>
using namespace std;

struct btree24_node {
    btree24_node* parent;
    int keys[4];
    btree24_node** children;
    int size = 0;
    
    void insertKeyAt(int key, int index) {
        for(int i = 3; i > index; i--) {
            keys[i] = keys[i-1];
        }
        keys[index] = key;
        size++;
    }
    
    bool contains(int num) {
        for(int i = 0; i < size; i++) {
            if(keys[i] == num) return true;
        }
        return false;
    }
    
    btree24_node(btree24_node* par, int num) {
        parent = par;
        insertKeyAt(num, 0);
        children = (btree24_node**)calloc(5, sizeof(btree24_node*));
    }
    
    btree24_node() {
        parent = nullptr;
        children = (btree24_node**)calloc(5, sizeof(btree24_node*));
    }
};