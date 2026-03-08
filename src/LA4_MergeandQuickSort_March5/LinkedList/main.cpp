#include <iostream>
#include "linkedlist.hpp"
using namespace std;

LinkedList* mergeSort(LinkedList* list);

int main(){
    int s;
    cout << "Enter the number of elements: ";
    cin >> s;

    cout << "Enter the value for each element:\n";
    LinkedList* list = new LinkedList();

    for(int i = 0; i<s; i++){
        int n;
        cin >> n;
        list->add(n);
    }

    mergeSort(list);

    cout << "Final result: ";
    list->print();

}


LinkedList* mergeSort(LinkedList* list){
    list->print();
    if(list->size<=1){
        return list;
    }

    //Step 1 - Divide
    LinkedList* firsthalf = new LinkedList();
    LinkedList* secondhalf = new LinkedList();

    int s = list->size;
    

    firsthalf->head = list->head;
    node* firstTemp = firsthalf->head;
    node* temp = list->head;
    int i;
    for(i = 0; i<s/2-1; i++){
        temp = temp->next;
    }

    firsthalf->tail = temp;

    secondhalf->head = temp;

    for(; i<s; i++){
        temp = temp->next;
    }
    secondhalf->tail = temp;
    if(secondhalf->tail) secondhalf->tail->next = nullptr;
    // secondTemp->next = nullptr;


    // Given: Step 2 - Recursive call
    cout << "My first half: ";
    firsthalf->print();
    // firsthalf = mergeSort(firsthalf);
    cout << "My second half: ";
    secondhalf->print();
    // secondhalf = mergeSort(secondhalf);

    //Step 3 - Combine
    LinkedList* sorted = new LinkedList();

    sorted->print();
    return firsthalf;

}

