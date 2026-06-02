#include <iostream>
#include <string>

using namespace std;

char letters[26] = {
    'A','B','C','D','E','F','G',
    'H','I','J','K','L','M',
    'N','O','P','Q','R','S',
    'T','U','V','W','X','Y','Z'
};

int getIndex(char ch) {
    ch = toupper(ch); 
    for (int i = 0; i < 26; i++) {
        if (letters[i] == ch) {
            return i; 
        }
    }
    return -1; 
}

string encrypt(string text, int a, int b) {
    char* ptr = &text[0]; 
    while (*ptr != '\0') {
        
        if (isalpha(*ptr)) {
            
            *ptr = toupper(*ptr);
            
            int x = getIndex(*ptr);
            
            int y = (a * x + b) % 26;

            *ptr = letters[y];
        }

        ptr++;

    }

    return text;
}

string decrypt(string text, int a, int b) {
    int aInverse = 1;

    for (int i = 0; i < 26; i++) {
        if ((a * i) % 26 == 1) {
            aInverse = i;
        }
    }

    char* ptr = &text[0]; 

    while (*ptr != '\0') {
        
        if (isalpha(*ptr)) {

            *ptr = toupper(*ptr);

            int y = getIndex(*ptr);

            int x = (aInverse * (y - b)) % 26;

            if (x < 0) {
                x += 26;
            }

            *ptr = letters[x];
        }

        ptr++;
    }

    return text;
}

int main() {
    int a, b, choice;
    string text;

    cout << "Enter keys a and b: ";
    cin >> a >> b;

    if (a % 2 == 0 || a % 13 == 0) {
        cout << "Invalid value for a!" << endl;
        return 0;
    }

    cout << "Choose mode:\n";
    cout << "1. Encrypt\n";
    cout << "2. Decrypt\n";
    cout << "Enter choice: ";
    cin >> choice;

    cin.ignore();
    
    cout << "Enter text: ";
    getline(cin, text);

    string result;

   if (choice == 1) {
        result = encrypt(text, a, b);
        cout << "\nEncrypted text: " << result << endl;
    }
    else if (choice == 2) {
        result = decrypt(text, a, b);
        cout << "\nDecrypted text: " << result << endl;
    }
    else {
        cout << "Invalid choice!" << endl;
        return 0;
    }

    return 0;
}
