
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <bitset>
#include <sstream>
#include <cstring>
#include <iomanip>

const std::string filePath = ".\\Data\\";

struct PolynomialOverGFData
{
    std::bitset<32> polynomialOne;
    std::bitset<32> polynomialTwo;
    std::bitset<32> polynomialField;
    std::bitset<32> quotient;
    std::bitset<32> remainder;
    std::bitset<32> product;
};

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

void divideGalois(std::bitset<32> divisor, PolynomialOverGFData &data)
{
    // dividend / divisor = quotient
    // Rewrite polynomial long division to hold the quotient and remainder in struct value.
    // Mimicing binary long division
    // If the degree of the first polynomial is less than the second polynomial.
    // First polynomial is the answer.
    // Hold necessary values.
    // Need to obtain quotient and remainder.+

    data.remainder = divisor;
    std::bitset<32> quotientTemp;
    int fieldDegree = getDegree(data.polynomialField);

    // If degree in remainder is greater than or equal to degree of second polynomial keep dividing.
    // If not, that is the answer.

    while (getDegree(data.remainder) >= fieldDegree)
    {
        // Calculate shift value.

        int shift = getDegree(data.remainder) - fieldDegree;

        // std::cout << "Shift = " << shift << " ";
        // Hold second polynomial for necessary shifting.
        // The shifting represents the divisor properly fitting into the divisor to do XOR operations on.

        std::bitset<32> shiftedPolyTwo = data.polynomialField;
        shiftedPolyTwo <<= shift;

        quotientTemp[shift] = 1;
        //std::cout << "Shift: " << shift << "\n";

        // XOR shifted polynomial if first polynomial for subtraction.
        // std::cout << result << " XOR " << shiftedPolyTwo;

        data.remainder ^= shiftedPolyTwo;
    }

    data.quotient = quotientTemp;
}

void multiplyGalois(PolynomialOverGFData &data)
{
    int index = 0;
    std::bitset<32> holdPolyTwo = data.polynomialTwo;
    data.product = 0; // Reset product value.

    while (holdPolyTwo != 0)
    {
        if (holdPolyTwo[0] == 1)
        {
            data.product = data.product ^ (data.polynomialOne << index);
        }

        holdPolyTwo = holdPolyTwo >> 1;
        ++index;
    }

    holdPolyTwo = 0;
}

