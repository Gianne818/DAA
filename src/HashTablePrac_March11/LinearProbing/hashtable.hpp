#include <cstdlib>
#include <iostream>
using namespace std;

class HashTable {
    char* table;
    int N;
    int count;
    const char DEFUNCT = ' ';

    // Use the ASCII code of the character
    int hash_code(char key) {
        return (int)key;
    }

    // This hash table uses a MAD compression function
    // where a = 59, b = 17, p = 509
    int compress(int code) {
        return ((code*59+17)%509)%N;
    }

    // Using the knowledge that a hash function is composed of two portions
    int hashfn(char key) {
        return compress(hash_code(key));
    }

public:
    HashTable(int N){
        this->N = N;
        this->count = 0;
        table = new char[N];
        for(int i = 0; i<N; i++){
            table[i] = '\0';
        }
    }

    // returns number of probing done, aka number of steps done from original hash code
    // if unable to insert, return -1
    int insert(char key) {
        if(count == N || search(key)>0) return -1; //if xylphy version of search, search(key)>0
        int index = hashfn(key);

        int i = 0;
        int probe = (index + i) % N;

        while(table[probe]!='\0' && table[probe]!=DEFUNCT){
            i++;
            probe = (index + i) % N;
        }

        table[probe] = key;
        count++;
        return i;
    }

    
    // returns number of probing done, aka number of steps done from original hash code
    // if not found, return the number of probing done until not found, but negative.
    // returns i+1 in xylphy, since probe = (index + i++)%N
    int search(char key) {
        int index = hashfn(key);

        int i = 0;
        int probe = (index + i) % N;

        while(i<N && table[probe]!='\0'){
            if(table[probe]==key){
                return i+1;
            }
            i++;
            probe = (index+i)%N;
        }
        return -i;
    }

    // returns number of probing done, aka number of steps done from original hash code
    // if unable to insert, return -1
    int remove(char key) {
        int i = search(key)-1;  //i = search(key)-1 if we use the xylphy version of search
        if(i<0) return -1; // i<0 check if we use xylphy version

        int index = hashfn(key);
        int probe = (index+i)%N;

        int next = (probe+1)%N;
        
        if(table[next] == '\0'){
            table[probe] = '\0';
            int temp = (probe-1 + N)%N;
            int numChecked = 0;
            while(table[temp]==DEFUNCT && numChecked < N){
                table[temp] = '\0';
                temp = (temp-1 + N)%N;
                numChecked++;
            }
        }
        else {
            table[probe] = DEFUNCT;
        }
        count--;
        return i;
    }

    void print() {
        for (int i = 0; i < N; i++) {
            cout << i << "\t";
        }
        cout << "\n";
        for (int i = 0; i < N; i++) {
            cout << table[i] << "\t";
        }
        cout << "\n";
    }
};