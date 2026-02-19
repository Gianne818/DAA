#include <iostream>
#include "arraylist.hpp"
#include "linkedlist.hpp"
using namespace std;

void bubbleSort(List* list);
void selectionSort(List* list);
void insertionSort(List* list);

int main(){
    int s;
    cout << "Enter the number of elements: ";
    cin >> s;
    
    char choice;
    cout << "Enter A for arraylist, L for linkedlist: ";
    cin >> choice;
    
    List* list = nullptr;
    switch(choice){
        case 'A':
            list = new ArrayList();
            break;
        case 'L':
            list = new LinkedList();
            break;
        default:
            cout << "Error choice. Exiting...";
            return 0;
    }
    cout << "Enter the elements of the array: ";

    int temp;
    for(int i = 0; i<s; i++){
        cin >> temp;
        list->add(temp);
    }

    cout << "Enter sorting choice (B - bubble, S - selection, I - insertion): ";
    char sortChoice;
    cin >> sortChoice;

    switch(sortChoice){
        case 'B':
            bubbleSort(list);
            break;
        case 'S':
            selectionSort(list);
            break;
        case 'I':
            insertionSort(list);
            break;
        default:
            cout << "Error choice. Exiting...";
            return 0;
    }

    cout << "Final result: ";
    list->print();
}

void bubbleSort(List* list){
    int s = list->size();
    for(int i = 0; i<s-1; i++){
        for(int j = 0; j<s-i-1; j++){
            if(list->get(j) > list->get(j+1)){
                list->swap(j, j+1);
                list->print();
            }
        }
    }
}

void selectionSort(List* list){
    int s = list->size();
    for(int i = 0; i<s-1; i++){
        int smallest = i;
        for(int j = i+1; j<s; j++){
            if(list->get(j) < list->get(smallest)){
                smallest = j;
            }
        }
        if(i!=smallest){
            list->swap(i, smallest);
            list->print();
        }
    }
}

void insertionSort(List* list){
    int s = list->size();
    for(int i = 1; i<s; i++){
        int j = i;
        while(j>=0 && list->get(j-1) > list->get(j)){
            list->swap(j, j-1);
            list->print();
            j--;
        }
    }
}