std::string FFunctionDecrypt(std::bitset<32> LH, std::bitset<32> RH, std::string key, int rounds, int blockSize)
{
    // Function = (Rn-1 * keyn) mod 0x13 for 8-bits block size.
    // Function = (Rn-1 * keyn) mod 0x11B for 16-bits block size.
    // 0x13 = 00010011
    // 0x11B = 100011011

    PolynomialOverGFData GFData;
    std::bitset <32> zeroOut("000000000");
    GFData.polynomialOne = zeroOut;
    GFData.polynomialTwo = zeroOut;
    GFData.polynomialField = zeroOut;
    GFData.quotient = zeroOut;
    GFData.remainder = zeroOut;
    GFData.product = zeroOut;

    
    if(blockSize == 8)
    {
        std::bitset <32> galoisField("00010011");
        GFData.polynomialField = galoisField;
    }else if(blockSize == 16)
    {
        std::bitset <32> galoisField("100011011");
        GFData.polynomialField = galoisField;
    }

    int i;
    for(i = rounds - 1; i >= 0; i--)
    {
        std::cout << "LH" << i << ": " << LH << ", RH" << i << ": " << RH <<"\n";

        // Temporarily set RH to polynomialOne in the GFData;
        GFData.polynomialOne = RH;
        // Temporarily set character key to polynomial two in the GFData.
        std::bitset <32> keyCharToBinary(key[i]);
        std::cout << "Value of " << key[i] << " = " << keyCharToBinary << "\n";
        GFData.polynomialTwo = keyCharToBinary;

        multiplyGalois(GFData);

        std::cout << GFData.polynomialOne << " * " << GFData.polynomialTwo  << " = " << GFData.product <<"\n";

        if (getDegree(GFData.product) < getDegree(GFData.polynomialField))
        {
            std::cout << "Remainder = " << GFData.remainder << "\n";
            std::bitset <32> tempRH = GFData.remainder ^ LH;
            LH = RH;
            RH = tempRH;
        }
        else
        {
            divideGalois(GFData.product, GFData);
            std::cout << "Remainder = " << GFData.remainder << "\n";
            std::bitset <32> tempRH = GFData.remainder ^ LH;
            LH = RH;
            RH = tempRH;
        }
        std::cout << "\n";
    }
    
    // Convert value to hex values.
    // A single hex value is made up of 4-bits.
    // First, try to convert each block to its HEX value.d

    unsigned long long LHNum = LH.to_ullong();
    unsigned long long RHNum = RH.to_ullong();

    char asciiLeft = static_cast<char>(LHNum); // Convert the first character to its ASCII value.
    char asciiRight = static_cast<char>(RHNum); // Convert the second character to its ASCII value. 

    std::cout << "LHF = " << asciiLeft << " = " << LHNum << "\n";
    std::cout << "RHF = " << asciiRight << " = " << RHNum << "\n";

    std::string finalOutput = ""; // Create a string to hold the cypher text data.
    finalOutput += asciiRight; // Add the first character to the cypher text data.
    finalOutput += asciiLeft; // Add the second character to the cypher text data.

    // unsigned long long LHNum = LH.to_ullong();
    // unsigned long long RHNum = RH.to_ullong();

    // std::stringstream LHHex;
    // std::stringstream RHHex;

    // LHHex << std::hex << std::setw(2) << LHNum;
    // RHHex << std::hex << std::setw(2) << RHNum;

    // std::string LHHexString = LHHex.str();
    // std::string RHHexString = RHHex.str();
    
    // std::string finalOutput = "";

    // // After all rounds, set the LH to RH and RH to LH.
    // finalOutput += RHHexString;
    // finalOutput += " ";
    // finalOutput += LHHexString;
    
    // std::cout << "LH" << i << " = " << LHHexString << ", RH" << i << " = " << RHHexString << "\n";

    return finalOutput;
}

