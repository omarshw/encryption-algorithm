#include <iostream>
#include <string>

using namespace std;

// Function that takes a pointer (char*) to modify the text directly
void encrypt(char* ptr, int a, int b) {
    // Keep going until the pointer hits the end of the string ('\0')
    while (*ptr != '\0') {
        if (*ptr >= 'A' && *ptr <= 'Z') {
            *ptr = ((a * (*ptr - 'A') + b) % 26) + 'A'; // uppercase math
        } 
        else if (*ptr >= 'a' && *ptr <= 'z') {
            *ptr = ((a * (*ptr - 'a') + b) % 26) + 'a'; // lowercase math
        }
        ptr++; // Move pointer to the next character
    }
}

int main() {
    int a, b;
    string text;

    cout << "Enter keys 'a' and 'b': ";
    cin >> a >> b;

    // 'a' cannot share factors with 26 (cannot be even or a multiple of 13)
    if (a % 2 == 0 || a % 13 == 0) {
        cout << "Invalid 'a' key!\n";
        return 0; 
    }

    cout << "Enter text: ";
    cin.ignore();
    getline(cin, text);

    // Call the function and pass the pointer to the start of the text string
    if (!text.empty()) {
        encrypt(&text[0], a, b);
    }

    cout << "Encrypted: " << text << endl;

    return 0;
}
