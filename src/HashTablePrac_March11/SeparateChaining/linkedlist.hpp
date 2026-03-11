#include <iostream>
using namespace std;

struct node {
    string elem;
    node* next;
};

class LinkedList {

public:

    int size;
    node* head, *tail;
    int index;

    LinkedList(){
        size = 0;
        head = nullptr;
        tail = nullptr;
        index = 0;
    }

    void add_last (string key){
        node* n = new node();
        n->elem = key;
        n->next = nullptr;

        if(tail){
            tail->next = n;
        } else {
            head = n;
        }
        tail = n;
        size++;
    }

    bool find_node(string key){
        node* temp = head;
        while(temp){
            if(temp->elem == key){
                return true;
            }
            temp = temp->next;
        }
        return false;
    }

    bool remove_node(string key){
        node* temp = head;
        node* prev = nullptr;
        while(temp){
            if(temp->elem == key){
                if(temp == head){
                    if(head == tail){
                        head = tail = nullptr;
                    } else {
                        head = head->next;
                    }
                } else if(temp == tail){
                    tail = prev;
                    tail->next = nullptr;
                }
                else {
                    prev->next = temp->next;
                }
                delete temp;
                size--;
                return true;
            } 
            prev = temp;
            temp = temp->next;
        }
        return false;
    }

    int size_() {
        return size;
    }

    void print(){
        if(!head){
            cout << "(empty)"; 
        } else {
            node* curr = head;
            while(curr){
                cout << curr->elem;
                if(curr != tail){
                    cout << " -> ";
                }
                curr = curr->next;
            }
        }
    }
};