std::string FFunctionEncrypt(std::bitset<32> LH, std::bitset<32> RH, std::string key, int rounds, int blockSize)
{
    // Total block size of 8-bits.
    // Each block contains 4-bits
    // Function = (Rn-1 * keyn) mod 0x13 for 8-bits block size.
    // Function = (Rn-1 * keyn) mod 0x11B for 16-bits block size.
    // 0x13 = 00010011 = x^4 + x^3 + 1
    // 0x11B = 100011011 = x^8 + x^4 + x^3 + x^2 + 1
    
    PolynomialOverGFData GFData;
    
    std::bitset <32> zeroOut("000000000");
    GFData.polynomialOne = zeroOut;
    GFData.polynomialTwo = zeroOut;
    GFData.polynomialField = zeroOut;
    GFData.quotient = zeroOut;
    GFData.remainder = zeroOut;
    GFData.product = zeroOut;

    if(blockSize == 8)
    {
        std::bitset <32> galoisField("00010011");
        GFData.polynomialField = galoisField;
    }else if(blockSize == 16)
    {
        std::bitset <32> galoisField("100011011");
        GFData.polynomialField = galoisField;
    }


    // Iterate all rounds of the key.
    int i = 0;
    for(i = 0; i < rounds; i++)
    {
        std::cout << "LH" << i << ": " << LH << ", RH" << i << ": " << RH <<"\n";

        // Temporarily set RH to polynomialOne in the GFData;
        GFData.polynomialOne = RH;
        // Temporarily set character key to polynomial two in the GFData.
        std::bitset <32> keyCharToBinary(key[i]);
        std::cout << "Value of " << key[i] << " = " << keyCharToBinary << "\n";
        GFData.polynomialTwo = keyCharToBinary;

        multiplyGalois(GFData);

        std::cout << GFData.polynomialOne << " * " << GFData.polynomialTwo  << " = " << GFData.product <<"\n";

        if (getDegree(GFData.product) < getDegree(GFData.polynomialField))
        {
            std::cout << "Remainder = " << GFData.remainder << "\n";
            std::bitset <32> tempRH = GFData.remainder ^ LH;
            LH = RH;
            RH = tempRH;
        }
        else
        {
            divideGalois(GFData.product, GFData);
            std::cout << "Remainder = " << GFData.remainder << "\n";
            std::bitset <32> tempRH = GFData.remainder ^ LH;
            LH = RH;
            RH = tempRH;
        }

        std::cout << "New LH = " << LH << ", new RH = " << RH << "\n";
        std::cout << "\n";
    }

    // Convert value to hex values.
    // A single hex value is made up of 4-bits.
    // First, try to convert each blockclear to its HEX value.d

    unsigned long long LHNum = LH.to_ullong();
    unsigned long long RHNum = RH.to_ullong();

    char asciiLeft = static_cast<char>(LHNum); // Convert the first character to its ASCII value.
    char asciiRight = static_cast<char>(RHNum); // Convert the second character to its ASCII value. 

    std::cout << "LHF = " << asciiLeft << " = " << LHNum << "\n";
    std::cout << "RHF = " << asciiRight << " = " << RHNum << "\n";

    std::string finalOutput = ""; // Create a string to hold the cypher text data.
    finalOutput += asciiRight; // Add the first character to the cypher text data.
    finalOutput += asciiLeft; // Add the second character to the cypher text data.
    
    // std::stringstream LHHex;
    // std::stringstream RHHex;

    // LHHex << std::hex << std::setw(2) << LHNum;
    // RHHex << std::hex << std::setw(2) << RHNum;

    // std::string LHHexString = LHHex.str();
    // std::string RHHexString = RHHex.str();
    // std::string finalOutput = "";

    // // After all rounds, set the LH to RH and RH to LH.
    // finalOutput += RHHexString;
    // finalOutput += " ";
    // finalOutput += LHHexString;

    // std::cout << "LH" << i << " = " << LHHexString << ", RH" << i << " = " << RHHexString << "\n";
    // std::cout << "\n";

    return finalOutput;
}


void encryptDataEigthBit(std::string plainTextBinary, std::string cypherText, std::string key, int blockSize)
{
    // One character is 8-bits.
    // One characters gets split into two 4-bit blocks.
    std::ifstream plainBinary(plainTextBinary);
    std::ofstream cypherFile(cypherText);

    
    // Open file and check if it's accessible.
    if(!plainBinary)
    {
        cypherFile.close();
        plainBinary.close();    
        std::cerr << "Error opening file.\n";
        return;
    }
    
    std::vector <std::bitset <32>> bits;

    std::string binaryValue;
    // Read each binary value (space separated)
    while (plainBinary >> binaryValue) {
        // Convert the binary string to a bitset
        std::bitset<32> bit(binaryValue);

        std::string leftStr = binaryValue.substr(0, 4); // Get the left 4 bits as a string
        std::string rigthStr = binaryValue.substr(4, 4); // Get the right 4 bits as a string

        std::bitset<32> leftBits(leftStr); // Mask to get the left 4 bits
        std::bitset<32> rightBits(rigthStr);

        bits.push_back(leftBits); // Store the left bits in the vector.
        bits.push_back(rightBits); // Store the right bits in the vector.
    }

    std::string cypherTextData = ""; // Create a string to hold the cypher text data.
    for(int i = 0; i < bits.size(); i+=2)
    {
        // Convert the characters to binary and store them in the vector.
        std::string firstBits = bits[i].to_string();
        std::string secondBits = bits[i + 1].to_string();
        
        char firstChar = static_cast<char>(std::bitset<32>(firstBits).to_ulong()); // Convert the first character to its ASCII value.
        char secondChar = static_cast<char>(std::bitset<32>(secondBits).to_ulong()); // Convert the second character to its ASCII value.

        std::cout << "First binary = " << firstBits << ", second bits = " << secondBits << "\n"; // Print the characters.
        
        cypherTextData += FFunctionEncrypt(bits[i], bits[i + 1], key, key.size(), blockSize); // Call the FFunction to encrypt the data.
    }

    cypherFile << cypherTextData;
    plainBinary.close();
    cypherFile.close();
}

