#include <iostream>
#include <string>

using namespace std;

// ده الألفابيت اللي بنستخدمه في التشفير (A-Z)
char letters[26] = {
    'A','B','C','D','E','F','G',
    'H','I','J','K','L','M',
    'N','O','P','Q','R','S',
    'T','U','V','W','X','Y','Z'
};

// دالة بتجيب رقم الحرف في الألفابيت (A = 0, B = 1 ... Z = 25)
// لو الحرف مش موجود بترجع -1
// Get index of letter (Omar)
int getIndex(char ch) {
    ch = toupper(ch); // نحول الحرف لكابيتال عشان نوحد التعامل
    for (int i = 0; i < 26; i++) {
        if (letters[i] == ch) {
            return i; // لقينا مكان الحرف
        }
    }
    return -1; // مش موجود
}

// دالة التشفير (Aymoun & Morcos)
// هنا بنطبق معادلة Affine Cipher: (a*x + b) mod 26
// الفكرة إننا بنمشي على النص باستخدام pointer ونعدل الحروف مباشرة في الذاكرة
string encrypt(string text, int a, int b) {
    char* ptr = &text[0]; // pointer بيبدأ من أول حرف في النص
    while (*ptr != '\0') {
        // بنلف على النص حرف حرف لحد ما نوصل لنهاية string
        
        if (isalpha(*ptr)) {
            // بنشتغل بس لو الحرف ده حرف (مش رقم أو مسافة)
            
            *ptr = toupper(*ptr);
            // بنحوّل الحرف لكابيتال عشان التشفير يبقى موحد
            
            int x = getIndex(*ptr);
            // بنجيب رقم الحرف في الألفابيت (A=0, B=1 ...)
            
            int y = (a * x + b) % 26;
            // دي معادلة التشفير الأساسية:
            // بنضرب في a ونضيف b وبناخد mod 26 عشان نلف داخل 26 حرف

            *ptr = letters[y];
            // بنستبدل الحرف الأصلي بالحرف المشفر من array letters
        }

        ptr++;
        // بنحرك الـ pointer للحرف اللي بعده في النص
    }

    return text;
}

// دالة فك التشفير (Omar & Adham & Hossam)
// هنا بنعكس معادلة Affine Cipher باستخدام pointer بدل الـ indexing
// الفكرة إننا بنمشي على النص في الذاكرة ونعدل الحروف مباشرة
string decrypt(string text, int a, int b) {
    int aInverse = 1;

    // بندور على الـ modular inverse بتاع a
    // يعني رقم لو ضربناه في a يدي 1 mod 26
    for (int i = 0; i < 26; i++) {
        if ((a * i) % 26 == 1) {
            aInverse = i;
        }
    }

    char* ptr = &text[0]; 
    // pointer بيبدأ من أول حرف في النص

    while (*ptr != '\0') {
        // بنمشي على النص حرف حرف لحد ما نوصل لنهاية string

        if (isalpha(*ptr)) {

            // بنحوّل الحرف لكابيتال عشان نبقى موحدين
            *ptr = toupper(*ptr);

            // بنجيب رقم الحرف المشفر
            int y = getIndex(*ptr);

            // معادلة فك التشفير:
            // x = aInverse * (y - b) mod 26
            int x = (aInverse * (y - b)) % 26;

            // لو الناتج طلع سالب بنعدله عشان يفضل داخل 0-25
            if (x < 0) {
                x += 26;
            }

            // بنرجّع الحرف الأصلي باستخدام الـ array
            *ptr = letters[x];
        }

        ptr++;
        // بنحرك الـ pointer للحرف اللي بعده
    }

    return text;
}

int main() {
    int a, b, choice;
    string text;

    cout << "Enter keys a and b: ";
    cin >> a >> b;

    // شرط مهم: a لازم يكون مناسب في Affine Cipher
    if (a % 2 == 0 || a % 13 == 0) {
        cout << "Invalid value for a!" << endl;
        return 0;
    }

    // اختيار المستخدم بين التشفير وفك التشفير
    cout << "Choose mode:\n";
    cout << "1. Encrypt\n";
    cout << "2. Decrypt\n";
    cout << "Enter choice: ";
    cin >> choice;

    cin.ignore(); // عشان نشيل enter

    cout << "Enter text: ";
    getline(cin, text);

    string result;

    // تشغيل الوظيفة حسب اختيار المستخدم
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
