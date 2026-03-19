#include <iostream>
using namespace std;

void helper(int n, char from, char to, char aux){
    if(n==1){
        cout << "Moving disk " << n << " from " << from << " to " << to << endl; 
        return;
    }
    helper(n-1, from, aux, to);
    cout << "Moving disk " << n << " from " << from << " to " << to << endl;
    helper(n-1, aux, to, from);

}

void hanoi(int n){
    helper(n, 'A', 'C', 'B');
}

int main(){
    int n;
    cout << "Enter number of disks: ";
    cin >> n;

    hanoi(n);
}