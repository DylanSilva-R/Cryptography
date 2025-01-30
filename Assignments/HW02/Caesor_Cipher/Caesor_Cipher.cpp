#include <stdio.h>
#include <limits>
#include <string.h>
#include "Proper_Mod.h"
using namespace std;

string alphabet = "abcdefghijklmnopqrstuvwxyz";
int sizeAlp = alphabet.size();

int findLocation(char letter)
{
    for(int i = 0; i < sizeAlp; i++)
    {
        if(letter == alphabet[i])
        {
            return i;
        }
    }
}

void bruteforce(string cipherText, int cipherSize)
{
    string decipher = "";
    int shiftLocation;
    
    for(int key = 0; key < sizeAlp; key++)
    {
        for(int cipherTra = 0; cipherTra < cipherSize; cipherTra++)
        {

            int charLoc = findLocation(cipherText[cipherTra]); 
            int shiftLocation = pMod(charLoc + key, sizeAlp);

            decipher += alphabet[shiftLocation];
        }

        cout << "Key = " << key << ", decipher = " << decipher<< endl;

        decipher = "";
    }

    cout << endl;

}

void encrypt(string plainText, int sizeOfPlainText, int key)
{
    string encryptedMsg = "";

    for(int plainTra = 0; plainTra < sizeOfPlainText; plainTra++)
    {
        int charLoc = findLocation((char)tolower(plainText[plainTra]));

        if(isspace(plainText[plainTra]))
        {
            encryptedMsg += " ";
            //encryptedMsg.insert(plainTra, " ");
        }else
        {
            int shiftLocation = pMod((charLoc + key), sizeAlp);
            encryptedMsg += alphabet[shiftLocation];
        }
    }

    cout << "Key = " << key << ", encrypted message: " << encryptedMsg << endl;

}

void decrypt(string encryptedMsg, int sizeOfEncryptedMsg, int key)
{
    string plainText = "";

    for(int encryTra = 0; encryTra < sizeOfEncryptedMsg; encryTra++)
    {
        int charLoc = findLocation((char)tolower(encryptedMsg[encryTra]));

        if(isspace(encryptedMsg[encryTra]))
        {
            plainText += " ";
        }else
        {
            int shiftLocation = pMod((charLoc - key), sizeAlp);
            cout << "Shift location = " << shiftLocation << endl;
            plainText += alphabet[shiftLocation];
        }
    }
    
    cout << "Key = " << key << ", plain text message: " << plainText << endl;

}

void menu()
{
    cout <<"1) Encrypt"<<endl;
    cout <<"2) Decrypt"<<endl;
    cout <<"3) Bruteforce"<<endl;
    cout <<"4) Exit"<<endl;
}

int main()
{
    cout <<"_______________"<<endl;
    cout <<"|Caesor Cipher|"<<endl;
    cout <<"|_____________|"<<endl;

    bool mainLoop = true;
    int menuOption;
    string cipherText;
    int sizeOfCipher;
    string plainText;
    int sizeOfPlain;
    int key;


    while(mainLoop)
    {

        menu();

        cout << "Input menu option: ";
        cin >> menuOption;
        cout << endl;

        if(!cin)
        {
            cout << "You input a string. Please try again." << endl;
            cin.clear();
            cin.ignore(256,'\n'); // Discard or ignore chracters from input.
            continue;
        }

        switch (menuOption)
        {
            case 1:
                cin.clear();
                cin.ignore(256,'\n'); // Discard or ignore chracters from input.

                cout << "Input plain text: ";
                getline(cin, plainText);
                sizeOfPlain = plainText.size();
                cout << endl;

                cout << "Input key: ";
                cin >> key;
                cout << endl;
                

                encrypt(plainText, sizeOfPlain, key);
            
                break;
            case 2:
                cin.clear();
                cin.ignore(256,'\n'); // Discard or ignore chracters from input.

                cout << "Input cipher text: ";
                getline(cin, cipherText);
                sizeOfCipher = cipherText.size();
                cout << endl;

                cout << "Input key: ";
                cin >> key;
                cout << endl;
                
                decrypt(cipherText, sizeOfCipher, key);

                break;
            case 3:
                cin.clear();
                cin.ignore(256,'\n'); // Discard or ignore chracters from input.

                cout << "Input the cipher text: ";
                getline(cin, cipherText);
                sizeOfCipher = cipherText.size();
                cout << "" << endl;
            
                bruteforce(cipherText, sizeOfCipher);

                break;
            case 4:
                mainLoop = false;

                break;
            default:
                cout << "Your input is out of bounds." << endl;

                break;
        }
    
    }
    

    return 0;
}