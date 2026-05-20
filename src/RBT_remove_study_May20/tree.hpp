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
    
    node* create_node(node* parent, int num){
        node* n = new node();
        n->parent = parent;
        n->element = num;
        n->is_red = true;
        n->left = nullptr;
        n->right = nullptr;
        return n;
    }
    
    node* search_node(node* curr, int num){
        if(curr == nullptr) return nullptr;
    
        if(num < curr->element){
            if(curr->left != nullptr) return search_node(curr->left, num);
        }
        else {
            if(curr->right!=nullptr) return search_node(curr->right, num);
        }
        return curr;
    }
    
    bool insert(int num){
        if(root == nullptr){
            node* n = create_node(nullptr, num);
            n->is_red = false;
            size++;
            root = n;
            return true;
        }
        
        node* par = search_node(root, num);
        if(par->element != num){
            node* n = create_node(par, num);
            if(par->element < num) par->right = n;
            else par->left = n;
            size++;
            
            while(n->is_red && par->is_red){
                // find uncle
                node* uncle = nullptr;
                node* gp = par->parent;
                if(gp->left == par){
                    uncle = gp->right;
                }
                else uncle = gp->left;
                
                // uncle is black, we perform a restructure
                if(!uncle || !uncle->is_red){
                    cout << "INSERTION Violation: Case 1\n";
                    node* someNode = restructure(n);
                    someNode->left->is_red = true;
                    someNode->right->is_red = true;
                    someNode->is_red = false;
                    break;
                }
                
                //uncle is red, perform recolor
                 else {
                    cout << "INSERTION Violation: Case 2\n";
                    uncle->is_red = false;
                    par->is_red = false;
                    
                    if(gp != root){
                        gp->is_red = true;
                    }
                    n = gp;
                    if(n) par = n->parent;
                 }
            }
            root->is_red = false;
            return true;
        }
        return false;
    }
    
    // case 1: sibling is black with red child, rotate on sibling
    // case 2:  sibling is black with no red child, recolor, parent=black
    // case 3:  sibling is red, rotate on par and recolor sibling
    void deleteFix(node* n){
        node* curr = n;
        while(curr->parent && !curr->is_red){
            if(curr->parent->left == curr){
                //sibling is right child
                node* sibling = curr->parent->right;
                
                // case 3
                if(sibling->is_red){
                   cout << "DELETION Violate: Case 3\n";
                   curr->parent->is_red = true;
                   sibling->is_red = false;
                   zigleft(sibling);
                   sibling = curr->parent->right;
                }
                
                //case 2
                if((!sibling->right || !sibling->right->is_red) &&
                (!sibling->left || !sibling->left->is_red)){
                    cout << "DELETION Violation: Case 2\n";
                    sibling->is_red = true;
                    curr = curr->parent;
                    
                } 
                
                // case 1
                else {
                    cout << "DELETION Violation: Case 1\n";
                    
                    // check for right child of sib
                    if(sibling->right && sibling->right->is_red){
                        //capture the color of the parent
                        node* newParent = restructure(sibling->right);
                        newParent->is_red = curr->parent->is_red;
                        if(newParent->left) newParent->left->is_red = false;
                        if(newParent->right) newParent->right->is_red = false;
                        
                    }
                    else if (sibling->left && sibling->left->is_red){
                        node* newParent = restructure(sibling->left);
                        newParent->is_red = curr->parent->is_red;
                        if(newParent->left) newParent->left->is_red = false;
                        if(newParent->right) newParent->right->is_red = false;
                    }
                    curr = root; // no further fixes needed for case 1`
                }
            }
            
            // mura ra siyag balik, but when sibling is left child
            else {
                node* sibling = curr->parent->left;
                
                if(sibling->is_red){
                    //resrtucture and  consider doule black
                    cout << "DELETION Violation: Case 3\n";
                    curr->parent->is_red = true;
                    sibling->is_red = false;
                    zigright(sibling);
                    sibling = curr->parent->left;
                }
                
                // case 2: sibling is black and no red child
                else if ((!sibling->right || !sibling->right->is_red) &&
                (!sibling->left || !sibling->left->is_red)){
                    cout << "DELETION Violation: Case 2\n";
                    sibling->is_red = true;
                    curr = curr->parent;
                }
                
                // case 1
                else {
                    cout << "DELETION Violaion: Case 1\n";
                    // check first for the left
                    if (sibling->left && sibling->left->is_red){
                        // should result in a zig only
                        node* newParent = restructure(sibling->left);
                        newParent->is_red = curr->parent->is_red;
                        if(newParent->left) newParent->left->is_red = false;
                        if(newParent->right) newParent->right->is_red = false;
                    }
                    else if(sibling->right && sibling->right->is_red){
                        node* newParent = restructure(sibling->right);
                        newParent->is_red = curr->parent->is_red;
                        if(newParent->right) newParent->right->is_red = false;
                        if(newParent->left) newParent->left->is_red = false;
                    }
                    curr = root;
                }
            }
                
        } 
        curr->is_red = false; // so that root is always black
    }
    
    bool remove(int num){
        if(size == 0) return false;
        
        node* rem_node = search_node(root, num);
        if(rem_node->element != num) return false;
        
        int children = 0;
        // 0 - no children
        // -1 - left child only
        // 1 - right child only
        // 2 - both children
        
        if(rem_node->right){
            children = 1;
        }
        if(rem_node->left){
            if(children == 1){
                children = 2;
            }
            else {
                children = -1;
            }
        }
        
        if(children == 0){
            if(!rem_node->is_red){
                deleteFix(rem_node);
            }
            
            node* par = rem_node->parent;
            if(!par) root = nullptr;
            else if(par->left == rem_node) par->left = nullptr;
            else par->right = nullptr;
            
            free(rem_node);
            size--;
            return true;
        }
        
        else if (children == -1 || children == 1){
            node* par = rem_node->parent;
            node* child;
            
            if(children == -1) child = rem_node->left;
            else child = rem_node->right;
            
            child->parent = par;
            
            if(!par) root = child;
            else if (par->left == rem_node) par->left = child;
            else par->right = child;
            
            if(!rem_node->is_red){
                child->is_red = false;
            }
            
            free(rem_node);
            size--;
            return true;
            
        }
        else {
            node* right_st = rem_node->right;
            while(right_st->left != nullptr){
                right_st = right_st->left;
            }
            
            int temp = right_st->element;
            remove(temp); // recursive call
            rem_node->element = temp;
            return true;
        }
        return false;
    }
    
    void recolor(node* curr){
        curr->is_red = !curr->is_red;
    }
    
    void makeParentest(node* curr, node* y){
        if(!y->parent) root = curr;
        else if (y->parent->left == y) y->parent->left = curr;
        else y->parent->right = curr;
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
        
        // find subtree T2 parent and connect them
        if(T2) T2->parent = y;
        y->left = T2;
        
        //make curr the parent;
        curr->parent = y->parent;
        makeParentest(curr, y);
        
        y->parent = curr;
        curr->right = y;
        
    }
    
    node* restructure(node* curr){
        node* par = curr->parent;
        node* gp = par->parent;
        
        
        bool gtop_right = true;
        if(gp->left == par) gtop_right = false;
        
        bool ptoc_right = true;
        if(par->left == curr) ptoc_right = false;
        
        if(gtop_right && ptoc_right){
            cout << "ZIGLEFT\n";
            zigleft(par);
            return par;
        }
        
        else if(gtop_right && !ptoc_right){
            cout << "ZIGZAGLEFT\n";
            zigright(curr);
            zigleft(curr);
            return curr;
        }
        
        else if(!gtop_right && !ptoc_right){
            cout << "ZIGRIGHT\n";
            zigright(par);
            return par;
        }
        
        else {
            cout << "ZIGZAGRIGHT\n";
            zigleft(curr);
            zigright(curr);
            return curr;
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