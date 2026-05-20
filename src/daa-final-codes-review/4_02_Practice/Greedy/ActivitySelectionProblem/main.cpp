#include <iostream>
#include "activitylist.hpp"
using namespace std;

int main(void) {
    char op;
    int id, start, finish;
    Activity** selected;
    int num_selected;

    ActivitySelector* selector = new ActivityList();
    
    do {
        cout << "Operation: ";
        cin >> op;
        switch (op) {
            case 'a': // add activity
                cin >> id >> start >> finish;
                cout << selector->insertActivity(id, start, finish) << endl;
                break;
            case 'r': // remove activity
                cin >> id;
                cout << selector->removeActivity(id) << endl;
                break;
            case 'c': // count activities
                cout << selector->numActivities() << endl;
                break;
            case 'g': // greedy activity selection
                selected = selector->greedyActivitySelector();
                if(selected == nullptr) {
                    cout << "No activities to select" << endl;
                } else {
                    num_selected = 0;
                    while(selected[num_selected] != nullptr && num_selected < selector->numActivities()) {
                        num_selected++;
                    }
                    cout << "Selected Activities (" << num_selected << "):" << endl;
                    for(int i = 0; i < num_selected; i++) {
                        selected[i]->toString();
                        cout << endl;
                    }
                    free(selected);
                }
                break;
            case 'p': // print all activities
                selector->print();
                break;
            case 'x':
                cout << "Exiting...";
                break;
            default:
                cout << "Invalid operation";
        }
    } while (op != 'x');

    return 0;
}