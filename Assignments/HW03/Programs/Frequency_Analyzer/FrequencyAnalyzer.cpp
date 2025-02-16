#include <iostream>
#include <stdio.h>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
using namespace std;

struct frequencyChar
{
    char character; // Character.
    int frequency; // Frequency of character.
    bool used; // Checking if character has been used.
};

// This function prints out the struct data on the terminal.
void printData(frequencyChar frequencyArray[], int asciiSize, int sizeOfData)
{
    string toHex;

    for (int i = 0; i < asciiSize; i++)
    {

        if (isprint(frequencyArray[i].character) != 0)
        {
            cout << endl;
            cout << frequencyArray[i].character << " - " << frequencyArray[i].frequency << " of " << sizeOfData << endl;
            cout << endl;
        }
        else
        {
            cout << endl;
            printf("%x", (int)frequencyArray[i].character);
            cout << " - " << frequencyArray[i].frequency << " of " << sizeOfData << endl;
            cout << endl;
        }
    }

    cout << "Most common: (" << frequencyArray[asciiSize - 1].character << " = " << (int)frequencyArray[asciiSize - 1].character << " = ";
    printf("%x) - ",(int)frequencyArray[asciiSize - 1].character); 
    cout << frequencyArray[asciiSize - 1].frequency << " of " << sizeOfData << endl;
}

// Merge sort
void merge(frequencyChar frequencyArray[], int left, int mid, int right)
{
    int i, j, k;
    int n1 = mid - left + 1;
    int n2 = right - mid;

    // Create temporary vectors
    frequencyChar leftFrequencyArray[n1];
    frequencyChar rightFrequencyArray[n2];

    // Copy data to temporary vectors
    for (i = 0; i < n1; i++)
        leftFrequencyArray[i] = frequencyArray[left + i];
    for (j = 0; j < n2; j++)
        rightFrequencyArray[j] = frequencyArray[mid + 1 + j];

    // Merge the temporary vectors back into vec[left..right]
    i = 0;
    j = 0;
    k = left;
    while (i < n1 && j < n2)
    {
        if (leftFrequencyArray[i].frequency <= rightFrequencyArray[j].frequency)
        {
            frequencyArray[k] = leftFrequencyArray[i];
            i++;
        }
        else
        {
            frequencyArray[k] = rightFrequencyArray[j];
            j++;
        }
        k++;
    }

    // Copy the remaining elements of leftVec[], if any
    while (i < n1)
    {
        frequencyArray[k] = leftFrequencyArray[i];
        i++;
        k++;
    }

    // Copy the remaining elements of rightVec[], if any
    while (j < n2)
    {
        frequencyArray[k] = rightFrequencyArray[j];
        j++;
        k++;
    }
}

void mergeSort(frequencyChar frequencyArray[], int left, int right)
{
    if (left < right)
    {
        int mid = left + (right - left) / 2;

        mergeSort(frequencyArray, left, mid);
        mergeSort(frequencyArray, mid + 1, right);

        merge(frequencyArray, left, mid, right);
    }
}

void frequencyAnalysis(string data, int sizeOfData)
{
    // Create array of 255 elements that of type frequencyChar
    int asciiCodeSize = 256;

    frequencyChar frequencyArray[asciiCodeSize];

    // Set all struct values used attributes to false and set all frequencies to 0;
    for (int i = 0; i < asciiCodeSize; i++)
    {
        frequencyArray[i].used = false;
        frequencyArray[i].frequency = 0;
        frequencyArray[i].character = char(i);
    }

    // Traverse through that data. Check if char value is contained in the frequencyChar array.
    // This will be possible by converting the char value to an integer value and using the integer value as its index position.
    for (int i = 0; i < sizeOfData; i++)
    {
        int convertToInt = (int)data[i];

        if (frequencyArray[convertToInt].used == true)
        {
            frequencyArray[convertToInt].frequency++;
        }
        else
        {
            frequencyArray[convertToInt].character = data[i];
            frequencyArray[convertToInt].frequency++;
            frequencyArray[convertToInt].used = true;
        }
    }

    mergeSort(frequencyArray, 0, asciiCodeSize - 1);

    printData(frequencyArray, asciiCodeSize, sizeOfData);
}

int main(int argc, char *argv[])
{

    if (argc < 2)
    {
        cerr << "You need to input a file name." << endl;
        return 1;
    }

    cout << argv[1] << " Frequency Analysis." << endl;

    ifstream inputFile(argv[1]);
    string data;
    int sizeOfData;
    stringstream buffer;

    if (inputFile.is_open())
    {
        buffer << inputFile.rdbuf();
        data = buffer.str();
        sizeOfData = data.size();

        cout << "Amount of data = " << sizeOfData << endl;

        frequencyAnalysis(data, sizeOfData);
    }

    return 0;
}