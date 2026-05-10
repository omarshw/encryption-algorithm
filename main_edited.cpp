#include <iostream>
#include <string>
#include <cctype>
#include <numeric> // Added for gcd

using namespace std;

const int ALPHABET_SIZE = 26; // Renamed for better readability

// Safe modulo function to handle negative numbers in C++
int safeMod(int val, int m) {
    return (val % m + m) % m;
}

// Kept the simple brute-force approach because it's easier to understand!
int modInverse(int a, int m) {
    for (int x = 1; x < m; x++) {
        if (((a % m) * (x % m)) % m == 1) {
            return x;
        }
    }
    return -1;
}

int encryptFunction(int x, int a, int b) {
    return safeMod((a * x) + b, ALPHABET_SIZE);
}

int decryptFunction(int y, int a, int b) {
    int a_inv = modInverse(a, ALPHABET_SIZE);
    return safeMod(a_inv * (y - b), ALPHABET_SIZE);
}

// Extracted string encryption into its own function
string encryptText(const string& text, int a, int b) {
    string result = "";
    for (char ch : text) {
        if (isalpha(ch)) {
            bool isUpper = isupper(ch);
            int x = tolower(ch) - 'a';
            int encrypted_x = encryptFunction(x, a, b);
            result += (isUpper ? 'A' : 'a') + encrypted_x;
        } else {
            result += ch;
        }
    }
    return result;
}

// Extracted string decryption into its own function
string decryptText(const string& text, int a, int b) {
    string result = "";
    for (char ch : text) {
        if (isalpha(ch)) {
            bool isUpper = isupper(ch);
            int y = tolower(ch) - 'a';
            int decrypted_y = decryptFunction(y, a, b);
            result += (isUpper ? 'A' : 'a') + decrypted_y;
        } else {
            result += ch;
        }
    }
    return result;
}

int main() {
    int a, b;
    string text;

    cout << "Enter values for 'a' and 'b': ";
    if (!(cin >> a >> b)) {
        cout << "Invalid input!" << endl;
        return 1;
    }

    // Using the built-in gcd from <numeric>
    if (gcd(a, ALPHABET_SIZE) != 1) {
        cout << "Error: The value 'a' (" << a << ") and 'ALPHABET_SIZE' (26) must be coprime!" << endl;
        cout << "Cannot encrypt or decrypt. Please choose another 'a'." << endl;
        return 0;
    }

    cout << "Enter text to encrypt: ";
    cin.ignore();
    getline(cin, text);

    string encrypted = encryptText(text, a, b);
    cout << "\nEncrypted text: " << encrypted << endl;

    string decrypted = decryptText(encrypted, a, b);
    cout << "Decrypted text: " << decrypted << endl;

    return 0;
}
