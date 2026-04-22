#pragma once
#include <cstdlib>
#include <iostream>
#include <string>
#include "rbt_node.hpp"
using namespace std;

class BinaryTree {
public:
    virtual rbt_node* left(rbt_node*) = 0;
    virtual rbt_node* right(rbt_node*) = 0;
    virtual void zigleft(rbt_node*) = 0;
    virtual void zigright(rbt_node*) = 0;
    virtual rbt_node* addRoot(int e) = 0;
    virtual rbt_node* addLeft(rbt_node* p, int e) = 0;
    virtual rbt_node* addRight(rbt_node* p, int e) = 0;
    virtual int remove(rbt_node*) = 0;
    virtual rbt_node* getRoot() = 0;
    virtual void setRoot(rbt_node*) = 0;
    virtual void print() = 0;
};

class MyBinaryTree : public BinaryTree {
    rbt_node* root = nullptr;
    int size = 0;

    rbt_node* create_node(int e, rbt_node* parent) {
        rbt_node* n = (rbt_node*)calloc(1, sizeof(rbt_node));
        n->elem = e;
        n->parent = parent;
        n->isRed = true;
        return n;
    }

public:
    void setRoot(rbt_node* r) { root = r; }

    rbt_node* addRoot(int e) {
        if (root) return nullptr;
        rbt_node* n = create_node(e, nullptr);
        root = n;
        size++;
        return n;
    }

    rbt_node* left(rbt_node* p) { return p->left; }
    rbt_node* right(rbt_node* p) { return p->right; }

    rbt_node* addLeft(rbt_node* p, int e) {
        if (p->left) return nullptr;
        rbt_node* n = create_node(e, p);
        p->left = n;
        size++;
        return n;
    }

    rbt_node* addRight(rbt_node* p, int e) {
        if (p->right) return nullptr;
        rbt_node* n = create_node(e, p);
        p->right = n;
        size++;
        return n;
    }

    int remove(rbt_node* n) {
        int res = n->elem;
        if (left(n) && right(n)) return -1;
        if (!left(n) && !right(n)) {
            if (n->parent) {
                if (left(n->parent) == n) n->parent->left = nullptr;
                else n->parent->right = nullptr;
            } else root = nullptr;
        } else {
            rbt_node* child = left(n) ? left(n) : right(n);
            if (n->parent) {
                if (left(n->parent) == n) n->parent->left = child;
                else n->parent->right = child;
                child->parent = n->parent;
            } else {
                root = child;
                child->parent = nullptr;
            }
        }
        size--;
        free(n);
        return res;
    }

    rbt_node* getRoot() { return root; }

    void zigleft(rbt_node* curr) {
        rbt_node* y = curr->parent;
        rbt_node* T2 = curr->left;
        curr->left = y;
        y->right = T2;
        if (T2) T2->parent = y;
        curr->parent = y->parent;
        if (!y->parent) root = curr;
        else if (y == y->parent->left) y->parent->left = curr;
        else y->parent->right = curr;
        y->parent = curr;
    }

    void zigright(rbt_node* curr) {
        rbt_node* y = curr->parent;
        rbt_node* T2 = curr->right;
        curr->right = y;
        y->left = T2;
        if (T2) T2->parent = y;
        curr->parent = y->parent;
        if (!y->parent) root = curr;
        else if (y == y->parent->left) y->parent->left = curr;
        else y->parent->right = curr;
        y->parent = curr;
    }

    void print() {
        if (!root) cout << "EMPTY\n";
        else print_node("", root, false);
    }

    void print_node(string prefix, rbt_node* n, bool isLeft) {
        cout << prefix << (isLeft ? "+--L: " : "+--R: ") << n->elem << (n->isRed ? " (R)" : " (B)") << "\n";
        if (n->left) print_node(prefix + "|   ", n->left, true);
        if (n->right) print_node(prefix + "|   ", n->right, false);
    }
};