#include <iostream>
#include <string>
// Assuming HTSepChain is in its own header or included here
#include "htsepchain.hpp" 

using namespace std;

int main() {
    cout << "Enter capacity of hash table: ";
    int size;
    cin >> size;

    // Use the specific implementation class
    HTSepChain *table = new HTSepChain(size);

    char op;
    string key; // Changed from int to string
    
    do {
        cout << "Operation: ";
        cin >> op;

        switch (op) {
            case 'i': // Insert
                cin >> key;
                try {
                    cout << table->insert(key) << endl;
                } catch (const runtime_error& e) {
                    cout << e.what() << endl;
                }
                break;

            case 's': // Search
                cin >> key;
                cout << table->search(key) << endl;
                break;

            case 'd': // Delete (Remove)
                cin >> key;
                cout << table->remove(key) << endl;
                break;

            case 'p': // Print
                table->print();
                break;

            case 'x':
                cout << "Exiting" << endl;
                break;
            
            default:
                cout << "Invalid operation." << endl;
        }
    } while (op != 'x');

    delete table; // Clean up memory
    return 0;
}