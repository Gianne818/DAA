#include <iostream>
#include <stdexcept>

using namespace std;

class HTSepChain {
    int** table;
    int N;
    int* bucketSizes;
    int cap;

    int hash_code(int key) {
        return key;
    }

    int compress(int code) {
        int a = 7, b = 3, p = 101; 
        return ((a * code + b) % p) % N;
    }

    int hashfn(int key) {
        return compress(hash_code(key));
    }

public:
    HTSepChain(int N) {
        this->N = N;
        this->cap = 5;
        table = new int*[N];
        bucketSizes = new int[N];
        for (int i = 0; i < N; i++) {
            table[i] = (int*)malloc(cap * sizeof(int));
            bucketSizes[i] = 0;
        }
    }

    int search(int key) {
        int index = hashfn(key);
        for (int i = 0; i < bucketSizes[index]; i++) {
            if (table[index][i] == key) {
                return i;
            }
        }
        return -1;
    }

    void insert(int key) {
        int index = hashfn(key);
        if (search(key) != -1) {
            throw logic_error("Already has key " + to_string(key));
        }
        if (bucketSizes[index] == cap) {
            throw logic_error("Bucket " + to_string(index) +  " has reached maximum capacity.");
        }
        table[index][bucketSizes[index]] = key;
        bucketSizes[index]++;
    }

    int remove(int key) {
        int index = hashfn(key);
        int target = search(key);
        if (target == -1) {
            return -1;
        }
        for (int i = target; i < bucketSizes[index] - 1; i++) {
            table[index][i] = table[index][i + 1];
        }
        bucketSizes[index]--;
        return bucketSizes[index];
    }

    void print() {
        for (int i = 0; i < N; i++) {
            cout << i << "\t";
            for (int j = 0; j < bucketSizes[i]; j++) {
                cout << table[i][j] << " ";
            }
            cout << endl;
        }
    }
};