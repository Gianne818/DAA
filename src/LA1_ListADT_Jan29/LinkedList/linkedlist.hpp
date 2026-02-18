// TODO entire implementation and add more header file/s as needed
#include <iostream>
#include <stdexcept>
#include "list.hpp"
using namespace std;

struct node{
    int elem;
    node* next;
    node* prev;
    
    node(int elem, node* prev, node* next){
        this->elem = elem;
        this->prev = prev;
        this->next = next;
    }
    
    node(){
        this->prev = nullptr;
        this->next = nullptr;
    }
    
};

class LinkedList : public List{
private:
    int s;
    node head;
    node tail;
    
    node* addBetween(int num, node* pred, node* succ){
        node* n = new node(num, pred, succ);
        pred->next = n;
        succ->prev = n;
        s++;
        return n;
    }
    
    int removeNode(node* n){
        int temp = n->elem;
        
        n->prev->next = n->next;
        n->next->prev = n->prev;
        
        free(n);
        s--;
        return temp;
    }
    
public:
    LinkedList(){
        s = 0;
        head.next = &tail;
        tail.prev = &head;
        
        head.prev = nullptr;
        tail.next = nullptr;
    }
    
    void insert(int num){
        addBetween(num, tail.prev, &tail);
    }
    
    int get(int pos){
        if(pos > s || pos < 1) throw invalid_argument("Invalid position");
        node* temp = head.next;
        for(int i = 0; i<pos-1; i++){
            temp = temp->next;
        }
        return temp->elem;
    }
    
    int remove(int num){
        node* temp = head.next;
        int ctr = 1;
        while(temp){
            if(temp->elem == num){
                removeNode(temp);
                return ctr;
            }
            temp = temp->next;
            ctr++;
        }
        return 0;
    }
    
    void print(){
        
        cout << "FROM HEAD: ";
        if(isEmpty()){
            cout << "(none)";
        } else {
            node* tempHead = head.next;
            do {
                cout << tempHead->elem << " ";
                if(tempHead!= tail.prev) cout << "-> ";
                tempHead = tempHead->next;
                
            } while (tempHead!=&tail);
        }
        
        cout << endl << "FROM TAIL: ";
        if(isEmpty()){
            cout << "(none)";
        } else {
            node* tempTail = tail.prev;
            do{
                cout << tempTail->elem << " ";
                if(tempTail!=head.next) cout << "<- ";
                tempTail = tempTail->prev;
            } while(tempTail!=&head);
        }
        
        
        cout << endl;
    }
    
    int size(){
        return s;
    }
    
    bool isEmpty(){
        return s==0;
    }
    
    void addAt(int num, int pos){
        if(pos > s+1 || pos < 1) throw invalid_argument("Invalid position");
        node* temp = head.next;
        for(int i = 0; i<pos-1; i++){
            temp = temp->next;
        }
        
        addBetween(num, temp->prev, temp);
    }
    
    int removeAt(int pos){
        if(pos > s || pos < 1) throw invalid_argument("Invalid position");
        node* temp = head.next;
        for(int i = 0; i<pos-1; i++){
            temp = temp->next;
        }
        return removeNode(temp);
    }
};