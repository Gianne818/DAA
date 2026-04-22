#include "node.hpp"
#include <iostream>
#include <cstdlib>

using namespace std;

class BTree24 {
    node* root;

    // Helper to initialize a new node with children array
    node* createEmptyNode() {
        node* newNode = (node*)calloc(1, sizeof(node));
        newNode->children = (node**)calloc(5, sizeof(node*));
        newNode->size = 0;
        newNode->parent = nullptr;
        return newNode;
    }

    // Splits a node that has overflowed (size == 4)
    void split(node* w) {
        node* u = w->parent;
        int uch = 0;

        // Step 1: Handle Parent/Root Promotion
        if (!u) {
            u = createEmptyNode();
            u->insertKeyAt(w->keys[2], 0);
            root = u;
        } else {
            // Find index in parent to insert the promoted key
            for (uch = 0; uch <= u->size; uch++) {
                if (u->children[uch] == w) break;
            }
            u->insertKeyAt(w->keys[2], uch);
        }

        // Step 2: Create Left Sibling (wpr) - keys 0 and 1
        node* wpr = createEmptyNode();
        wpr->parent = u;
        wpr->insertKeyAt(w->keys[0], 0);
        wpr->insertKeyAt(w->keys[1], 1);
        
        for (int j = 0; j < 3; j++) {
            wpr->children[j] = w->children[j];
            if (wpr->children[j]) wpr->children[j]->parent = wpr;
        }

        // Step 3: Create Right Sibling (w2pr) - key 3
        node* w2pr = createEmptyNode();
        w2pr->parent = u;
        w2pr->insertKeyAt(w->keys[3], 0);
        
        for (int j = 0; j < 2; j++) {
            w2pr->children[j] = w->children[3 + j];
            if (w2pr->children[j]) w2pr->children[j]->parent = w2pr;
        }

        // Step 4: Update Parent's children pointers
        for (int i = 4; i > uch; i--) {
            u->children[i] = u->children[i - 1];
        }
        u->children[uch] = wpr;
        u->children[uch + 1] = w2pr;

        delete w;

        // Step 5: Recurse if the parent now has 4 keys
        if (u->size == 4) {
            split(u);
        }
    }

public:
    BTree24() : root(nullptr) {}

    node* search_sir(int num, node* n) {
        if (n == nullptr) return nullptr;

        for (int i = 0; i < n->size; i++) {
            if (n->keys[i] == num) return n;
            if (n->keys[i] > num) {
                if (n->children[i]) return search_sir(num, n->children[i]);
                return n;
            }
        }
        if (n->children[n->size] != nullptr) {
            return search_sir(num, n->children[n->size]);
        }
        return n;
    }

    bool insert(int num) {
        // Case 1: Empty Tree
        if (root == nullptr) {
            root = createEmptyNode();
            root->insertKeyAt(num, 0);
            return true;
        }

        // Case 2: Find leaf and check for duplicates
        node* w = search_sir(num, root);
        if (w->contains(num)) return false;

        // Case 3: Insert into leaf
        int i;
        for (i = 0; i < w->size; i++) {
            if (num < w->keys[i]) break;
        }
        w->insertKeyAt(num, i);

        // Case 4: Handle potential overflow
        if (w->size == 4) {
            split(w);
        }

        return true;
    }

