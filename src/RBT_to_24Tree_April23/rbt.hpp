#pragma once
#include "mybinarytree.hpp"
#include "btree24_node.hpp"
using namespace std;

class RBT {
public:
    BinaryTree* tree = new MyBinaryTree();

    rbt_node* getRoot() { return tree->getRoot(); }

    void recolor(rbt_node* curr) {
        curr->isRed = !curr->isRed;
    }

    void doubleRedRemedy(rbt_node* curr) {
        while (curr->parent && curr->parent->isRed) {
            rbt_node* par = curr->parent;
            rbt_node* gp = par->parent;
            rbt_node* uncle;
            if (gp->left == par) uncle = gp->right;
            else uncle = gp->left;

            if (uncle && uncle->isRed) {
                recolor(uncle);
                recolor(par);
                recolor(gp);
                curr = gp;
            } else {
                if (gp->right == par && par->right == curr) {
                    recolor(par);
                    recolor(gp);
                    tree->zigleft(par);
                } else if (gp->right == par && par->left == curr) {
                    recolor(curr);
                    recolor(gp);
                    tree->zigright(curr);
                    tree->zigleft(curr);
                } else if (gp->left == par && par->right == curr) {
                    recolor(curr);
                    recolor(gp);
                    tree->zigleft(curr);
                    tree->zigright(curr);
                } else {
                    recolor(par);
                    recolor(gp);
                    tree->zigright(par);
                }
            }
        }
        tree->getRoot()->isRed = false;
    }

    rbt_node* insert(int num) {
        rbt_node* n = tree->getRoot();
        if (n == NULL) {
            rbt_node* newRoot = tree->addRoot(num);
            newRoot->isRed = false;
            return newRoot;
        }
        rbt_node* inserted = insert_node(n, num);
        if (inserted != NULL) {
            doubleRedRemedy(inserted);
        }
        return inserted;
    }

    rbt_node* insert_node(rbt_node* n, int num) {
        if (n == NULL || n->elem == num) return NULL;
        if (num > n->elem) {
            if (!n->right) return tree->addRight(n, num);
            else return insert_node(n->right, num);
        } else {
            if (!n->left) return tree->addLeft(n, num);
            else return insert_node(n->left, num);
        }
    }

    void print() {
        tree->print();
    }

private:
    rbt_node* createRBTNode(int elem, bool isRed, rbt_node* parent) {
        rbt_node* n = (rbt_node*)calloc(1, sizeof(rbt_node));
        n->elem = elem;
        n->isRed = isRed;
        n->parent = parent;
        return n;
    }

    rbt_node* convertToRBTNode(btree24_node* n24, rbt_node* parent) {
        if (!n24) return nullptr;

        rbt_node* blackNode = nullptr;

        if (n24->size == 1) {
            blackNode = createRBTNode(n24->keys[0], false, parent);
            blackNode->left = convertToRBTNode(n24->children[0], blackNode);
            blackNode->right = convertToRBTNode(n24->children[1], blackNode);
        } else if (n24->size == 2) {
            blackNode = createRBTNode(n24->keys[0], false, parent);
            rbt_node* redRight = createRBTNode(n24->keys[1], true, blackNode);
            blackNode->right = redRight;

            blackNode->left = convertToRBTNode(n24->children[0], blackNode);
            redRight->left = convertToRBTNode(n24->children[1], redRight);
            redRight->right = convertToRBTNode(n24->children[2], redRight);
        } else if (n24->size == 3) {
            blackNode = createRBTNode(n24->keys[1], false, parent);
            rbt_node* redLeft = createRBTNode(n24->keys[0], true, blackNode);
            rbt_node* redRight = createRBTNode(n24->keys[2], true, blackNode);
            
            blackNode->left = redLeft;
            blackNode->right = redRight;

            redLeft->left = convertToRBTNode(n24->children[0], redLeft);
            redLeft->right = convertToRBTNode(n24->children[1], redLeft);
            redRight->left = convertToRBTNode(n24->children[2], redRight);
            redRight->right = convertToRBTNode(n24->children[3], redRight);
        }
        return blackNode;
    }

public:
    void convertFrom24Tree(btree24_node* root24) {
        rbt_node* newRoot = convertToRBTNode(root24, nullptr);
        tree->setRoot(newRoot);
    }
};