#include <cstdlib>
#include <iostream>

using namespace std;

class HashTable {
    char* table;
    int N;
    int count;
    // Sentinel character representing a "defunct" or deleted slot
    const char DEFUNCT = ' '; 

    // Use the ASCII code of the character
    int hash_code(char key) {
        return (int) key;
    }

    // This hash table uses a MAD compression function
    // where a = 59, b = 17, p = 509
    int compress(int code) {
        return ((59 * code + 17) % 509) % N;
    }

    // Using the knowledge that a hash function is composed of two portions
    int hashFunction(char key) {
        return compress(hash_code(key));
    }

public:
    explicit HashTable(int N) : N(N), count(0) {
        if(N < 0) N = 0;
        table = new char[N];
        for(int i = 0; i < N; i++)
            table[i] = '\0';
    }

    int insert(char key) {
        // Linear probing: search until we find an empty slot or a defunct slot
        // Also check if key already exists to prevent duplicates
        if (count == N || search(key) >= 0) {
            return -1;
        }

        int index = hashFunction(key);
        int i = 0;
        int probe;

        while (true) {
            probe = (index + i) % N;
            // We can insert at an empty slot OR a defunct slot
            if (table[probe] == '\0' || table[probe] == DEFUNCT) {
                table[probe] = key;
                count++;
                return i;
            }
            i++;
        }
    }

    int search(char key) {
        int index = hashFunction(key);
        int i = 0;
        
        while (i < N) {
            int probe = (index + i) % N;
            
            // If we hit an empty slot, the key definitely isn't here
            if (table[probe] == '\0') {
                return -1;
            }
            
            // If it matches the key, return the number of probes
            if (table[probe] == key) {
                return i;
            }
            
            // If it's DEFUNCT or a different key, keep probing
            i++;
        }
        return -1;
    }

    int remove(char key) {
        int index = hashFunction(key);
        int i = 0;

        while (i < N) {
            int probe = (index + i) % N;
            
            if (table[probe] == '\0') {
                return -1; // Key not found
            }
            
            if (table[probe] == key) {
                table[probe] = DEFUNCT; // Replace with sentinel
                count--;
                return i;
            }
            i++;
        }
        return -1;
    }

    void print() {
        for (int i = 0; i < N; i++) {
            cout << i << "\t";
        }
        cout << "\n";
        for (int i = 0; i < N; i++) {
            // Helper to visualize the defunct marker in the console
            if (table[i] == DEFUNCT) cout << "D" << "\t";
            else cout << table[i] << "\t";
        }
        cout << "\n";
    }
};