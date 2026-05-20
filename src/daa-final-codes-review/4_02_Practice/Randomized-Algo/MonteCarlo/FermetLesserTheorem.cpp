#include <bits/stdc++.h>
using namespace std;

/*
Randomized Algorithm 

Large Prime Number Optimized using
Fermet's Lesser Theorem

Carmichael numbers - Composite numbers that pass Fermat's test (a^(n-1) ≡ 1 mod n) for all a coprime to n. Smallest: 561.


*/

long long powerMod(long long a, long long d, long long n) {
    long long result = 1;
    a = a % n;
    while (d > 0) {
        if (d & 1)
            result = (result * a) % n;
        a = (a * a) % n;
        d >>= 1;
    }
    return result;
}

bool isPrimeFermat(long long n, int k = 5) {
    if (n <= 1) return false;
    if (n <= 3) return true;
    if (n % 2 == 0) return false;
    
    // Randomly pick A between 2 and n-2
    for (int i = 0; i < k; i++) {
        long long a = 2 + rand() % (n - 3);
        if (powerMod(a, n - 1, n) != 1)
            return false;
    }
    return true;
}

int main() {
    srand(time(0));
    
    long long num;
    cout << "Enter a large number: ";
    cin >> num;
    
    if (isPrimeFermat(num))
        cout << num << " is PROBABLY prime (Monte Carlo)\n";
    else
        cout << num << " is composite\n";
    
    return 0;
}

/*
TIME: 
SPACE: O(1)

Note: Carmichael numbers (e.g., 561) pass Fermat test but are composite - use Miller-Rabin for better accuracy.
   - Composite numbers that pass Fermat's test (a^(n-1) ≡ 1 mod n) for all a coprime to n. Smallest: 561.


*/