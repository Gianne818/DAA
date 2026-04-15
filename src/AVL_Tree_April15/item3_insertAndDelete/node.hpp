#include <algorithm>
 
using namespace std;
 
struct node {
    node* parent;
    node* right;
    node* left;
    int elem;
 
    // TODO paste your height method here
    int height() {
        int lh = (left == NULL) ? -1 : left->height();
        int rh = (right == NULL) ? -1 : right->height();
        return 1 + max(lh, rh);
    }
    int getBalance(){
        int lh = (left == NULL) ? -1 : left->height();
        int rh = (right == NULL) ? -1 : right->height();
        return lh - rh;
    }
};