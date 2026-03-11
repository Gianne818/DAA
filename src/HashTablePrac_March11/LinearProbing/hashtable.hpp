#include <cstdlib>
#include <iostream>
using namespace std;

class HashTable {
    char* table;
    int size;
    int count;

    // Use the ASCII code of the character
    int hash_code(char key) {
        return (int) key;
    }

    // This hash table uses a MAD compression function
    // where a = 59, b = 17, p = 509
    int compress(int code) {
        return ((59*code+17)%509)%size;
    }

    // Using the knowledge that a hash function is composed of two portions
    int hashFunction(char key) {
        int code = hash_code(key);
        return compress(code);
    }

public:
    HashTable(int size){
        this->size = size;
        table = new char[size];
        for(int i = 0; i<size; i++){
            table[i] = '\0';
        }
        count = 0;
    }

    int insert(char key) {
        int ind = hashFunction(key);
        int i = 0;
        int probe = (ind + i++) % size;

        if(count==size) return -1;

        while(table[probe]!='\0'){
            if(table[probe]==key) return -1;
            probe = (ind + i++) % size;
        }
        table[probe] = key;
        count++;
        return i-1;
    }

    int search(char key) {
        int ind = hashFunction(key);
        int i = 0; 
        int probe = (ind+i)%size;
        
        int checked = 0;
        while(checked<count){
            if(table[probe]==key){
                return i;
            }
            else if (table[probe]!='\0'){
                checked++;
            }
            probe = (ind + i++)%size;
        }

        return -i;
    }

    int remove(char key) {
        return 0;
    }

    void print() {
        for (int i = 0; i < size; i++) {
            cout << i << "\t";
        }
        cout << "\n";
        for (int i = 0; i < size; i++) {
            cout << table[i] << "\t";
        }
        cout << "\n";
    }
};