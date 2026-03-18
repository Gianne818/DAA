#include <iostream>
using namespace std;

template<typename T>
class HTSepChain{
    T** table;
    int N;
    int* bucketSizes;
    int cap;

    int hash_code(T elem){
        return (int) elem;
    }

    int compress(int code){
        return (code%N + N)%N;
    }

    int hashfn(T elem){
        return compress(hash_code(elem));
    }

public:
    HTSepChain(int N){
        this->N = N;
        table = new T*[N];
        bucketSizes = new int[N];
        cap = 10;
        for(int i = 0; i<N; i++){
            table[i] = (T*) malloc(cap*sizeof(T));
            bucketSizes[i] = 0;
        }
    }


    int search(T elem){
        int index = hashfn(elem);

        for(int i = 0; i<bucketSizes[index]; i++){
            if(table[index][i] == elem){
                return i;
            }
        }
        return -1;
    }

    int insert(T elem){
        int index = hashfn(elem);

        if(search(elem)!=-1){
            throw logic_error("Already has key.");
        }
        if(bucketSizes[index] == cap){
            throw logic_error("Maximum bucket size reached.");
        }

        table[index][bucketSizes[index]] = elem;
        bucketSizes[index]++;
        return bucketSizes[index];
    }

    int remove(T elem){
        int index = hashfn(elem);
        int target = search(elem);
        if(target==-1){
            return -1;
        }

        for(int i = target; i<bucketSizes[index]-1; i++){
            table[index][i] = table[index][i+1];
        }
        bucketSizes[index]--;
        return bucketSizes[index];
    }

    void print(){
        for(int i = 0; i<N; i++){
            cout << i << "\t";
            for(int j = 0; j<bucketSizes[i]; j++){
                cout << table[i][j] << " ";
            }
            cout << endl;
        }
    }
};