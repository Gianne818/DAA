#include "node.hpp"
#include <iostream>
#include <cstdlib>
using namespace std;
class BSTree {
    node* root;
    int size;

    public:
    BSTree() {
        root = NULL;
        size = 0;
    }
    
    node* create_node(int num, node* par){
        node* n = new node();
        n->parent = par;
        n->element = num;
        n->is_red = true;
        n->left = nullptr;
        n->right = nullptr;
        return n;
    }
    
    // node* doubleRedRemedy(node* curr){
    //     node* par = curr->parent;
    //     node* gp = par->parent;
    //     node* uncle;
    //     if(gp->left == par) uncle = gp->right;
    //     else uncle = gp->left;
        
    //     while(curr->is_red && par->is_red){
    //         //if uncle is black
    //         if(!uncle || !uncle->is_red){
    //             //check if zigright
    //             cout << "INSERTION Violation: Case 2:\n";
    //             if(gp->left == par && par->left == curr){
    //                 cout << "ZIGRIGHT\n";
    //                 gp->is_red = true;
    //                 par->is_red = false;
    //                 curr->is_red = true;
    //                 zigright(par);
    //             }
                
    //             //check if zigzagleft
    //             else if(gp->right == par && par->left == curr){
    //                 cout << "ZIGZAGLEFT\n";
    //                 gp->is_red = true;
    //                 par->is_red = true;
    //                 curr->is_red = false;
    //                 zigright(curr);
    //                 zigleft(curr);
    //             }
                
    //             //check if zigleft
    //             else if(gp->right == par && par->right == curr){
    //                 cout << "ZIGLEFT\n";
    //                 gp->is_red = true;
    //                 par->is_red = false;
    //                 curr->is_red = true;
    //                 zigleft(par);
    //             }
                
    //             //zigzagright
    //             else {
    //                 cout << "ZIGZAGRIGHT\n";
    //                 gp->is_red = true;
    //                 par->is_red = true;
    //                 curr->is_red = false;
    //                 zigleft(curr);
    //                 zigright(curr);
    //             }
    //         } else {
    //             cout << "INSERTION Violation: Case 1:\n";
    //             uncle->is_red = false;
    //             par->is_red = false;
    //             gp->is_red = true;
    //             curr = gp;
    //         }
    //     }
    //     root->is_red = false;
    //     return curr;
    // }
    
    
    node* insert_helper(node* curr, node* par, int num){
        if(!curr){
            node* n = create_node(num, par);
            // cout << "creating node: " << n->element << ", parent: " << n->parent->element << endl;
            return n;
        }
        if(curr->element == num){
            return nullptr;
        }
        
        if(num < curr->element){
            if(curr->left == nullptr){
                node* n = create_node(num, curr);
                curr->left = n;
                return n;
            }
            else {
                return insert_helper(curr->left, curr, num);
            }
        }
            
        
        if(num > curr->element){
            if(curr->right == nullptr){
                node* n = create_node(num, curr);
                curr->right = n;
                return n;
            }
            else {
                return insert_helper(curr->right, curr, num);
            }
        }
        node* n = create_node(num, par);
        return n;
    }
    
    void recolor(node* curr){
        curr->is_red = !curr->is_red;
    }

    bool insert(int num) {
        if(!root){
           node* n = create_node(num, nullptr);
           n->is_red = false;
           root = n;
           size++;
           return true;
        } 
        else {
            node* newNode = insert_helper(root, nullptr, num);
            size++;
            
            node* par = newNode->parent;
            
            while(newNode->is_red && par->is_red){
                node* gp = par->parent;
                node* uncle;
                
                //find uncle
                if(gp->left == par) uncle = gp->right;
                else uncle = gp->left;
                
                //check if uncle is black, do restructure
                
                if(!uncle || !uncle->is_red){
                    cout << "INSERTION Violation: Case 1\n";
                    node* someNode = restructure(newNode);
                    someNode->left->is_red = true;
                    someNode->right->is_red = true;
                    someNode->is_red = false;
                    break;
                }
                
                //uncle is red, do recolor
                else {
                    cout << "INSERTION Violation: Case 2\n";
                    if(uncle) uncle->is_red = false;
                    par->is_red = false;
                    
                    if(gp!=root){
                        gp->is_red = true;
                        // cout << "newnode: " << gp->element << ", par: " << par->element << endl;
                    }
                    newNode = gp;
                    if(newNode) par = newNode->parent;
                    
                }
                
            }
            root->is_red = false;
            return true;
        }
        return false;
    }
    
