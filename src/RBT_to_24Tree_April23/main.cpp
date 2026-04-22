#include <iostream>
#include "rbt.hpp"
#include "btree24.hpp"
using namespace std;

int main() {
    RBT* rbt = new RBT();
    cout << "--- Inserting into RBT ---\n";
    rbt->insert(10);
    rbt->insert(20);
    rbt->insert(30);
    rbt->insert(15);
    rbt->insert(25);
    rbt->print();

    cout << "\n--- Converting RBT to 2-4 Tree ---\n";
    BTree24* bt24 = new BTree24();
    bt24->convertFromRBT(rbt->getRoot());
    bt24->print();

    cout << "\n--- Inserting directly into new 2-4 Tree ---\n";
    BTree24* bt24_manual = new BTree24();
    bt24_manual->insert(50);
    bt24_manual->insert(60);
    bt24_manual->insert(70);
    bt24_manual->insert(55);
    bt24_manual->print();

    cout << "\n--- Converting 2-4 Tree to RBT ---\n";
    RBT* rbt_converted = new RBT();
    rbt_converted->convertFrom24Tree(bt24_manual->getRoot());
    rbt_converted->print();

    return 0;
}