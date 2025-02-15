#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include "Proper_Mod.h"
using namespace std;

/*
*   Key expansion function expands the key relative to message data.
*/
string keyExpansion(string data , int sizeData, string key, int sizeKey, string alphabet, int sizeAlphabet)
{
    char charAtIndexMsg;
    string keyExp;
    int countKeyLoc = 0;
    int keyLocAlph;
    bool foundKeyLocAlph = false;

    for(int i = 0; i < sizeData; i++)
    {
        if(countKeyLoc == sizeKey)
        {
            countKeyLoc = 0;
        }

        charAtIndexMsg = data[i];

        for(int j = 0; j < sizeAlphabet; j++)
        {

            if(charAtIndexMsg == alphabet[j])
            {
                //cout << charAtIndexMsg << " = " << alphabet[j] << endl;
                keyExp += key[countKeyLoc];
                foundKeyLocAlph = true;
                break;
            }
        }

        if(foundKeyLocAlph)
        {
            countKeyLoc++;
            foundKeyLocAlph = false;
        }else
        {
            keyExp += '*';
        }
    }

    cout << data << endl;
    cout << keyExp << endl;

    return keyExp;
}

void encryptFun(string data , int sizeData, string key, int sizeKey, string alphabet, int sizeAlphabet)
{
    // Key needs to fit inside data.
    string encryptedMsg;
    string keyExp = keyExpansion(data, sizeData, key, sizeKey, alphabet, sizeAlphabet);

    for(int i = 0; i < sizeData; i++)
    {
        if(keyExp[i] == '*')
        {
            encryptedMsg += data[i];
        }else
        {
            int charKeyLocation;
            int charMsgLocation;

            for(int j = 0; j < sizeAlphabet; j++)
            {
                if(data[i] == alphabet[j])
                {
                    // cout << "Data " << data[i] << " = Location " << j << endl;
                    charMsgLocation = j;
                }

                if(keyExp[i] == alphabet[j])
                {
                    // cout << "Data " << keyExp[i] << " = Location " << j << endl;
                    charKeyLocation = j;
                }
            }

            int newLocation = pMod(charMsgLocation + charKeyLocation, sizeAlphabet); 
            encryptedMsg += alphabet[newLocation];
        }
    }

    cout << encryptedMsg << endl;
}


void decryptFun(string data , int sizeData, string key, int sizeKey, string alphabet, int sizeAlphabet)
{
    string decryptedMsg;
    string keyExp = keyExpansion(data, sizeData, key, sizeKey, alphabet, sizeAlphabet);

    for(int i = 0; i < sizeData; i++)
    {
        if(keyExp[i] == '*')
        {
            decryptedMsg += data[i];
        }else
        {
            int charKeyLocation;
            int charMsgLocation;

            for(int j = 0; j < sizeAlphabet; j++)
            {
                if(data[i] == alphabet[j])
                {
                    //cout << "Data " << data[i] << " = Location " << j << endl;
                    charMsgLocation = j;
                }

                if(keyExp[i] == alphabet[j])
                {
                    //cout << "Data " << keyExp[i] << " = Location " << j << endl;
                    charKeyLocation = j;
                }
            }

            int newLocation = pMod(charMsgLocation - charKeyLocation, sizeAlphabet); 
            decryptedMsg += alphabet[newLocation];
        }
    }

    cout << decryptedMsg << endl;
}

int main(int argc, char * argv[])
{
    // argc keeps track of the amount of arguments that are passed. This includes the executable file.
    // argv[] let's you access the argument. In this case the file name would be in location 1

    string inputData;
    string encryptedData;
    string key;
    int keySize;
    string alphabet;
    bool encrypt = false;
    bool decrypt = false;

    if(argc < 2)
    {
        cerr << "Not enough arguments were identified." << endl;
        return 1;
    }

    if(argc > 5)
    {
        cerr << "Too many arguments." << endl;
        return 1;
    }


    ifstream inputFile (argv[1]);
    ifstream outputFile (argv[3]);
    stringstream buffer;
    string data;
    int sizeOfData;
    int sizeOfAlphabet;

    if(inputFile.is_open() && outputFile.is_open())
    {
        if(*argv[4] == 'e')
        {
            /*
            * Read data from plain1.txt file and encrypt it using the key.
            */

           // First, the user needs to input an alphabet to use to encrypt the data.

            cout << "Input alphabet values: ";
            getline(cin, alphabet);
            cout << endl;

            sizeOfAlphabet = alphabet.size();

            // Second, read all data and add it to a string.

            buffer << inputFile.rdbuf();
            data = buffer.str();
            sizeOfData = data.size();

            // Third, obtain key data.

            key = argv[2];
            keySize = key.size();

            cout << "Alphabet input = " << alphabet << endl;

            encryptFun(data , sizeOfData, key, keySize, alphabet, sizeOfAlphabet);

        }else if(*argv[4] == 'd')
        {
            /*
            * Read data from cypher2.txt and decrypt with the key.
            */

            cout << "Input alphabet values: ";
            getline(cin, alphabet);
            cout << endl;
    
            sizeOfAlphabet = alphabet.size();



            // Second, read all data and add it to a string.
        
            buffer << outputFile.rdbuf();
            data = buffer.str();
            sizeOfData = data.size();

            // Third obtain key data.
            key = argv[2];
            keySize = key.size();
            
            //string data , int sizeData, string key, int sizeKey, string alphabet, int sizeAlphabet
            decryptFun(data, sizeOfData, key, keySize, alphabet, sizeOfAlphabet);            

        }else
        {
            cerr << "Didn't use 'e' or 'd' commands" << endl;
            return 1;
        }
    }else
    {
        cerr << "Couldn't open files." << endl;
        return 1;
    }

    inputFile.close();
    outputFile.close();

    return 0;
}