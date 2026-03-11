#include <iostream>
#include "hashtable.hpp"
using namespace std;

int main() {
    cout << "Enter capacity of hash table: ";
    int size;
    cin >> size;

    HashTable *table = new HashTable(size);

    char op;
    int key; // Changed to int
    do {
        cout << "Operation: ";
        cin >> op;

        switch (op) {
            case 'i': // Insert
                cin >> key;
                cout << table->insert(key) << endl;
                break;

            case 's': // Search
                cin >> key;
                cout << table->search(key) << endl;
                break;

            case 'd': // Delete
                cin >> key;
                cout << table->remove(key) << endl;
                break;

            case 'p':
                table->print();
                break;

            case 'x':
                cout << "Exiting" << endl;
                break;
        }
    } while (op != 'x');

    return 0;
}