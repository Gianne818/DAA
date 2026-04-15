#include "mybinarytree.hpp"
 
class BST {
	BinaryTree* tree = new MyBinaryTree();
	void rebalance(node* curr){
	    while(curr){
	        int bal = curr->getBalance();
	        //cout << bal << endl;
	        if(bal > 1 || bal < -1){
	            restructure(curr);
	            break;
	        }
	        curr = curr->parent;
	    }
	}

 
	public:
	bool search(int num) {
		return search_node(tree->getRoot(), num);
	}
 
	bool search_node(node* n, int num) {
		if (n == NULL) {
			return false;
		}
		if (n->elem == num) {
			return true;
		}
		if (num > n->elem) {
			// proceed to right
			return search_node(n->right, num);
		} else {
			return search_node(n->left, num);
		}
	}
 
    // TODO perform post-processing by checking for violation after insertion
    // from the node inserted (or from its parent) until the root
	node* insert(int num) {
		node* n = tree->getRoot();
		if (n == NULL) {
			return tree->addRoot(num);
		}
		node* newNode = insert_node(n, num);
		rebalance(newNode);
		return newNode;
	}
 
	node* insert_node(node* n, int num) {
		if (n == NULL) {
			return NULL;
		}
		if (n->elem == num) {
			return NULL;
		}
		if (num > n->elem) {
			if (!n->right) {
				return tree->addRight(n, num);
			} else {
				return insert_node(n->right, num);
			}
		} else {
			if (!n->left) {
				return tree->addLeft(n, num);
			} else {
				return insert_node(n->left, num);
			}
		}
	}
 
 
    // TODO perform post-processing by checking for violation after deletion
    // from the parent of the node removed until the root
    bool remove(int num) {
        return remove_node(tree->getRoot(), num);
    }
 
	bool remove_node(node* n, int num) {
	    if (n == NULL) {
			return false;
		}
	    node* parent = nullptr;
	    if(search_node(n, num)){
	        parent = n->parent;
	    }
		if (n->elem == num) {
            if (n->left && n->right) {
                node* r = n->right;
                while (r->left) {
                    r = r->left;
                }
                node* p = r->parent;
                int rem = tree->remove(r);
                n->elem = rem;
                rebalance(p);
            } else {
    			tree->remove(n);
    			rebalance(parent);
            }

            return true;
		}
		if (num > n->elem) {
			return remove_node(n->right, num);
		} else {
			return remove_node(n->left, num);
		}
	}
 
    // TODO copy and paste your completed restructure method here
    // GIVEN the grandparent (or z), find the parent (or y), and the child (or x).
    bool restructure(node* gp) {
        node* par; // parent
        // TODO find parent
        int lh = gp->left ? gp->left->height() : -1;
        int rh = gp->right ? gp->right->height() : -1;
        par = (lh > rh) ? gp->left : gp->right;
 
        // This is an indicator of the placement of grandparent to parent (gtop)
        bool gtop_right = false;
        if (gp->right == par) {
            gtop_right = true;
        }
 
        node* child;
        // TODO find child
        int lh1 = par->left ? par->left->height() : -1;
        int rh1 = par->right ? par->right->height() : -1;
        if(lh1 > rh1){
            child = par->left;
        }else if(rh1 > lh1){
            child = par->right;
        }else{
            child = (par == gp->left) ? par->left : par->right;
        }
 
        // This is an indicator of the placement of parent to child (ptoc)
        bool ptoc_right = false;
        if (par->right == child) {
            ptoc_right = true;
        }
 
        // FOR THE FOLLOWING: Write in each of the if statements a console output
        // on its corresponding operation (ZIGLEFT, ZIGRIGHT, ZIGZAGLEFT, or ZIGZAGRIGHT)
 
        // z
        //  \
        //   y
        //    \
        //     x
        if (gtop_right && ptoc_right) {
            zigleft(par);
            cout << "ZIGLEFT" << endl;
        }
 
        // z
        //   \
        //     y
        //    /
        //   x
        else if (gtop_right && !ptoc_right) {
            zigright(child);
            zigleft(child);
            cout << "ZIGZAGLEFT" << endl;
            // TODO call to either zigleft or zigright or both
        }
 
        //     z
        //    /
        //   y
        //  /
        // x
        else if (!gtop_right && !ptoc_right) {
            zigright(par);
            cout << "ZIGRIGHT" << endl;
            // TODO call to either zigleft or zigright or both
        }
 
        //      z
        //    /
        //  y
        //   \
        //    x
        else {
            zigleft(child);
            zigright(child);
            cout << "ZIGZAGRIGHT" << endl;
            // TODO call to either zigleft or zigright or both
        }
 
        return true;
    }
 
    void zigleft(node* curr) {
        tree->zigleft(curr);
    }
 
    void zigright(node* curr) {
        tree->zigright(curr);
    }
 
	void print() {
		tree->print();
	}
};