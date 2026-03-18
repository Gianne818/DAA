#include <iostream>
using namespace std;

int towerOfHanoi(int n, char from, char to, char aux){
    if(n==0){
        return 0;
    }

    int moves = towerOfHanoi(n-1, from, to, aux);
    cout << "Moving disk " << n << " from " << from << " to " << to << " using " << aux << endl; 
    moves++;
    moves += towerOfHanoi(n-1, aux, to, from);
    
    return moves;
}

int main(){
    int n;
    cout << "Enter number of disks: ";
    cin >> n;

    int res = towerOfHanoi(n, 'A', 'B', 'C');
    cout << "The number of moves is: " << res << endl; 
}