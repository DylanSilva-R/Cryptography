
#include <iostream>
#include <bitset>
#include <string>
#include <vector>
#include <math.h>


bool isPrime(int x)
{
    if(x <= 1)
    {
        return false;
    }

    for(int i = 2; i < x; i++)
    {
        if(x % i == 0)
        {
            return false;
        }
    }

    return true;
}

int binaryToDecimal(std::string n)
{
    std::string num = n;
    int dec_value = 0;

    // Initializing base value to 1, i.e 2^0
    int base = 1;

    int len = num.length();
    for (int i = len - 1; i >= 0; i--) {
        if (num[i] == '1')
            dec_value += base;
        base = base * 2;
    }

    return dec_value;
}

std::string hexToBinary(std::string hexData)
{
    int size = hexData.length();
    std::string binaryData = "";

    for (int i = 0; i < size; i++)
    {
        switch (hexData[i])
        {
            case '0':
                binaryData += "0000";

                break;
            case '1':
                binaryData += "0001";

                break;
            case '2':
                binaryData += "0010";

                break;
            case '3':
                binaryData += "0011";

                break;
            case '4':
                binaryData += "0100";

                break;
            case '5':
                binaryData += "0101";

                break;
            case '6':
                binaryData += "0110";

                break;
            case '7':
                binaryData += "0111";

                break;
            case '8':
                binaryData += "1000";

                break;
            case '9':
                binaryData += "1001";

                break;
            case 'A':
                binaryData += "1010";

                break;
            case 'B':
                binaryData += "1011";

                break;
            case 'C':
                binaryData += "1100";

                break;
            case 'D':
                binaryData += "1101";
                
                break;
            case 'E':
                binaryData += "1110";
                
                break;
            case 'F':
                binaryData += "1111";

                break;
            default:
                
                std::cerr<< "Invalid hex value\n";

                break;
        }
    }

    return binaryData;
}

std::vector<int> convertArrayToInteger(std::vector<std::string> binaryData, int size)
{
    std::vector<int> integerData;
    int integerConverion;

    for(int i = 0; i < size; i++)
    {
        integerConverion = binaryToDecimal(binaryData[i]);
        integerData.push_back(integerConverion);
    }

    return integerData;
}

std::vector<std::string> convertArrayToBinary(std::vector<std::string> hexData, int size)
{
    std::vector<std::string> binaryData;
    std::string binaryVal;

    for(int i = 0; i < size; i++)
    {
        binaryVal = hexToBinary(hexData[i]);
        binaryData.push_back(binaryVal);
    }

    return binaryData;
}

void twoLargestPrimeNumbers(std::vector<std::string> binaryData, int size)
{
    int largePrimes[2];
    int binaryDecimalArray[size];
    int binToDecimal;



}

std::vector<std::string> stringToArray(std::string data)
{
    int stringLength = data.length();
    std::vector<std::string> newData;
    std::string holdData = "";

    for (int i = 0; i < stringLength; i++)
    {
        if (data[i] == ' ')
        {
            newData.push_back(holdData);
            holdData = "";
            continue;
        }

        holdData += data[i];

        if (data[i + 1] == '\0')
        {
            newData.push_back(holdData);
            holdData = "";
            break;
        }
    }

    return newData;
}

void printData(std::vector<std::string> data, int size)
{

    for (int i = 0; i < size; i++)
    {
        std::cout << data[i] << "\n";
    }
}

int main()
{
    std::cout << "________________ \n";
    std::cout << "|Blum Blum Shub| \n";
    std::cout << "|______________| \n";

    std::string seed = "3FA 0FF AD5 C3E 011 1837 22 40C";
    
    // Format data into string vector.
    std::vector<std::string> formattedSeed = stringToArray(seed);
    int sizeData = formattedSeed.size();

    // Convert data to binaries.
    std::vector<std::string> hexToBinaryVec = convertArrayToBinary(formattedSeed, sizeData);

    // Convert binary data to integers.
    std::vector<int> binaryToInt = convertArrayToInteger(hexToBinaryVec, sizeData);
    
    // Sort integers.



    //twoLargestPrimeNumbers(formattedData, sizeData);

    return 0;
}