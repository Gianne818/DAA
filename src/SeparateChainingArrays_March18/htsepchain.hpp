#include <iostream>
#include "arraylist.hpp"
using namespace std;

template <typename T>

class HTSepChain {
    ArrayList<T>** table;
    int size;
    int N;

    int hash_code(T elem){
        return (int) elem;
    }

    //Division compression
    int compress(int code){
        return (code%N + N)%N;
    }

    int hashfn(T elem){
        return compress(hash_code(elem));
    }

public:
    HTSepChain(int N){
        this->N = N;
        size = 0;
        table = new ArrayList<T>*[N];
        for(int i = 0; i<N; i++){
            table[i] = new ArrayList<T>();
        }
    }

    bool search(T elem){
        int index = hashfn(elem);

        if(table[index]->search(elem)!=-1){
            return true;
        }
        return false;
    }

    int insert(T elem){
        if(search(elem)){
            throw logic_error("Already added key");
        }
        int index = hashfn(elem);
        table[index]->add(elem);
        return table[index]->getSize();
    }

    int remove(T elem){
        if(!search(elem)) return -1;
        int index = hashfn(elem);

        table[index]->remove(elem);
        return table[index]->getSize();
    }

    void print(){
        for(int i = 0; i<N; i++){
            cout << i << "\t";
            table[i]->print();
            cout << endl;
        }
    }



};