#include <iostream>
using namespace std;

int findMaxRecur(int* arr, int s, int curMax, int curInd){
    if(curInd == s) return curMax;
    if(arr[curInd]>curMax) curMax = arr[curInd];
    return findMaxRecur(arr, s, curMax, curInd+1);
}

void helper(int* arr, int s, int max, int* countArr, int curIndArr, int curIndCountArr){
    if(curIndArr == s) return;
    if(curIndCountArr == max+1) return;

    if(countArr[curIndCountArr] > 0){
        arr[curIndArr] = curIndCountArr;
        countArr[curIndCountArr]--;
        curIndArr++;
    } else {
        curIndCountArr++;
    }

    helper(arr, s, max, countArr, curIndArr, curIndCountArr);
}

void countingSortRecur(int* arr, int s){
    int max = findMaxRecur(arr, s, arr[0], 0);

    int* countArr = new int[max+1]{0};
    for(int i = 0; i<s; i++){
        countArr[arr[i]]++;
    }

    helper(arr, s, max, countArr, 0, 0);
}


int main(){
    int s;
    cout << "Enter the size of the array: ";
    cin >> s;

    int* arr = new int[s];
    cout << "Enter array values:" << endl;

    for(int i = 0; i<s; i++){
        cin >> arr[i];
    }

    countingSortRecur(arr, s);
    cout << "Final result:\n";
    for(int i = 0; i<s; i++){
        cout << arr[i] << " ";
    }

}