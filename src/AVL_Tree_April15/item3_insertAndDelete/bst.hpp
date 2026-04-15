#include "mybinarytree.hpp"
 
class BST {
	BinaryTree* tree = new MyBinaryTree();

    void rebalance(node* curr){
        while(curr){
            int bf = curr->getBalance();
            if(bf > 1 || bf < -1){
                restructure(curr);
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
        node* inserted = insert_node(n, num);
        rebalance(inserted);
        return inserted;
    }

    // node* insert(int num){
    //     node* n = tree->getRoot();
    //     if(!n) return tree->addRoot(num);
    //     node* newNode = insert_node(n, num);

    //     rebalance(newNode);
    //     return newNode;
    // }

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

    // node* insert_node(node* n, int num) {
    //    if(!n) return nullptr;

    //    if(n->elem == num){
    //         return nullptr;
    //    }


    //    if(num < n->elem){
    //         if(!n->left) return tree->addLeft(n, num);
    //         else return insert_node(n->left, num);
    //    }
    //    else{
    //         if(!n->right) return tree->addRight(n, num);
    //         else return insert_node(n->right, num);
    //    } 
    // }
 
 
    // TODO perform post-processing by checking for violation after deletion
    // from the parent of the node removed until the root
    bool remove(int num) {
        return remove_node(tree->getRoot(), num);
    }

    bool remove_node(node* n, int num) {
        if (n == NULL) {
            return false;
        }
        if (n->elem == num) {
            node* par = n->parent;
            if (n->left && n->right) {
                node* r = n->right;
                while (r->left) {
                    r = r->left;
                }
                node* rPar = r->parent;
                int rem = tree->remove(r);
                n->elem = rem;
                rebalance(rPar);
            } else {
                tree->remove(n);
                rebalance(par);
            }
            return true;
        }
        if (num > n->elem) {
            return remove_node(n->right, num);
        } else {
            return remove_node(n->left, num);
        }
    }

    // bool remove_node(node* n, int num){
    //     if(!n) return false;

    //     if(n->elem == num){
    //         node* par = n->parent;
    //         if(n->left && n->right){
    //             node* r = n->right;
    //             while(r->left){
    //                 r = r->left;
    //             }

    //             node* rPar = r->parent;
    //             int temp = tree->remove(r);
    //             n->elem = temp;
    //             rebalance(rPar);
    //         } else {
    //             tree->remove(n);
    //             rebalance(par);

    //         }
    //         return true;
    //     }

    //     if(n->elem > num){
    //         return remove_node(n->left, num);
    //     } else {
    //         return remove_node(n->right, num);
    //     }
    // }
 
    // TODO copy and paste your completed restructure method here
    // GIVEN the grandparent (or z), find the parent (or y), and the child (or x).
    bool restructure(node* gp) {
        node* par;
        // TODO find parent
        int gpLH = gp->left ? gp->left->height() : -1;
        int gpRH = gp->right ? gp->right->height() : -1;
        par = (gpLH > gpRH) ? gp->left : gp->right;

        // This is an indicator of the placement of grandparent to parent (gtop)
        bool gtop_right = false;
        if(gp->right == par) gtop_right = true;
    
        node* child;
        // TODO find child
        int pLH = par->left ? par->left->height() : -1;
        int pRH = par->right ? par->right->height() : -1;
        if(pLH > pRH) child = par->left;
        else if (pLH < pRH) child =  par->right;
        else child = (par == gp->left) ? par->left : par->right; 

        // This is an indicator of the placement of parent to child (ptoc)
        bool ptoc_right = false;
        if(child == par->right) ptoc_right = true;
        

        // FOR THE FOLLOWING: Write in each of the if statements a console output
        // on its corresponding operation (ZIGLEFT, ZIGRIGHT, ZIGZAGLEFT, or ZIGZAGRIGHT)

        // z
        //  \
        //   y
        //    \
        //     x
        if (gtop_right && ptoc_right) {
            cout << "ZIGLEFT\n";
            tree->zigleft(par);
        }

            // z
            //   \
            //     y
            //    /
            //   x
        else if (gtop_right) {
            cout << "ZIGZAGLEFT\n";
            tree->zigright(child);
            tree->zigleft(child);
        }

            //     z
            //    /
            //   y
            //  /
            // x
        else if (!ptoc_right) {
            cout << "ZIGRIGHT\n";
            tree->zigright(par);
        }

            //      z
            //    /
            //  y
            //   \
            //    x
        else {
            cout << "ZIGZAGRIGHT\n";
            tree->zigleft(child);
            tree->zigright(child);
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