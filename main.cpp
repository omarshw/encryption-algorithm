#include <iostream>
#include <string>

using namespace std;

// Alphabet array
char letters[26] = {
    'A','B','C','D','E','F','G',
    'H','I','J','K','L','M',
    'N','O','P','Q','R','S',
    'T','U','V','W','X','Y','Z'
};

// Get index of letter
int getIndex(char ch) {
    ch = toupper(ch);
    for (int i = 0; i < 26; i++) {
        if (letters[i] == ch) {
            return i;
        }
    }

    return -1;
}

// Encrypt function
string encrypt(string text, int a, int b) {
    for (int i = 0; i < text.length(); i++) {
        if (isalpha(text[i])) {
            // Convert everything to uppercase
            text[i] = toupper(text[i]);

            // Get letter index
            int x = getIndex(text[i]);
            // Affine formula
            int y = (a * x + b) % 26;
            // Replace using array
            text[i] = letters[y];
        }
    }

    return text;
}

// Decrypt function
string decrypt(string text, int a, int b) {
    int aInverse = 1;

    // Find inverse of a
    for (int i = 0; i < 26; i++) {
        if ((a * i) % 26 == 1) {
            aInverse = i;
        }
    }

    for (int i = 0; i < text.length(); i++) {
        if (isalpha(text[i])) {
            // Convert everything to uppercase
            text[i] = toupper(text[i]);

            // Get encrypted letter index
            int y = getIndex(text[i]);

            // Decryption formula
            int x = (aInverse * (y - b)) % 26;

            // Fix negative values
            if (x < 0) {
                x += 26;
            }

            // Replace using array
            text[i] = letters[x];
        }
    }

    return text;
}

// Pointer function
void showCharacters(char* ptr) {
    while (*ptr != '\0') {
        cout << *ptr << " ";
        ptr++;
    }

    cout << endl;
}

int main() {
    int a, b;
    string text;

    cout << "Enter keys a and b: ";
    cin >> a >> b;

    // Invalid values for a
    if (a % 2 == 0 || a % 13 == 0) {
        cout << "Invalid value for a!" << endl;
        return 0;
    }

    cin.ignore();

    cout << "Enter text: ";
    getline(cin, text);

    // Encrypt
    string encrypted = encrypt(text, a, b);

    cout << "\nEncrypted text: " << encrypted << endl;

    // Pointer demo
    cout << "\nCharacters using pointer:\n";

    showCharacters(&encrypted[0]);

    // Decrypt
    string decrypted = decrypt(encrypted, a, b);

    cout << "\nDecrypted text: " << decrypted << endl;

    return 0;
}
