#include "heap.hpp"

// TODO huffman
node* huffman_code(Heap* heap) {
    if(heap->size() == 0) return nullptr;
    if(heap->size() == 1) return heap->removeMin();
    node* newNode = nullptr;
    while(heap->size() >= 2){
        node* smallest = heap->removeMin();
        node* secSmallest = heap->removeMin();
        int newWeight = smallest->weight + secSmallest->weight;
        
        newNode = new node('a', newWeight);
        newNode->left = smallest;
        newNode->right= secSmallest;
        
        smallest->parent = newNode;
        secSmallest->parent = newNode;
        
        heap->insert(newNode);
        
    }
    return newNode;
}