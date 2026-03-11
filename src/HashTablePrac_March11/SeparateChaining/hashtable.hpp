#include <iostream>
#include <cstdlib>
#include "linkedlist.hpp" // Assuming this contains the LinkedList class provided


//by GEMINI

using namespace std;

class HashTable {
    LinkedList* table; // Array of Linked Lists
    int size;          // Capacity of the table
    int count;         // Number of elements currently in the table

    // Using the bit representation/cast for integers as suggested in slides
    int hash_code(int key) {
        return key; 
    }

    // MAD compression function: [(ai + b) % p] % size
    int compress(int code) {
        // Using common prime p = 509 as in your previous code
        // Ensure the result of (a*i + b) is positive before modulo
        int a = 59, b = 17, p = 509;
        int compressed = ((a * code + b) % p) % size;
        return (compressed < 0) ? compressed + size : compressed;
    }

    int hashFunction(int key) {
        return compress(hash_code(key));
    }

public:
    explicit HashTable(int size) : size(size), count(0) {
        if (size < 0) size = 0;
        // Using an array of LinkedList objects
        table = new LinkedList[size];
    }

    // Returns the number of elements already in the bucket (collisions)
    int insert(int key) {
        int index = hashFunction(key);
        
        // In separate chaining, we usually allow duplicates or 
        // check if it exists. Here, search(key) returns pos or -1.
        if (search(key) != -1) {
            return -1; 
        }

        int collisions = table[index].size;
        table[index].addTail(key);
        count++;
        return collisions;
    }

    // Returns the position in the linked list (1-based) or -1 if not found
    int search(int key) {
        int index = hashFunction(key);
        return table[index].get(key);
    }

    // Returns the position it was deleted from, or -1 if not found
    int remove(int key) {
        int index = hashFunction(key);
        int pos = table[index].remove(key);
        if (pos != -1) {
            count--;
        }
        return pos;
    }

    void print() {
        for (int i = 0; i < size; i++) {
            cout <<  "[" << i << "]" << ": ";
            table[i].print();
        }
    }
};