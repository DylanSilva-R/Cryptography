#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
using namespace std;



void encrypt(string data , int sizeData, string key, int sizeKey, string alphabet, int sizeAlphabet)
{
    // Key needs to fit inside data.
    char charAtIndexKey;
    int keyLocAlph;

    for(int i = 0; i < sizeData; i++)
    {
        charAtIndexKey = key[i % sizeData];

        for(int j = 0; j < sizeAlphabet; j++)
        {
            if(key[charAtIndexKey] == alphabet[j])
            {
                keyLoc = j;
                break;


            }
        }
    }
}


void decrypt()
{

}

int main(int argc, char * argv[])
{
    // argc keeps track of the amount of arguments that are passed. This includes the executable file.
    // argv[] let's you access the argument. In this case the file name would be in location 1

    string inputData;
    string encryptedData;
    string key;
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
            * First, the user needs to input an alphabet to use to encrypt the data.
            */

            cout << "Input alphabet values: ";
            cin >> alphabet;
            cout << endl;


            sizeOfAlphabet = alphabet.size();

            buffer << inputFile.rdbuf();
            data = buffer.str();

            // Second, read all data and add it to a string.
            
            cout << "Data in file: " << data << endl; 
            


        }else if(*argv[4] == 'd')
        {
            /*
            * Read data from cypher2.txt and decrypt with the key.
            */

            cout << "Input alphabet values: ";
            cin >> alphabet;
            cout << endl;

            buffer << inputFile.rdbuf();
            data = buffer.str();

            // Second, read all data and add it to a string.
            


            cout << "Data" << data << endl; 
            

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