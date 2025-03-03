#include <iostream>
#include <string>
#include <cstring>
#include <bitset>



std::string convertToBinary(std::string functionStr, int size)
{
    // This function converst the hex value to binary.
    std::string binary = "";

    for (int i = 0; i < size; i++)
    {
        switch (functionStr[i])
        {
        case '0':  
            binary += "0000";
            break;
        case '1':
            binary += "0001";
            break;
        case '2':
            binary += "0010";
            break;
        case '3':
            binary += "0011";
            break;
        case '4':
            binary += "0100";
            break;
        case '5':
            binary += "0101";
            break;
        case '6':
            binary += "0110";
            break;
        case '7':
            binary += "0111";
            break;
        case '8':
            binary += "1000";
            break;
        case '9':
            binary += "1001";
            break;
        case 'A':
            binary += "1010";
            break;
        case 'B':
            binary += "1011";
            break;
        case 'C':
            binary += "1100";
            break;
        case 'D':
            binary += "1101";
            break;
        case 'E':
            binary += "1110";
            break;
        case 'F':
            binary += "1111";
            break;

        }

    }

    return binary;
}

std::string getRidOfChars(std::string function, int size)
{
    // Primary purpose of this function is to get rid of 0x characters from hex inputs.

    int i;
    for (i = 0; i < size; i++)
    {
        if (function[i] == 'x')
        {
            break;
        }
    }

    function.erase(0, i + 1);

    size = function.size();
    std::string binaryStr = convertToBinary(function, size);

    return binaryStr;
}

int getDegree(std::bitset<32> binary)
{
    int degree = -1;
    if (binary == 0)
    {
        return (degree);
    }
    while (binary != 0)
    {
        ++degree;         
        binary = binary >> 1;
    }
    return (degree);
}

std::bitset<32> divideGalois(std::bitset<32> PolynomialOne, std::bitset<32> PolynomialTwo)
{

    // If the degree of the first polynomial is less than the second polynomial.
    // First polynomial is the answer.
    if (getDegree(PolynomialOne) < getDegree(PolynomialTwo)) {
        return PolynomialOne;
    }
    
    //  Hold necessary values.
    std::bitset<32> result = PolynomialOne;
    int polyTwoDegree = getDegree(PolynomialTwo);
    
    // If degree in remainder is greater than or equal to degree of second polynomial keep dividing.
    // If not, that is the answer.
    while (getDegree(result) >= polyTwoDegree) {
        // Calculate shift value.
        int shift = getDegree(result) - polyTwoDegree;
        // std::cout << "Shift = " << shift << " ";
        
        // Hold second polynomial for necessary shifting.
        // The shifting represents the divisor properly fitting into the divisor to do XOR operations on.
        std::bitset<32> shiftedPolyTwo = PolynomialTwo;
        shiftedPolyTwo <<= shift;
        
        // XOR shifted polynomial if first polynomial for subtraction.
        // std::cout << result << " XOR " << shiftedPolyTwo;
        result ^= shiftedPolyTwo;
        // std::cout << " = " << result << "\n";
    }
    
    return result;
}

std::bitset<32> multiplyGalois(std::bitset<32> PolynomialOne, std::bitset<32> PolynomialTwo, std::bitset<32> PolynomialThree)
{
    int index = 0;
    std::bitset<32> result;

    while(PolynomialTwo != 0)
    {
        if(PolynomialTwo[0] == 1)
        {
            result = result ^ (PolynomialOne << index);
        }

        PolynomialTwo = PolynomialTwo >> 1;
        ++index;
    }

    return divideGalois(result, PolynomialThree);

}

