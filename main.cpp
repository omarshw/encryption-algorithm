#include <iostream>
#include <string>
#include <cctype>

using namespace std;

const int c = 26; 

int gcd(int a, int b) {
    if (b == 0) return a;
    return gcd(b, a % b);
}

int modInverse(int a, int m) {
    for (int x = 1; x < m; x++) {
        if (((a % m) * (x % m)) % m == 1) {
            return x;
        }
    }
    return -1;
}

int encryptFunction(int x, int a, int b) {
    return ((a * x) + b) % c;
}

int decryptFunction(int y, int a, int b) {
    int a_inv = modInverse(a, c);
    int res = (a_inv * (y - b)) % c;
    
    if (res < 0) {
        res += c;
    }
    return res;
}

int main() {
    int a, b;
    string text;

    cout << "Enter values for 'a' and 'b': ";
    if (!(cin >> a >> b)) {
        cout << "Invalid input!" << endl;
        return 1;
    }

    if (gcd(a, c) != 1) {
        cout << "Error: The value 'a' (" << a << ") and 'c' (26) must be coprime!" << endl;
        cout << "Cannot encrypt or decrypt. Please choose another 'a'." << endl;
        return 0;
    }

    cout << "Enter text to encrypt: ";
    cin.ignore();
    getline(cin, text);

    string encrypted = "";
    for (char& ch : text) {
        if (isalpha(ch)) {
            bool isUpper = isupper(ch);
            int x = tolower(ch) - 'a';
            int encrypted_x = encryptFunction(x, a, b);
            encrypted += (isUpper ? 'A' : 'a') + encrypted_x;
        } else {
            encrypted += ch;
        }
    }

    cout << "\nEncrypted text: " << encrypted << endl;

    string decrypted = "";
    for (char& ch : encrypted) {
        if (isalpha(ch)) {
            bool isUpper = isupper(ch);
            int y = tolower(ch) - 'a';
            int decrypted_y = decryptFunction(y, a, b);
            decrypted += (isUpper ? 'A' : 'a') + decrypted_y;
        } else {
            decrypted += ch;
        }
    }

    cout << "Decrypted text: " << decrypted << endl;

    return 0;
}
