#include <iostream>
#include <stdexcept>
#include <ctime>
#include <cstdlib>
using namespace std;

class HashTable {
private:
    // Using -1 for DEFUNCT and -2 for EMPTY to allow 0 and positive keys
    const int DEFUNCT = -1;
    const int EMPTY = -2;

    int* table;      
    int capacity;    // N: The size of the bucket array [cite: 188]
    int n;           // current number of entries
    int p;           // Prime number larger than N [cite: 209]
    int a, b;        // Integers chosen from [0, p-1] with a > 0 [cite: 211, 212]

    // Helper to find a prime larger than capacity for MAD
    bool isPrime(int num) {
        if (num <= 1) return false;
        for (int i = 2; i * i <= num; i++) {
            if (num % i == 0) return false;
        } 
        return true;
    }

    int nextPrime(int num) {
        while (!isPrime(++num));
        return num;
    }

    // Primary Hash: MAD Method [(ai + b) mod p] mod N
    int primaryHash(int k) {
        // Ensure k is positive for the modulo arithmetic
        unsigned int key = (k < 0) ? -k : k;
        return ((a * key + b) % p) % capacity;
    }

    // Secondary Hash: h'(k) = q - (k mod q) 
    // The "Why": Secondary hash must not evaluate to zero 
    int secondaryHash(int k) {
        unsigned int key = (k < 0) ? -k : k;
        int q = p % capacity; // Use a prime-related value smaller than N
        if (q <= 1) q = 3; 
        return q - (key % q);
    }

public:
    HashTable(int cap) {
        capacity = cap;
        n = 0;
        table = new int[capacity];
        
        for (int i = 0; i < capacity; i++) {
            table[i] = EMPTY;
        }

        // Dynamically initialize MAD parameters
        srand(time(0));
        p = nextPrime(capacity); // p must be a prime > N [cite: 209]
        a = (rand() % (p - 1)) + 1; // a is in [1, p-1] [cite: 211, 212]
        b = rand() % p;             // b is in [0, p-1] [cite: 211]
    }

    ~HashTable() {
        delete[] table;
    }

    // Insert using Double Hashing: A[(h(k) + i * h'(k)) mod N] [cite: 350, 351]
    void insert(int key) {
        if (n >= capacity) throw runtime_error("Hash Table Overflow");

        int h = primaryHash(key);
        int step = secondaryHash(key);
        int i = 0;

        while (i < capacity) {
            int j = (h + i * step) % capacity;
            
            // Re-use DEFUNCT slots or fill EMPTY ones [cite: 334]
            if (table[j] == EMPTY || table[j] == DEFUNCT) {
                table[j] = key;
                n++;
                return;
            }
            i++;
        }
    }

    bool search(int key) {
        int h = primaryHash(key);
        int step = secondaryHash(key);
        int i = 0;

        while (i < capacity) {
            int j = (h + i * step) % capacity;
            
            // Search stops if an EMPTY cell is found [cite: 318, 334]
            if (table[j] == EMPTY) return false; 
            
            // Search skips DEFUNCT sentinels to find the key [cite: 334]
            if (table[j] == key) return true;
            
            i++;
        }
        return false;
    }

    void remove(int key) {
        int h = primaryHash(key);
        int step = secondaryHash(key);
        int i = 0;

        while (i < capacity) {
            int j = (h + i * step) % capacity;
            
            if (table[j] == EMPTY) return; 
            
            if (table[j] == key) {
                // Replace with "defunct" to avoid breaking search chains [cite: 333]
                table[j] = DEFUNCT;
                n--;
                return;
            }
            i++;
        }
    }

    void print() {
        for (int i = 0; i < capacity; i++) {
            cout << "[" << i << "]: ";
            if (table[i] == EMPTY) cout << "---";
            else if (table[i] == DEFUNCT) cout << "DEFUNCT";
            else cout << table[i];
            cout << endl;
        }
    }
};