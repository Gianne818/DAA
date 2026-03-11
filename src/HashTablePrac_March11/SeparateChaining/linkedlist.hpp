#include <iostream>
using namespace std;

struct node {
    int elem;
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

    void add (int num){
        node* n = new node();
        n->elem = num;
        n->next = nullptr;

        if(tail){
            tail->next = n;
        } else {
            head = n;
        }
        tail = n;
        size++;
    }


    void addHead(int num){
        node* n = new node();
        n->elem = num;

        if(!head){
            head = tail = n;
            size++;
            return;
        }

        node* temp = head;
        head = n;
        n->next = temp;
        head = n;
        size++;
    }

    void addTail(int num){
        node* n = new node();
        n->elem = num;
        n->next = nullptr;

        if(tail){
            tail->next = n;
        } else {
            head = n;
        }
        tail = n;
        size++;
    }

    int get(int num){
        node* temp = head;
        int pos = 1;
        while(temp){
            if(temp->elem == num){
                return pos;
            }
            pos++;
            temp = temp->next;
        }
        return -1;
    }

    int remove(int num){
        node* temp = head;
        node* prev;
        int pos = 1;
        while(temp){
            if(temp->elem==num){
                if(temp==head){
                    if(head==tail){
                        head=tail=nullptr;
                    } else {
                        head = head->next;
                    }
                } else if(temp==tail){
                    tail = prev;
                    tail->next = nullptr;
                }
                else {
                    prev->next = temp->next;
                }
                free(temp);
                size--;
                return pos;
            } 
            pos++;
            prev = temp;
            temp = temp->next;
        }
        return -1;
    }

    int removeAt(int pos){
        return 0;
    }

    int removeAll(int num){
        node* temp = head;
        node* prev;
        int count = 0;
        while(temp){
            if(temp->elem == num){
                node* deleteNode = temp;
                if(temp==head){
                    if(head==tail){
                        head = tail = nullptr;
                    } else {
                        head = head->next;
                    }
                } else if(temp==tail){  
                    tail = prev;
                    tail->next = nullptr;
                } else {
                    prev->next = temp->next;
                }
                temp = temp->next;
                free(deleteNode);
                size--;
                count++;
            } else {
                prev = temp;
                temp = temp->next;
            }
            
            
        }
        cout << "Current size: " << size << endl;
        return count;
    }

    void flip(){
        node* curr = head;
        node* prev = nullptr;
        node* next = nullptr;
        while(curr){
            next = curr->next;
            curr->next = prev;
            prev = curr;
            curr = next;
        }
        head = prev;
    }

    void print(){
        cout << endl;
        if(!head){
            cout << "Empty." << endl; 
        } else {
            node* curr = head;
            do {
                cout << curr->elem;
                if(curr!=tail){
                    cout << " -> ";
                } else {
                    cout << endl;
                }
                curr = curr->next;
            } while(curr);
        }
        cout << endl;
    }
};