int main(int argc, char **argv)
{

    if (argc < 0 && argc > 4)
    {
        std::cerr << "There are too many arguments are too little.\n";
    }

    if (argc == 2)
    {
        // First get rid of useless characters: 0x
        char *function = argv[1];
        int size = strlen(function);

        std::string functionStr;
        functionStr.assign(function, size);

        std::string binaryStr = getRidOfChars(functionStr, size);
        std::bitset<32> binary (binaryStr);

        std::cout << "Finding degree of polynomial: " << function << "\n";

        // Find degree of function.
        int degree = getDegree(binary);
        std::cout << "Degree of "<< binary << " = "<< degree <<"\n";

    }
    else if (argc == 3)
    {
        char* PolynomialOne = argv[1];
        char* PolynomialTwo = argv[2];
        int sizeofPolynomialOne = strlen(PolynomialOne);
        int sizeofPolynomialTwo = strlen(PolynomialTwo);

        std::string PolynomialOneStr;
        PolynomialOneStr.assign(PolynomialOne);

        std::string PolynomialTwoStr;
        PolynomialTwoStr.assign(PolynomialTwo);

        std::cout<< "Polynomial one: " << PolynomialOneStr << "\n";
        std::cout << "Polynomial two: " << PolynomialTwoStr << "\n";

        std::string binaryStrPolynomialOne = getRidOfChars(PolynomialOneStr, sizeofPolynomialOne);
        std::string binaryStrPolynomialTwo = getRidOfChars(PolynomialTwoStr, sizeofPolynomialTwo);

        std::bitset<32> binaryPolynomialOne (binaryStrPolynomialOne);
        std::bitset<32> binaryPolynomialTwo (binaryStrPolynomialTwo);

        std::bitset<32> result = divideGalois(binaryPolynomialOne, binaryPolynomialTwo);

        std::cout << result << "\n";

    }else if(argc == 4)
    {

        char* PolynomialOne = argv[1];
        char* PolynomialTwo = argv[2];
        char* PolynomialThree = argv[3];
        int sizeofPolynomialOne = strlen(PolynomialOne);
        int sizeofPolynomialTwo = strlen(PolynomialTwo);
        int sizeofPolynomialThree = strlen(PolynomialThree);


        std::string PolynomialOneStr;
        PolynomialOneStr.assign(PolynomialOne);

        std::string PolynomialTwoStr;
        PolynomialTwoStr.assign(PolynomialTwo);

        std::string PolynomialThreeStr;
        PolynomialThreeStr.assign(PolynomialThree);

        std::cout<< "Polynomial one: " << PolynomialOneStr << "\n";
        std::cout << "Polynomial two: " << PolynomialTwoStr << "\n";
        std::cout << "Polynomial three: " << PolynomialThreeStr << "\n";

        std::string binaryStrPolynomialOne = getRidOfChars(PolynomialOneStr, sizeofPolynomialOne);
        std::string binaryStrPolynomialTwo = getRidOfChars(PolynomialTwoStr, sizeofPolynomialTwo);
        std::string binaryStrPolynomialThree = getRidOfChars(PolynomialThreeStr, sizeofPolynomialThree);

        std::bitset<32> binaryPolynomialOne (binaryStrPolynomialOne);
        std::bitset<32> binaryPolynomialTwo (binaryStrPolynomialTwo);
        std::bitset<32> binaryPolynomialThree (binaryStrPolynomialThree);

        std::bitset<32> result = multiplyGalois(binaryPolynomialOne, binaryPolynomialTwo, binaryPolynomialThree);
        std::cout << result << "\n";


    }

      char* PolynomialOne = argv[1];
        char* PolynomialTwo = argv[2];
        char* PolynomialThree = argv[3];
        int sizeofPolynomialOne = strlen(PolynomialOne);
        int sizeofPolynomialTwo = strlen(PolynomialTwo);
        int sizeofPolynomialThree = strlen(PolynomialThree);


        // std::string PolynomialOneStr;
        // PolynomialOneStr.assign("0xD5");

        // std::string PolynomialTwoStr;
        // PolynomialTwoStr.assign("0xD5");

        // std::string PolynomialThreeStr;
        // PolynomialThreeStr.assign("0xD5");

        // int sizeofPolynomialOne = PolynomialOneStr.size();
        // int sizeofPolynomialTwo = PolynomialTwoStr.size();
        // int sizeofPolynomialThree  = PolynomialThreeStr.size();

        // std::cout<< "Polynomial one: " << PolynomialOneStr << "\n";
        // std::cout << "Polynomial two: " << PolynomialTwoStr << "\n";
        // std::cout << "Polynomial three: " << PolynomialThreeStr << "\n";

        // std::string binaryStrPolynomialOne = getRidOfChars(PolynomialOneStr, sizeofPolynomialOne);
        // std::string binaryStrPolynomialTwo = getRidOfChars(PolynomialTwoStr, sizeofPolynomialTwo);
        // std::string binaryStrPolynomialThree = getRidOfChars(PolynomialThreeStr, sizeofPolynomialThree);

        // std::bitset<32> binaryPolynomialOne (binaryStrPolynomialOne);
        // std::bitset<32> binaryPolynomialTwo (binaryStrPolynomialTwo);
        // std::bitset<32> binaryPolynomialThree (binaryStrPolynomialThree);

        // std::bitset<32> result = multiplyGalois(binaryPolynomialOne, binaryPolynomialTwo, binaryPolynomialThree);
        // std::cout << result << "\n";



    return 1;
}