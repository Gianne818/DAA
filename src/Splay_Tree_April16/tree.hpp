#include "node.hpp"
#include <iostream>
using namespace std;
class BSTree {
    node* root;
    int size;
    
    node* splay(node* curr){
        while(curr->parent){
            restructure(curr);
        }
        return curr;
    }

    node* create_node(int num, node* parent) {
        node* n = (node*) malloc( sizeof(node) );
        n->element = num;
        n->parent = parent;
        n->right = NULL;
        n->left = NULL;
        return n;
    }

    bool search(node* curr, int num) {
        if (curr == NULL) {
            return false;
        }
        if (num == curr->element) {
            return true;
        }

        if (num < curr->element) {
            return search(curr->left, num);
        }
        return search(curr->right, num);
    }

    node* search_node(node* curr, int num) {
        if (num == curr->element) {
            return curr;
        }

        if (num < curr->element) {
            if (curr->left != NULL) {
                return search_node(curr->left, num);
            }
            return curr;
        }
        if (curr->right != NULL) {
            return search_node(curr->right, num);
        }
        return curr;
    }

    public:
    BSTree() {
        root = NULL;
        size = 0;
    }

    bool search(int num) {
        if(isEmpty()) return false;
        
        node* curr = search_node(root, num);
        splay(curr);
        return true;
    }

    bool insert(int num) {
        if(root == nullptr){
            root = create_node(num, nullptr);
            size++;
            return true;
        } else {
            node* par = search_node(root, num);
            if(par->element != num){
                node* newNode = create_node(num, par);
                if(num < par->element){
                    par->left = newNode;
                }
                else {
                    par->right = newNode;
                }
                splay(newNode);
                size++;
                return true;
            }
        }
        return false;
    }

    bool remove(int num) {
      if (isEmpty()) {
        return false;
      }
      node* rem_node = search_node(root, num);
      splay(rem_node);
      
      if (rem_node->element != num) {
        return false;
      }
      
      node* left_st = rem_node->left;
      node* right_st = rem_node->right;
      
      if(left_st) left_st->parent = nullptr;
      if(right_st) right_st->parent = nullptr;
      
      
      if(!left_st && !right_st){
          root = nullptr;
      }
      else if (left_st && !right_st){
          root = left_st;
      }
      else if (right_st && !left_st){
          root = right_st;
      }
      
      else {
          node* succ = right_st;
          while(succ->left){
              succ = succ->left;
          }
          
          while(succ->parent){
              restructure(succ);
          }
          
          succ->parent = nullptr;
          succ->left = left_st;
          left_st->parent = succ;
          root = succ;
      }
      
      free(rem_node);
      size--;

      return false;
    }
    
    void makeParentest(node* curr, node* y){
        if(!y->parent) root = curr;
        else if (y->parent->left == y) y->parent->left = curr;
        else y->parent->right = curr;
    }

    // TODO implementation of rotate operation of x where
    //  |
    //  y
    //   \
    //    x <- curr
    void zigleft(node* curr) {
        node* y = curr->parent;
        node* T2 = curr->left;
        
        if(T2) T2->parent = y;
        y->right = T2;
        
        curr->parent = y->parent;
        makeParentest(curr, y);
        
        curr->left = y;
        y->parent = curr;
        
    }

    // TODO implementation of rotate operation of x where
    //   |
    //   y
    //  /
    // x <- curr
    void zigright(node* curr) {
        node* y = curr->parent;
        node* T2 = curr->right;
        
        if(T2) T2->parent = y;
        y->left = T2;
        
        curr->parent = y->parent;
        makeParentest(curr, y);
        
        curr->right = y;
        y->parent = curr;
    }

    // GIVEN the child (or x), find the parent (or y), and the grandparent if any (or z).
    // Splay the child to the root recursively or iteratively.
    void restructure(node* child) {
        node* par; // parent
        // TODO find parent
        par = child->parent;

        // This is an indicator of the placement of parent to child (ptoc)
        bool ptoc_right = false;
        if (par->right == child) {
            ptoc_right = true;
        }

        node* gp;
        // TODO find grandparent. If gp does not exist, proceed to doing ZIGLEFT or ZIGRIGHT.
        
        if(!par->parent){
            if(ptoc_right){
                cout << "ZIGLEFT\n";
                zigleft(child);
                return;
            }
            else {
                cout << "ZIGRIGHT\n";
                zigright(child);
                return;
            }
        }
        else gp = par->parent;
        
        // This is an indicator of the placement of grandparent to parent (gtop)
        bool gtop_right = false;
        if (gp->right == par) {
            gtop_right = true;
        }

        // FOR THE FOLLOWING: Write in each of the if statements a console output
        // on its corresponding operation (ZIGZIGLEFT, ZIGZIGRIGHT, ZIGZAGLEFT, or ZIGZAGRIGHT)

      // z
      //  \
      //   y
      //    \
      //     x
      if (gtop_right && ptoc_right) {
        // TODO call to either zigleft or zigright or both
        cout << "ZIGZIGLEFT\n";
        zigleft(par);
        zigleft(child);
        // return par;
      }

      // z
      //   \
      //     y
      //    /
      //   x
      else if (gtop_right && !ptoc_right) {
        // TODO call to either zigleft or zigright or both
        cout << "ZIGZAGLEFT\n";
        zigright(child);
        zigleft(child);
        // return curr;
      }

      //     z
      //    /
      //   y
      //  /
      // x
      else if (!gtop_right && !ptoc_right) {
        // TODO call to either zigleft or zigright or both
        cout << "ZIGZIGRIGHT\n";
        zigright(par);
        zigright(child);
        // return par;
      }

      //      z
      //    /
      //  y
      //   \
      //    x
      else {
        // TODO call to either zigleft or zigright or both
        cout << "ZIGZAGRIGHT\n";
        zigleft(child);
        zigright(child);
        // return curr;
      }

      return;
    }

    // WARNING. Do not modify the methods below.
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
        cout << curr->element << " ";
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
        cout << curr->element << " ";
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
        cout << curr->element << " ";
    }

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