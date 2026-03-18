#include <iostream>
#include <stdexcept>

using namespace std;

template <typename T>
class HTSepChain {
    T** table;
    int* bucketSizes;
    int N;

    int hash_code(T elem) {
        return (int)elem;
    }

    int compress(int code) {
        return (code % N + N) % N;
    }

    int hashfn(T elem) {
        return compress(hash_code(elem));
    }

public:
    HTSepChain(int N) {
        this->N = N;
        table = new T*[N];
        bucketSizes = new int[N];
        for (int i = 0; i < N; i++) {
            table[i] = nullptr;
            bucketSizes[i] = 0;
        }
    }

    bool search(T elem) {
        int index = hashfn(elem);
        for (int i = 0; i < bucketSizes[index]; i++) {
            if (table[index][i] == elem) {
                return true;
            }
        }
        return false;
    }

    int insert(T elem) {
        if (search(elem)) {
            throw logic_error("Already added key");
        }
        int index = hashfn(elem);
        int currSize = bucketSizes[index];
        
        T* temp = new T[currSize + 1];
        for (int i = 0; i < currSize; i++) {
            temp[i] = table[index][i];
        }
        temp[currSize] = elem;
        
        delete[] table[index];
        table[index] = temp;
        bucketSizes[index]++;
        
        return bucketSizes[index];
    }

    int remove(T elem) {
        int index = hashfn(elem);
        int currSize = bucketSizes[index];
        int target = -1;

        for (int i = 0; i < currSize; i++) {
            if (table[index][i] == elem) {
                target = i;
                break;
            }
        }

        if (target == -1) return -1;

        if (currSize == 1) {
            delete[] table[index];
            table[index] = nullptr;
        } else {
            T* temp = new T[currSize - 1];
            for (int i = 0, j = 0; i < currSize; i++) {
                if (i != target) {
                    temp[j++] = table[index][i];
                }
            }
            delete[] table[index];
            table[index] = temp;
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