    	bool remove(int num) {
	    if (!root) return false;
	    
	    node* w = search_sir(num, root);
	    
	    // If node doesn't exist or doesn't contain the key, nothing to remove
	    if (!w || !w->contains(num)) {
	        return false;
	    }
	    
	    // Find the exact index of the key to remove
	    int idx = 0;
	    for (int i = 0; i < w->size; i++) {
	        if (w->keys[i] == num) {
	            idx = i;
	            break;
	        }
	    }
	    
	    // If 'w' is an internal node, swap the key with its in-order predecessor
	    if (w->children[0] != nullptr) {
	        // The right child branch of keys[idx] is at children[idx + 1]
	        node* succ = w->children[idx + 1];
	        
	        // Keep going left to find the smallest key in the right subtree
	        while (succ->children[0] != nullptr) {
	            succ = succ->children[0];
	        }
	        
	        // Swap the value with the successor's leftmost key (index 0)
	        w->keys[idx] = succ->keys[0];
	        
	        // Now, we switch our focus to deleting the swapped key from the leaf
	        w = succ;
	        idx = 0;
	    }
	    
	    // Remove the key from the leaf node by shifting keys over
	    for (int i = idx; i < w->size - 1; i++) {
	        w->keys[i] = w->keys[i + 1];
	    }
	    w->size--;
	    
	    // Handle Underflow (Node has 0 keys). Bubble up if necessary.
	    while (w->size == 0 && w != root) {
	        node* p = w->parent;
	        int c_idx = 0;
	        
	        // Find which child index 'w' is in its parent
	        for (int i = 0; i <= p->size; i++) {
	            if (p->children[i] == w) {
	                c_idx = i;
	                break;
	            }
	        }
	        
	        // Identify siblings
	        node* left_sib = (c_idx > 0) ? p->children[c_idx - 1] : nullptr;
	        node* right_sib = (c_idx < p->size) ? p->children[c_idx + 1] : nullptr;
	        
	        // Case 1: Transfer/Borrow from Left Sibling
	        // Determine sizes safely (0 if sibling doesn't exist)
	        int l_size = left_sib ? left_sib->size : 0;
	        int r_size = right_sib ? right_sib->size : 0;
	        
	        // Case 1 & 2: Transfer/Borrow from the sibling with MORE keys.
	        // In case of a tie, prefer the Right sibling.
	        if (l_size > 1 || r_size > 1) {
	            if (l_size > r_size) {
	                // --- BORROW FROM LEFT SIBLING ---
	                // Make room in 'w'
	                for (int i = w->size; i > 0; i--) w->keys[i] = w->keys[i - 1];
	                for (int i = w->size + 1; i > 0; i--) w->children[i] = w->children[i - 1];
	                
	                // Pull down parent key into 'w'
	                w->keys[0] = p->keys[c_idx - 1];
	                w->children[0] = left_sib->children[left_sib->size]; 
	                if (w->children[0]) w->children[0]->parent = w;
	                w->size++;
	                
	                // Push sibling's rightmost key up to parent
	                p->keys[c_idx - 1] = left_sib->keys[left_sib->size - 1];
	                left_sib->size--;
	                break; // Underflow resolved
	            } else {
	                // --- BORROW FROM RIGHT SIBLING ---
	                // Pull down parent key into 'w'
	                w->keys[w->size] = p->keys[c_idx];
	                w->children[w->size + 1] = right_sib->children[0]; 
	                if (w->children[w->size + 1]) w->children[w->size + 1]->parent = w;
	                w->size++;
	                
	                // Push sibling's leftmost key up to parent
	                p->keys[c_idx] = right_sib->keys[0];
	                
	                // Shift right sibling's keys/children to the left
	                for (int i = 0; i < right_sib->size - 1; i++) right_sib->keys[i] = right_sib->keys[i + 1];
	                for (int i = 0; i < right_sib->size; i++) right_sib->children[i] = right_sib->children[i + 1];
	                right_sib->size--;
	                break; // Underflow resolved
	            }
	        }
	        else {
	            if (right_sib) {
	                // Merge 'right_sib' into 'w'
	                w->keys[w->size] = p->keys[c_idx];
	                w->size++;
	                
	                for (int i = 0; i < right_sib->size; i++) {
	                    w->keys[w->size + i] = right_sib->keys[i];
	                }
	                for (int i = 0; i <= right_sib->size; i++) {
	                    w->children[w->size + i] = right_sib->children[i];
	                    if (w->children[w->size + i]) {
	                        w->children[w->size + i]->parent = w;
	                    }
	                }
	                w->size += right_sib->size;
	                
	                // Remove the pulled-down key and 'right_sib' pointer from the parent
	                for (int i = c_idx; i < p->size - 1; i++) p->keys[i] = p->keys[i + 1];
	                for (int i = c_idx + 1; i < p->size; i++) p->children[i] = p->children[i + 1];
	                p->size--;
	                
	                delete right_sib;
	                w = p; // Continue the loop to check if parent underflowed
	            }
	            else if (left_sib) {
	                // Merge 'w' into 'left_sib'
	                left_sib->keys[left_sib->size] = p->keys[c_idx - 1];
	                left_sib->children[left_sib->size + 1] = w->children[0];
	                if (left_sib->children[left_sib->size + 1]) {
	                    left_sib->children[left_sib->size + 1]->parent = left_sib;
	                }
	                left_sib->size++;
	                
	                // Remove the pulled-down key and 'w' pointer from the parent
	                for (int i = c_idx - 1; i < p->size - 1; i++) p->keys[i] = p->keys[i + 1];
	                for (int i = c_idx; i < p->size; i++) p->children[i] = p->children[i + 1];
	                p->size--;
	                
	                delete w;
	                w = p; // Continue the loop to check if parent underflowed
	            }
	        }
	    }
	    
	    // Special case: If the root node is completely empty (size == 0)
	    if (root->size == 0) {
	        if (root->children[0]) {
	            node* temp = root;
	            root = root->children[0]; // The child becomes the new root
	            root->parent = nullptr;
	            delete temp;
	        } else {
	            // Tree is completely empty
	            delete root;
	            root = nullptr;
	        }
	    }
	    
	    return true;
	}

    // --- Provided methods ---
    void print_node(string s, node* n) {
        cout << s << ": ";
        for (int i = 0; i < n->size; i++) cout << n->keys[i] << " ";
        cout << endl;
        for (int i = 0; i <= n->size; i++) {
            if (n->children[i]) print_node("Child " + to_string(i + 1) + " of " + s, n->children[i]);
        }
    }

    bool check_parent(node* curr, node* par) {
        if (!curr) return true;
        if (curr->parent != par) return false;
        bool res = true;
        for (int i = 0; i <= curr->size; i++) res &= check_parent(curr->children[i], curr);
        return res;
    }

    void print() {
        if (root) {
            print_node("Root", root);
            check_parent(root, NULL);
        }
    }
};