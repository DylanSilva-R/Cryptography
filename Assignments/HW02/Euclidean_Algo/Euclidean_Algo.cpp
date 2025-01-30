#include <stdio.h>
#include "Proper_Mod.h"


int GCD(int a, int b)
{
    /*
    * Recrussibe algorithm
    */

    int remainder = pMod(a, b);
    int quotient;

    if(remainder == 0)
    {
        quotient = a / b;
        cout << a << " = " << b << "*" << quotient << " + " << remainder << endl;
        return b;
    }else
    {
        quotient = a / b;
        cout << a << " = " << b << "*" << quotient << " + " << remainder << endl;
        return GCD(b, remainder);
    }

}


void menu()
{
    cout << "1) Input values" << endl;
    cout << "2) Exit" << endl;
}

int main()
{

    cout << "_____________________" << endl;
    cout << "|Euclidean Algorithm|" << endl;
    cout << "|___________________|" << endl;
    cout << endl;

    bool mainLoop = true;
    int menuInput;
    int a;
    int b;
    int gcd;

    while(mainLoop)
    {
        menu();

        cout << "Input menu option: ";
        cin >> menuInput;
        cout << endl;


        if(!cin)
        {
            cout << "You input a string. Please try again." << endl;
            cin.clear();
            cin.ignore(256,'\n'); // Discard or ignore chracters from input.
            continue;
        }

        switch(menuInput)
        {
            case 1:
                cin.clear();
                cin.ignore(256, '\n');

                cout << "a = ";
                cin >> a;
                cout << endl;

                cout << "b = ";
                cin >> b;
                cout << endl;

                a = abs(a);
                b = abs(b);

                if(a > b)
                {
                    gcd = GCD(a, b);
                    cout << endl;
                    cout << "GCD(" << a << ", " << b << ") = " << gcd <<endl;
                }else
                {
                    gcd = GCD(b, a);
                    cout << endl;
                    cout << "GCD(" << a << ", " << b << ") = " << gcd <<endl;
                }

                break;
            case 2:
                mainLoop = false;
                break;
            default:
                cout << "Your inpti is out bounds. Please try again." << endl;
                break;
        }


    }


}