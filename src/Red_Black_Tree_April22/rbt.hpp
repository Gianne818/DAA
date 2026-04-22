#include "mybinarytree.hpp"
 
class RBT {
	BinaryTree* tree = new MyBinaryTree();

 
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

    void recolor(node* curr){
        curr->isRed = !curr->isRed;
    }

    //curr is the child
    void doubleRedRemedy(node* curr){
        while(curr->parent && curr->parent->isRed){
            node* par = curr->parent;
            node* gp = par->parent;
            node* uncle;
            if(gp->left == par) uncle = gp->right;
            else uncle = gp->left;

            // check uncle
            //uncle is red, we do recolor
            if(uncle && uncle->isRed){
                recolor(uncle);
                recolor(par);
                recolor(gp);
                curr = gp;
            } 
            
            //uncle is black or null
            else {
                //check for zigleft;
                if(gp->right == par && par->right == curr){
                    recolor(par);
                    recolor(gp);
                    zigleft(par);
                } 
                //check for zigzagleft
                else if (gp->right == par && par->left == curr){
                    recolor(curr);
                    recolor(gp);
                    zigright(curr);
                    zigleft(curr);
                }
                
                //check for zigzagright
                else if (gp->left == par && par->right == curr){
                    recolor(curr);
                    recolor(gp);
                    zigleft(curr);
                    zigright(curr);
                }
                
                //zigright
                else {
                    recolor(par);
                    recolor(gp);
                    zigright(par);
                }
            }
        }
        tree->getRoot()->isRed = false;
    }
 
	node* insert(int num) {
        node* n = tree->getRoot();
        if (n == NULL) {
            node* newNode = tree->addRoot(num);
            newNode->isRed = false;
            return newNode;
        }
        node* inserted = insert_node(n, num);
        if(inserted) doubleRedRemedy(inserted);
        return inserted;
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
            } else {
                tree->remove(n);
            }
            return true;
        }
        if (num > n->elem) {
            return remove_node(n->right, num);
        } else {
            return remove_node(n->left, num);
        }
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