void decryptDataEightBit(std::string cypherTextBinaries, std::string plainText, std::string key, int blockSize)
{
    // ifstream is used to read from file.
    // ofstream is used to write onto file.

    std::ifstream cypherFileBinaries(cypherTextBinaries);
    std::ofstream plainFile(plainText);

    if(!cypherFileBinaries)
    {
        std::cerr << "Error opening file.\n";
        cypherFileBinaries.close();
        plainFile.close();    
        return;
    }
    
    std::vector <std::bitset <32>> bits;
    std::string binaryValue;
    // Read each binary value (space separated)
    while (cypherFileBinaries >> binaryValue) {
        // Convert the binary string to a bitset
        std::bitset<32> bit(binaryValue);

        std::string leftStr = binaryValue.substr(0, 4); // Get the left 4 bits as a string
        std::string rigthStr = binaryValue.substr(4, 4); // Get the right 4 bits as a string

        std::bitset<32> leftBits(leftStr); // Mask to get the left 4 bits
        std::bitset<32> rightBits(rigthStr);

        bits.push_back(leftBits); // Store the left bits in the vector.
        bits.push_back(rightBits); // Store the right bits in the vector.
    }

    std::string cypherTextData = ""; // Create a string to hold the cypher text data.
    for(int i = 0; i < bits.size(); i+=2)
    {
        // Convert the characters to binary and store them in the vector.
        std::string firstBits = bits[i].to_string();
        std::string secondBits = bits[i + 1].to_string();
        
        char firstChar = static_cast<char>(std::bitset<32>(firstBits).to_ulong()); // Convert the first character to its ASCII value.
        char secondChar = static_cast<char>(std::bitset<32>(secondBits).to_ulong()); // Convert the second character to its ASCII value.

        std::cout << "First char = " << firstChar << ", second char = " << secondChar << "\n"; // Print the characters.
        
        cypherTextData += FFunctionDecrypt(bits[i], bits[i + 1], key, key.size(), blockSize); // Call the FFunction to encrypt the data.
    }

    plainFile << cypherTextData; // Write the decrypted message to the file.
    plainFile.close();
    cypherFileBinaries.close();
}

void encryptDataSixteenBit(std::string plainTextBinaries, std::string cypherText, std::string key, int blockSize)
{
    // ifstream is used to read from file.
    // ofstream is used to write onto file.
    // Each characters represents 8-bits; therefore, two characters need to be chosen to represent 16-bits.

    std::ifstream plainFileBinaries(plainTextBinaries); // Open file.
    std::ofstream cypherFile(cypherText); // Create file.

    if(!plainFileBinaries) // Check if file is accessible.
    {
        std::cerr << "Error opening file.\n";
        plainFileBinaries.close();  
        cypherFile.close();  
        return;
    }

    std::vector <std::bitset <32>> bits;
    std::string binaryValue;
    // Read each binary value (space separated)
    while (plainFileBinaries >> binaryValue) {
        // Convert the binary string to a bitset
        std::bitset<32> bit(binaryValue);
        bits.push_back(bit); // Store the left bits in the vector.
    }

    std::cout << "Amount of bits = " << bits.size() << "\n";
    std::string cypherTextData = ""; // Create a string to hold the cypher text data.
    for(int i = 0; i < bits.size(); i+=2)
    {
        // Convert the characters to binary and store them in the vector.
        std::string firstBits = bits[i].to_string();
        std::string secondBits = bits[i + 1].to_string();
        
        char firstChar = static_cast<char>(std::bitset<32>(firstBits).to_ulong()); // Convert the first character to its ASCII value.
        char secondChar = static_cast<char>(std::bitset<32>(secondBits).to_ulong()); // Convert the second character to its ASCII value.

        std::cout << "First char = " << firstChar << ", second char = " << secondChar << "\n"; // Print the characters.
        
        cypherTextData += FFunctionEncrypt(bits[i], bits[i + 1], key, key.size(), blockSize); // Call the FFunction to encrypt the data.
    }

    cypherFile << cypherTextData;
    plainFileBinaries.close();
    cypherFile.close();
}

