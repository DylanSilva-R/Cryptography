import java.util.HashMap;
import java.util.Scanner;

public class Main
{

    static int get_Degree(String binary, int size)
    {
        int countUpToIndex = 0;
        boolean oneExists = false;

        for(countUpToIndex = 0; countUpToIndex < size; countUpToIndex++)
        {
            if(binary.charAt(countUpToIndex) == '1')
            {
                oneExists = true;
                break;
            }
        }

        if(oneExists)
        {
            int countDegree = size - countUpToIndex;
            return countDegree - 1;
        }else
        {
            return 0;
        }
    }

    static String hexToBinary(String hex) throws CustomException
    {
        String binary = "";
 
        // Convert hex to uppercase.
        hex = hex.toUpperCase();
 
        // initializing the HashMap class
        HashMap<Character, String> hashMap = new HashMap<Character, String>();
 
        // storing the key value pairs
        hashMap.put('0', "0000");
        hashMap.put('1', "0001");
        hashMap.put('2', "0010");
        hashMap.put('3', "0011");
        hashMap.put('4', "0100");
        hashMap.put('5', "0101");
        hashMap.put('6', "0110");
        hashMap.put('7', "0111");
        hashMap.put('8', "1000");
        hashMap.put('9', "1001");
        hashMap.put('A', "1010");
        hashMap.put('B', "1011");
        hashMap.put('C', "1100");
        hashMap.put('D', "1101");
        hashMap.put('E', "1110");
        hashMap.put('F', "1111");
 
        int i;
        char ch;
 
        // Go through all hex values to convert
        for (i = 0; i < hex.length(); i++) {

            ch = hex.charAt(i); // Hold character value
 
            if (hashMap.containsKey(ch))
 
                binary += hashMap.get(ch);
 
            else {
                throw new CustomException("Invalid Hexadecimal String");
            }
        }
 
        return binary;
    }

    static void menu()
    {
        System.out.println("1) Find highest degree in polynomial.");
        System.out.println("2) Divide polynomials");
        System.out.println("3) Multiply polynomials");
    }

    public static void main(String[]args)
    {
        System.out.println("______________________");
        System.out.println("|Polynomical analysis|");
        System.out.println("|____________________|");
        System.out.println("By: Dylan Silva-Rivas");

        try 
        {
            Scanner input = new Scanner(System.in);

            String HexVal = "0x00";

            String[] newString = HexVal.split("x");
            

            String binary = hexToBinary(newString[1]);
            int sizeBin = binary.length();


            System.out.println(binary);
            System.out.println("Binary location 0: " + binary.charAt(sizeBin-1));

            int highestDegree = get_Degree(binary, sizeBin);

            System.out.println("Highest degree = " + highestDegree);
            input.close();   
        } catch (Exception e) 
        {
            System.err.println(e.getMessage());
        }
    }
}


class CustomException extends Exception
{
    public CustomException(String errorMsg)
    {
        super(errorMsg);
    }
}
