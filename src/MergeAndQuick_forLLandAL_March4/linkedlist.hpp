#include "list.hpp"
using namespace std;

struct node{
    int elem;
    node* next;
};

class LinkedList : public List {
    node* head;
    node* tail;
    int index;

    node* create_node(int num){
        node* newNode = new node();
        newNode->elem = num;
        newNode->next = nullptr;
        return newNode;
    }

    public:
    LinkedList(){
        head = tail = nullptr;
        index = 0;
    }

    int add(int num){
        node* newNode = create_node(num);
        if(!head){
            head = tail = newNode;
        } else {
            tail->next = newNode;
            tail = newNode;
        }
        index++;
        return index;
    }

    int get(int pos){
        if(pos>=index || pos < 0) return -1;
        node* temp = head;
        for(int i = 0; i<pos; i++){
            temp = temp->next;
        }
        return temp->elem;
    }

    int size(){
        return index;
    }

    void swap(int pos1, int pos2){
        node* temp1 = head, *temp2 = head, *prev1 = nullptr, *prev2 = nullptr;

        for(int i = 0; i<pos1; i++){
            prev1 = temp1;
            temp1 = temp1->next;
        }

        for(int i = 0; i<pos2; i++){
            prev2 = temp2;
            temp2 = temp2->next;
        }

        if(prev1) prev1->next = temp2;
        else head = temp2;

        if(prev2) prev2->next = temp1;
        else head = temp1;

        node* toSwap = temp1->next;
        temp1->next = temp2->next;
        temp2->next = toSwap;

        if(!temp1->next) tail = temp1;
        if(!temp2->next) tail = temp2;
    }

    void print(){
        if(!head){
            cout << "EMPTY" << endl;
        }

        node* temp = head;
        while(temp){
            cout << temp->elem << " ";
            temp = temp->next;
        }
        cout << endl;
    }
};