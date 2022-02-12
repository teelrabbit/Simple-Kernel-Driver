#include <iostream>

using namespace std;

int main()
{
    cout << "\033[0;36n" <<
"                 | |   | /                \n"
"                .'''-------.----.          \n"
"                |          U    |          \n"
"                | ====o======== |          \n"
"                | ============= |          \n"
"                | ________GF337 |          \n"
"                ||   Welcome   ||          \n"
"                ||             ||          \n"
"                ||_____________||          \n"
"                |__.---'''---.__|          \n"
"                |---------------|          \n"
"                |[Yes][(|)][ No]|          \n"
"                | ___  ___  ___ |          \n"
"                |[<-'][CLR][.->]|          \n"
"                | ___  ___  ___ |          \n"
"                |[1__][2__][3__]|          \n"
"                | ___  ___  ___ |          \n"
"                |[4__][5__][6__]|          \n"
"                | ___  ___  ___ |          \n"
"                |[7__][8__][9__]|          \n"
"                | ___  ___  ___ |          \n"
"                |[*__][0__][#__]|          \n"
"                `--------------'           \n"

<< "\033[0;33m" << endl;
    cout<<"[=] Enter a phone number to be converted:: >> " << "\033[0;37m";
    string phone_number; string filtered_number; bool trufalse=false;
    getline(cin, phone_number);
    
    for (int j = 0; j < phone_number.length(); j++) {
        if (isalpha(phone_number[j])) {
            filtered_number += phone_number[j];
            if (j == 7) {trufalse = true;}
        }
        /*else {
            cout  << "\033[0;31m" << "[-] Invalid Input!!!" << endl;
            break;
            return 1;
        } */
    }

    if (filtered_number.length() > 7) {
        cout << "\033[0;31m" <<"[i] invalid number [========|Please Re-Enter|========]" << "\033[0;37m" <<endl;
    }
    
    
    if (trufalse == true) {
        for (int i = 0; i < 7; i++) {
        if (i == 0) {cout << "[+] Corresponding phone number:: ";}
        if (i == 3) {cout << "-";}
        switch (tolower(filtered_number[i])) {
            case 'a':
            case 'b':
            case 'c':
                cout << "2";
                break;
            case 'd':
            case 'e':
            case 'f':
                cout << "3";
                break;
            case 'g':
            case 'h':
            case 'i':
                cout << "4";
                break;
            case 'j':
            case 'k':
            case 'l':
                cout << "5";
                break;
            case 'm':
            case 'n':
            case 'o':
                cout << "6";
                break;
            case 'p':
            case 'q':
            case 'r':
            case 's':
                cout << "7";
                break;
            case 't':
            case 'u':
            case 'v':
                cout << "8";
                break;
            case 'w':
            case 'x':
            case 'y':
            case 'z':
                cout << "9";
                break;
        }
    }
    }
    
    
    
    return 0;
}
