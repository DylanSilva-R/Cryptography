/*
* This program can be used to find modular inverse as well.
*
*/
#include <stdio.h>
#include "Proper_Mod.h"

struct values
{
    int t2;
    int s2;
    int gcd;
};

struct values EEA(int a, int b, int s1, int s2, int t1, int t2)
{
    int remainder = pMod(a, b);
    int quotient = a / b;

    int t3 = t1 - (t2 * quotient);
    int s3 = s1 - (s2 * quotient);

    if(remainder == 0)
    {
        cout << a << " = " << b << "*" << quotient << " + " << remainder << " | s1 = " << s1 << " | s2 = " << s2 << " | s3 = X | t1 = " << t1 << " | t2 = " << t2 << " | t3 = X" << endl;
        cout << endl;

        struct values value;

        value.s2 = s2;
        value.t2 = t2;
        value.gcd = b;

        return value;
    }else
    {

        //cout << "New T value = " << t1 << " - (" << t2 << "*" << quotient << ")" <<endl;// t1 - (t2 * quotient)
        //cout << "New S value = " <<s1 << " - (" << s2 << "*" << quotient << ")" <<endl;// s1 - (s2 * quotient)

        cout << a << " = " << b << "*" << quotient << " + " << remainder << " | s1 = " << s1 << " | s2 = " << s2 << " | s3 = " << s3 << " | t1 = " << t1 << " | t2 = " << t2 << "| t3 = " << t3 << endl;
    
        return EEA(b, remainder, s2, s3, t2, t3);
    }
}

void menu()
{
    cout << "1) Input values" <<endl;
    cout << "2) Exit" <<endl;
}

int main()
{
    cout << "______________________________" <<endl;
    cout << "|Extended Euclidean Algorithm|" <<endl;
    cout << "|____________________________|" <<endl;

    int a;
    int b;
    int menuInput;
    struct values data;
    bool mainLoop = true;


    while(mainLoop)
    {
        menu();

        cout << "Input menu option: ";
        cin >> menuInput;
        cout << endl;

        switch (menuInput)
        {
            cin.clear();
            fflush(stdin);

            case 1:

                cout << "a = ";
                cin >> a;
                cout << endl;

                cin.clear();
                fflush(stdin);

                cout << "b = ";
                cin >> b;
                cout << endl;

                data = EEA(a, b, 1, 0, 0, 1);

                cout << "GCD(" << a << ", " << b << ") = " << data.gcd << endl;
                cout << data.gcd << " = " << a << "(" << data.s2 << ") + " << b << "(" << data.t2 << ")" <<endl;

                break;
            case 2:
                mainLoop = false;

                break;
            default:
                cout << "Your input is out of bounds." <<endl;
                break;
        }

    }
}