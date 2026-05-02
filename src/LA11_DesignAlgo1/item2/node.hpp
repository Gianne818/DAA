#include <iostream>
#include <string>
using namespace std;

struct node {
	char ch;
	int weight;
	node *left, *right, *parent;

	node(char c, int w) : ch(c), weight(w), left(nullptr), right(nullptr), parent(nullptr) {};
    

    
	// TODO getCode
	string getCode() {
	   string code = "";
	   node* curr = this;
	   while(curr->parent){
	       node* p = curr->parent;
	       if(p->left == curr) code = "0" + code;
	       else code = "1" + code;
	       curr = p;
	   }
	    return code;
	}
};