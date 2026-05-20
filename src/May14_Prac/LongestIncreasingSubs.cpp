#include <iostream>
#include <set>
using namespace std;

int main (){
    cout << "Enter size: ";
    int s;
    cin >> s;


    int arr[s];

    int dp[s];

    cout << "Enter values: ";
    for(int i = 0; i<s; i++){
        cin >> arr[i];
        dp[i] = 1;
    }

    for(int i = 0; i<s; i++){
        for(int j = 0; j<i; j++){
            if(arr[j] < arr[i]){
                if(dp[j] <= dp[i]){
                    if(dp[j]+1 >  dp[i]){
                        dp[i]++;
                    }
                }
            }
        }
    }

    cout << "The sequence: ";
    int curFound = 9999;
    stack<int> myStack;

    for(int i = s-1; i>0; i--){
        if(i == s-1){
            myStack.push(arr[i]);
            curFound = dp[i];
            continue;
        }
        // cout << "dp[i]: " << dp[i] << ", curFound: " << curFound << endl;
        if(dp[i] - curFound == -1){
            myStack.push(arr[i]);
            curFound = dp[i];
        }
    }
    
    for(int i = 0; i<myStack.size(); i++){
        int res = myStack.top();
        myStack.pop();

        cout << res << " ";
    }

    cout << endl << endl;
}