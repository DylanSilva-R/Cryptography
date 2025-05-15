#include <iostream>
#include <bitset>

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

void polynomialLongDivision(std::bitset<32> divisor, PolynomialOverGFData &data)
{
    // dividend / divisor = quotient
    // Rewrite polynomial long division to hold the quotient and remainder in struct value.
    // Mimicing binary long division

    // If the degree of the first polynomial is less than the second polynomial.
    // First polynomial is the answer.
    //  Hold necessary values.
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
        std::cout << "Shift: " << shift << "\n";

        // XOR shifted polynomial if first polynomial for subtraction.
        // std::cout << result << " XOR " << shiftedPolyTwo;

        data.remainder ^= shiftedPolyTwo;
    }

    data.quotient = quotientTemp;
}

int main()
{

    std::bitset<32> polyOne("001000000001");
    std::bitset<32> polyField("000100011011");

    PolynomialOverGFData data;

    data.polynomialOne = polyOne;
    data.polynomialField = polyField;

    // Take in divisor, dividend
    polynomialLongDivision(polyOne, data);
    
    std::cout << "\n";
    std::cout << "Quotient = " << data.quotient <<"\n";
    std::cout << "Remainder  " << data.remainder <<"\n";

    return 0;
}