    node* makeParentest(node* curr, node* y){
        if(!y->parent) root = curr;
        else if (y->parent->left == y) y->parent->left = curr;
        else y->parent->right = curr;
        return curr;
    }
    
    void zigleft(node* curr){
        node* y = curr->parent;
        node* T2 = curr->left;
        
        if(T2) T2->parent = y;
        y->right = T2;
        
        curr->parent = y->parent;
        makeParentest(curr, y);
        
        y->parent = curr;
        curr->left = y;
    }
    
    void zigright(node* curr){
        node* y = curr->parent;
        node* T2 = curr->right;
        
        if(T2) T2->parent = y;
        y->left = T2;
        
        curr->parent = y->parent;
        makeParentest(curr, y);
        
        y->parent = curr;
        curr->right = y;
    }
    
    //child
    node* restructure(node* curr){
        node* par = curr->parent;
        node* gp = par->parent;
        
        bool gtop_right = true;
        if(gp->left == par) gtop_right = false;
        
        //find child
        bool ptoc_right = true;
        if(par->left == curr) ptoc_right = false;
        
        
        //explicit conditions for less thinking
        if(gp && gtop_right && ptoc_right){
            cout << "ZIGLEFT\n";
            zigleft(par);
            return par;
        }
        
        else if(gp && gtop_right && !ptoc_right){
            cout << "ZIGZAGLEFT\n";
            zigright(curr);
            zigleft(curr);
            return curr;
        }
        
        
        else if (gp && !gtop_right && !ptoc_right){
            cout << "ZIGRIGHT\n";
            zigright(par);
            return par;
        }
        
        else if (gp && !gtop_right && ptoc_right){
            cout << "ZIGZAGRIGHT\n";
            zigleft(curr);
            zigright(curr);
            return curr;
        }
        
        //no gp
        else if (ptoc_right){
            cout << "ZIGLEFT\n";
            zigleft(par);
            return par;
        }
        
        else {
            cout << "ZIGRIGHT\n";
            zigright(par);
            return par;
        }
    }

    // WARNING. Do not modify these methods below.
    // Doing so will nullify your score for this activity.
    void print() {
        if (isEmpty()) {
            cout << "EMPTY" << endl;
            return;
        }
        cout << "PRE-ORDER: ";
        print_preorder(root);
        cout << endl << "IN-ORDER: ";
        print_inorder(root);
        cout << endl << "POST-ORDER: ";
        print_postorder(root);
        cout << endl << "STATUS: " << check_parent(root, NULL) << endl;
    }

    bool isEmpty() {
        return size == 0;
    }

    void print_preorder(node* curr) {
        cout << curr->element;
        if (curr->is_red) {
            cout << "(R) ";
        } else {
            cout << "(B) ";
        }
        if (curr->left != NULL) {
            print_preorder(curr->left);
        }
        if (curr->right != NULL) {
            print_preorder(curr->right);
        }
    }

    void print_inorder(node* curr) {
        if (curr->left != NULL) {
            print_inorder(curr->left);
        }
        cout << curr->element;
        if (curr->is_red) {
            cout << "(R) ";
        } else {
            cout << "(B) ";
        }
        if (curr->right != NULL) {
            print_inorder(curr->right);
        }
    }

    void print_postorder(node* curr) {
        if (curr->left != NULL) {
            print_postorder(curr->left);
        }
        if (curr->right != NULL) {
            print_postorder(curr->right);
        }
        cout << curr->element;
        if (curr->is_red) {
            cout << "(R) ";
        } else {
            cout << "(B) ";
        }
    }

    // WARNING. Do not modify this method.
    // Doing so will nullify your score for this activity.
    bool check_parent(node* curr, node* par) {
        if (!curr) {
            return true;
        }
        if (curr->parent != par) {
            if (!curr->parent) {
                cout << "Illegal parent of " << curr->element << ": NULL -- must be " << par->element << endl;
            } else if (!par) {
                cout << "Illegal parent of " << curr->element << ": " << curr->parent->element << "must be NULL" << endl;
            } else {
                cout << "Illegal parent of " << curr->element << ": " << curr->parent->element << " -- must be " << par->element << endl;
            }
            return false;
        }
        return check_parent(curr->left, curr) && check_parent(curr->right, curr);
    }
};