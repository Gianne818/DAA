#pragma once
#include "btree24_node.hpp"
#include "rbt_node.hpp"
#include <iostream>
#include <string>
using namespace std;

class BTree24 {
    btree24_node* root;

    btree24_node* createEmptyNode() {
        btree24_node* newNode = (btree24_node*)calloc(1, sizeof(btree24_node));
        newNode->children = (btree24_node**)calloc(5, sizeof(btree24_node*));
        newNode->size = 0;
        newNode->parent = nullptr;
        return newNode;
    }

    void split(btree24_node* w) {
        btree24_node* u = w->parent;
        int uch = 0;

        if (!u) {
            u = createEmptyNode();
            u->insertKeyAt(w->keys[2], 0);
            root = u;
        } else {
            for (uch = 0; uch <= u->size; uch++) {
                if (u->children[uch] == w) break;
            }
            u->insertKeyAt(w->keys[2], uch);
        }

        btree24_node* wpr = createEmptyNode();
        wpr->parent = u;
        wpr->insertKeyAt(w->keys[0], 0);
        wpr->insertKeyAt(w->keys[1], 1);
        
        for (int j = 0; j < 3; j++) {
            wpr->children[j] = w->children[j];
            if (wpr->children[j]) wpr->children[j]->parent = wpr;
        }

        btree24_node* w2pr = createEmptyNode();
        w2pr->parent = u;
        w2pr->insertKeyAt(w->keys[3], 0);
        
        for (int j = 0; j < 2; j++) {
            w2pr->children[j] = w->children[3 + j];
            if (w2pr->children[j]) w2pr->children[j]->parent = w2pr;
        }

        for (int i = 4; i > uch; i--) {
            u->children[i] = u->children[i - 1];
        }
        u->children[uch] = wpr;
        u->children[uch + 1] = w2pr;

        free(w->children);
        free(w);

        if (u->size == 4) split(u);
    }

    btree24_node* convertRBTNode(rbt_node* rbtNode) {
        if (!rbtNode || rbtNode->isRed) return nullptr;

        btree24_node* n24 = createEmptyNode();
        rbt_node* blackChildren[4] = {nullptr, nullptr, nullptr, nullptr};
        int childCount = 0;

        if (rbtNode->left && rbtNode->left->isRed) {
            n24->keys[n24->size++] = rbtNode->left->elem;
            blackChildren[childCount++] = rbtNode->left->left;
            blackChildren[childCount++] = rbtNode->left->right;
        } else {
            blackChildren[childCount++] = rbtNode->left;
        }

        n24->keys[n24->size++] = rbtNode->elem;

        if (rbtNode->right && rbtNode->right->isRed) {
            n24->keys[n24->size++] = rbtNode->right->elem;
            blackChildren[childCount++] = rbtNode->right->left;
            blackChildren[childCount++] = rbtNode->right->right;
        } else {
            blackChildren[childCount++] = rbtNode->right;
        }

        for (int i = 0; i < childCount; i++) {
            if (blackChildren[i]) {
                btree24_node* child24 = convertRBTNode(blackChildren[i]);
                n24->children[i] = child24;
                if (child24) child24->parent = n24;
            }
        }
        return n24;
    }

public:
    BTree24() : root(nullptr) {}

    btree24_node* getRoot() { return root; }

    btree24_node* search_sir(int num, btree24_node* n) {
        if (n == nullptr) return nullptr;
        for (int i = 0; i < n->size; i++) {
            if (n->keys[i] == num) return n;
            if (n->keys[i] > num) {
                if (n->children[i]) return search_sir(num, n->children[i]);
                return n;
            }
        }
        if (n->children[n->size] != nullptr) return search_sir(num, n->children[n->size]);
        return n;
    }

    bool insert(int num) {
        if (root == nullptr) {
            root = createEmptyNode();
            root->insertKeyAt(num, 0);
            return true;
        }
        btree24_node* w = search_sir(num, root);
        if (w->contains(num)) return false;

        int i;
        for (i = 0; i < w->size; i++) {
            if (num < w->keys[i]) break;
        }
        w->insertKeyAt(num, i);

        if (w->size == 4) split(w);
        return true;
    }

    void convertFromRBT(rbt_node* rbtRoot) {
        root = convertRBTNode(rbtRoot);
    }

    void print_node(string s, btree24_node* n) {
        cout << s << ": ";
        for (int i = 0; i < n->size; i++) cout << n->keys[i] << " ";
        cout << endl;
        for (int i = 0; i <= n->size; i++) {
            if (n->children[i]) print_node("Child " + to_string(i + 1) + " of " + s, n->children[i]);
        }
    }

    void print() {
        if (root) print_node("Root", root);
        else cout << "EMPTY\n";
    }
};