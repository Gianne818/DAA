#include <iostream>
#include <string>

using namespace std;

// Performs a 5-bit cyclic shift to the left [cite: 161]
int getCyclicShiftHashCode(string key) {
    unsigned int h = 0;
    for (int i = 0; i < key.length(); i++) {
        // Shift h left by 5 bits and move the overflow to the right [cite: 161]
        h = (h << 5) | (h >> 27); 
        h += (unsigned int)key[i]; // Add the new character to the partial sum [cite: 160]
    }
    return (int)h;
}


int main() {
    string words[2] = {"obedient", "joyous"}; // Example words [cite: 131, 132]
    
    for (int i = 0; i < 2; i++) {
        cout << "Key: " << words[i] << " | Hash: " << getCyclicShiftHashCode(words[i]) << endl;
    }
    return 0;
}