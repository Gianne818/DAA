#include "node.hpp"
#include <iostream>
using namespace std;
class BSTree {
    node* root;
    int size;

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
            // restructure(curr);
            return false;
        }
        if (num == curr->element) {
            splay(curr);
            // restructure(curr);
            return true;
        }

        if (num < curr->element) {
            // restructure(curr);
            return search(curr->left, num);
        }
        // restructure(curr);
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
        return search(root, num);
    }

    bool insert(int num) {
        if (root == NULL) {
            root = create_node(num, NULL);
            size++;
            return true;
        } else {
            node* parent = search_node(root, num);
            if (parent->element != num) {
                node* newest = create_node(num, parent);
                if (parent->element < num) {
                    parent->right = newest;
                } else {
                    parent->left = newest;
                }
                size++;
                splay(newest);
                return true;
            }
        }
        return false;
    }
    
    bool remove(int num) {
        if (isEmpty()) {
            return false;
        }

        // Find the node. If not found, search_node returns the last accessed node.
        node* rem_node = search_node(root, num);
        
        // Splay the node (or the last accessed node if not found)
        splay(rem_node);

        // If the root is not the number we want, it's not in the tree.
        if (root->element != num) {
            return false;
        }

        // rem_node is now the root.
        node* left_subtree = root->left;
        node* right_subtree = root->right;

        free(root);
        size--;

        if (!left_subtree && !right_subtree) {
            root = NULL;
        } else if (!left_subtree) {
            root = right_subtree;
            root->parent = NULL;
        } else if (!right_subtree) {
            root = left_subtree;
            root->parent = NULL;
        } else {
            // Requirement: Go to the right subtree and find the leftmost node
            node* successor = right_subtree;
            while (successor->left != NULL) {
                successor = successor->left;
            }

            // Splay the successor to the top of the right subtree's context
            // Note: Since successor is the leftmost, it won't have a left child.
            while (successor->parent != right_subtree->parent) {
                restructure(successor);
            }
            
            // Now successor is the root of the right side
            successor->parent = NULL; 
            successor->left = left_subtree;
            left_subtree->parent = successor;
            root = successor;
        }

        return true;
    }

    // bool remove(int num) {
    //   if (isEmpty()) {
    //     return false;
    //   }
    //   node* rem_node = search_node(root, num);
    //   if (rem_node->element != num) {
    //     return false;
    //   }

    //   // FIND the number of children.
    //   int children = 0;
    //   // 0 - no children
    //   // -1 - left child only
    //   // 1 - right child only
    //   // 2 - both children
    //   if (rem_node->right) {
    //     children = 1;
    //   }
    //   if (rem_node->left) {
    //     if (children == 1) {
    //       children = 2;
    //     } else {
    //       children = -1;
    //     }
    //   }

    //   if (children == 0) { // NO CHILDREN
    //     node* parent = rem_node->parent;
    //     if (!parent) {
    //       root = NULL;
    //     } else {
    //       if (rem_node == parent->left) {
    //         parent->left = NULL;
    //       } else {
    //         parent->right = NULL;
    //       }
    //     }

    //     free(rem_node);
    //     size--;
    //   } else if (children == -1 || children == 1) { // ONE CHILD
    //     node* parent = rem_node->parent;
    //     node* child;
    //     if (children == -1) {
    //       child = rem_node->left;
    //     } else {
    //       child = rem_node->right;
    //     }

    //     child->parent = parent;
    //     if (!parent) {
    //       root = child;
    //     } else {
    //       if (parent->left == rem_node) {
    //         parent->left = child;
    //       } else {
    //         parent->right = child;
    //       }
    //     }

    //     free(rem_node);
    //     size--;
    //   } else { // TWO CHILDREN
    //     node* right_st = rem_node->right;
    //     while (right_st->left != NULL) {
    //       right_st = right_st->left;
    //     }

    //     int temp = right_st->element;
    //     remove(temp);
    //     rem_node->element = temp;
    //   }
    //   return true;
    // }
    
    void makeParentest(node* curr, node* y){
        if(!y->parent){
            root = curr;
            // cout << "ROOT IS NOW CURR: " << root->element << endl;
        } 
        else if (y->parent->left == y) y->parent->left = curr;
        else y->parent->right = curr;
    }

    // TODO implementation of rotate operation of x where
    //  |
    //  y
    //   \
    //    x <- curr
    void zigleft(node* curr) {
        // cout << "ZIGLEFT ON " << curr->element << endl;
        node* y = curr->parent;
        node* T2 = curr->left;
        
        if(T2) T2->parent = y;
        y->right = T2;
        
        if(!y->parent){
            root = curr;
            // cout << "ROOT IS NOW CURR: " << root->element << endl;
        } 
        else if (y->parent->left == y) y->parent->left = curr;
        else y->parent->right = curr;
        
        curr->parent = y->parent;
        y->parent = curr;
        curr->left = y;
        
        // print();
        
        
    }

    // TODO implementation of rotate operation of x where
    //   |
    //   y
    //  /
    // x <- curr
    void zigright(node* curr) {
        // cout << "ZIGRIGHT ON " << curr->element << endl;
        node* y = curr->parent;
        node* T2 = curr->right;
        
        if(T2) T2->parent = y;
        y->left = T2;
        
        
        if(!y->parent){
            root = curr;
            // cout << "ROOT IS NOW CURR: " << root->element << endl;
        } 
        else if (y->parent->left == y) y->parent->left = curr;
        else y->parent->right = curr;
        curr->parent = y->parent;
        y->parent = curr;
        curr->right = y;
        
        // print();
    }

    // GIVEN the child (or x), find the parent (or y), and the grandparent if any (or z).
    // Splay the child to the root recursively or iteratively.
    void restructure(node* child) {
        node* par; // parent
        // TODO find parent
        if(!child->parent) return;
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
            }else{
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
      }

      return;
    }
    
    node* splay(node* curr){
        while(curr->parent){
            restructure(curr);
            // print();
            // cout << "curr: " << curr->element << ", root: " <<  root->element << endl;
        }
        return curr;
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