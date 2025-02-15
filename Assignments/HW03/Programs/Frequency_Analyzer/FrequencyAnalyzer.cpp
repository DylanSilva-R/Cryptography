#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
using namespace std;


struct frequencyChar
{
    char character;
    int frequency;
};


void frequencyAnalysis(string data, int sizeOfData)
{
    for(int i = 0; i < sizeOfData; i++)
    {

    }
}

int main(int argc, char * argv[])
{


    if(argc < 2)
    {
        cerr << "You need to input a file name." << endl;
        return 1;
    }

    ifstream inputFile (argv[1]);
    string data;
    int sizeOfData;
    stringstream buffer;


    if(inputFile.is_open())
    {
        buffer << inputFile.rdbuf();
        data = buffer.str();
        sizeOfData = data.size();

    }

    return 0;
}