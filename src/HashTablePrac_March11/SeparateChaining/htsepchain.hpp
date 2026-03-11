#include "hashtable.hpp"
#include "linkedlist.hpp"

class HTSepChain : public HashTable {

    LinkedList** table; // this linkedlist is pointing to an array
    int N; // capacity of the hashtable
    int count;

    public:
    HTSepChain(int N){
        this->N = N;
        this->count = 0;
        this->table = new LinkedList*[N];
        for(int i = 0; i<N; i++){
            table[i] = new LinkedList();
        }
    }

    /*
        For the string's hash code, use the Polynomial Hash Code using a=5. 
        For the compression function, you will implement the Division Method.
    */

    int hash_code(string key){
        int h = 0, a = 5;
        for(int i = 0; i<key.length(); i++){
            h = h * a + (int)key[i];
        }
        return h;
    }

    int compress(int code){
        return (code % N + N) % N;
    }

    int hashfn(string key){
        return compress(hash_code(key));
    }


    
    // int hash_code(string key) {
    //     int h = 0, a = 5;
    //     for (char c : key) {
    //         h = h * a + (int)c; //horner's method in evalutaing polynomials
    //     }
    //     return h;
    // }

    // int compress(int code) { 
    //     return (code % N + N) % N;
    //  }

    //  int hashfn(string key){
    //     return compress(hash_code(key));
    //  }

    //return size of current linkedlist
    int insert(string key){
        int index = hashfn(key);

        if(table[index]->find_node(key)){
            throw runtime_error("already added key " + key);
        }

        table[index]->add_last(key);
        count++;
        return table[index]->size_();
    }

    int remove(string key){
        int index = hashfn(key);
        if(table[index]->remove_node(key)){
            count--;
            return table[index]->size_();
        }
        return -1;
    }

    int search(string key){
        int index = hashfn(key);
        if(table[index]->find_node(key)){
            return table[index]->size_();
        }
        return -1;
    }

    void print() {

        for (int i = 0; i < N; i++) {

            cout << i << "\t";
            table[i]->print();
            cout << endl;
        }

    }
};