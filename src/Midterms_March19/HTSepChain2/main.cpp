#include <iostream>
#include <stdexcept>
#include "htsepchain.hpp"

using namespace std;

int main() {
    int size;
    cout << "Enter capacity of hash table: ";
    cin >> size;

    HTSepChain *table = new HTSepChain(size);

    char op;
    int key;
    
    do {
        cout << "Operation: ";
        cin >> op;

        switch (op) {
            case 'i':
                cin >> key;
                try {
                    table->insert(key);
                    cout << "Inserted " << key << endl;
                } catch (exception& e) {
                    cout << e.what() << endl;
                }
                break;

            case 's':
                cin >> key;
                cout << table->search(key) << endl;
                break;

            case 'd':
                cin >> key;
                cout << table->remove(key) << endl;
                break;

            case 'p':
                table->print();
                break;

            case 'x':
                cout << "Exiting" << endl;
                break;
            
            default:
                cout << "Invalid operation." << endl;
        }
    } while (op != 'x');

    delete table;
    return 0;
}