void decryptDataSixteenBit(std::string cypherTextBinaries, std::string plainText, std::string key, int blockSize)
{    
    // ifstream is used to read from file.
    // ofstream is used to write onto file.

    std::ifstream cypherFileBinaries(cypherTextBinaries);
    std::ofstream plainFile(plainText);
    std::string allData;
    std::stringstream buffer;
    int rounds = key.size();

    if(!cypherFileBinaries)
    {
        std::cerr << "Error opening file.\n";
        cypherFileBinaries.close();
        plainFile.close();    
        return;
    }
    
    std::vector <std::bitset <32>> bits;
    std::string binaryValue;
    // Read each binary value (space separated)
    while (cypherFileBinaries >> binaryValue) {
        // Convert the binary string to a bitset
        std::bitset<32> bit(binaryValue);
        bits.push_back(bit); // Store the left bits in the vector.
    }

    // Read binary file and properly push data into vector.
    std::string decryptedMsg = "";
    for(int i = 0; i < bits.size(); i += 2)
    {
        // Convert the characters to binary and store them in the vector.
        std::string firstBits = bits[i].to_string();
        std::string secondBits = bits[i + 1].to_string();
        
        char firstChar = static_cast<char>(std::bitset<32>(firstBits).to_ulong()); // Convert the first character to its ASCII value.
        char secondChar = static_cast<char>(std::bitset<32>(secondBits).to_ulong()); // Convert the second character to its ASCII value.

        std::cout << "First char = " << firstChar << ", second char = " << secondChar << "\n"; // Print the characters.
        
        decryptedMsg += FFunctionDecrypt(bits[i], bits[i + 1], key, key.size(), blockSize); // Call the FFunction to encrypt the data.
    }

    plainFile << decryptedMsg; // Write the decrypted message to the file.
    cypherFileBinaries.close();
    plainFile.close();
}



int main(int argc, char *argv[])
{
    std::cout << "\n";
    std::cout << "_________________________\n";
    std::cout << "|Fiestel Cipher 8/16 bit|\n";
    std::cout << "|_______________________|\n";
    std::cout << "\n";

    if(argc != 6)
    {
        std::cerr << "ERROR, too few arguments\n";
        std::cerr << "Input: feistel <File_One> <File_Two> <Key> <'e' | 'd'> <8|16 bits>\n";
        std::cout << "\n";
    }else
    {
        std::string firstFile = argv[1];
        // Second file is a file that will be created.
        std::string secondFile = argv[2];
        std::string key = argv[3];
        char* encryptOrDecrypt = argv[4];
        int blockSize = atoi(argv[5]);

        firstFile = filePath + firstFile;
        secondFile = filePath + secondFile;

        std::cout << "First file = " << firstFile << "\n";
        std::cout << "Second file  = " << secondFile << "\n";

        // Depending on the block size, that will determine on how many characters will be implemented to encrypt the data.

        if(*encryptOrDecrypt == 'e')
        {

            if(blockSize == 8)
            {
                encryptDataEigthBit(firstFile, secondFile, key, blockSize);

            }else if(blockSize == 16)
            {
                encryptDataSixteenBit(firstFile, secondFile, key, blockSize);
            }else
            {
                std::cerr << "You input an invalid block size.\n";
            }

        }else if(*encryptOrDecrypt == 'd')
        {

            if(blockSize == 8)
            {
                encryptDataEigthBit(firstFile, secondFile, key, blockSize);

            }else if(blockSize == 16)
            {
                decryptDataSixteenBit(firstFile, secondFile, key, blockSize);
            }else
            {
                std::cerr << "You input an invalid block size. The only options are 8 and 16.\n";
            }

        }else
        {
            std::cerr << "You didn't mention encrption or decryption.\n";
            std::cerr << "Usage: feistel <Input_Filename> <Key> 'e' | 'd'\n";
            std::cout << "\n";
        }


        delete encryptOrDecrypt;
    }

    return 0;
}
