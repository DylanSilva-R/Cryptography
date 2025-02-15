
/*
Rules:

a mod b = r
a = bq + r

0 <= r < b

a mod -b => -a mod b
-a mod -b => a mod b
-a mod b, just compute
*/

#include <iostream>
#include <cstdlib>
using namespace std;

class MyException : public std::exception {
    private:
    string message;

    public:
    MyException(string msg) : message(msg) {}
    string what () {
        return message;
    }
};

int pMod(int a, int b)
{
    // Find out all test cases.

    int quotient = 0;
    int remainder = 0;


    try
    {
        if(b == 0)
        {
            throw MyException("b can't be zero"); 
        }
        
        if(a < 0 && b < 0)
        {
            a = abs(a);
            b = abs(b);

            remainder = a % b;
            quotient = a / b;

            // cout << a << " = " << b << " * " << quotient << " + " << remainder <<endl;
            return remainder;
        }else if(a > 0 && b < 0)
        {
            a = -a;
            b = abs(b);

            quotient = a / b;

            if(quotient * b == a)
            {
                // cout << a << " = " << b << " * " << quotient << " + " << 0 <<endl;
                return 0;
            }else
            {
                quotient--;
                remainder = abs(quotient * b) + a;

                // cout << a << " = " << b << " * " << quotient << " + " << remainder <<endl;
                return remainder;
            }

        }else if(a < 0 && b > 0)
        {

            quotient = a / b;

            if(quotient * b == a)
            {
                //cout << a << " = " << b << " * " << quotient << " + " << 0 <<endl;
                return 0;
            }else
            {
                quotient--;
                remainder = abs(quotient * b) + a;

                //cout << a << " = " << b << " * " << quotient << " + " << remainder <<endl;
                return remainder;
            }

        }else
        {
            remainder = a % b;
            quotient = a / b;

            // cout << a << " = " << b << " * " << quotient << " + " << remainder <<endl;
            return remainder;
        }

    }
    catch(MyException e)
    {
        std::cerr << e.what() << endl;
        EXIT_FAILURE;
    }
}