import java.util.InputMismatchException;
import java.util.Scanner;
import java.lang.Math;

class CaesorCipherJ
{
  static char alphabet [] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n','o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z'};

  static int properModulus(int a, int b) throws customException
  {
    int r = 0;
    int q = 0;
    int newQ = 0;
    int newP = 0;
    int newR = 0;

    // First, check for 0 value inputs.

    if(b == 0 || (a == 0 && b == 0))
    {
      throw new customException("You input b = 0 or a = 0 and b = 0");
    }

    if(a >= 0 && b > 0 || a > 0 && b < 0) // Second, check for positive inputs.
    {
      r = a % b;
      q = a / b;

      return r;
    }else if(a < 0 && b > 0) // Third, check for a negative -a input and +b input and +a and -b inputs.
    {
      newQ = a / b;
      newQ = newQ + -1;
      newP = newQ * b;
      newR = a - newP;

    }else if(a < 0 && b < 0) // Fourth, check for -a and -b input.
    {
      newQ = a / b;
      newQ = Math.abs(newQ);
      newQ = newQ + 1;

      newP = newQ * b;
      newR = a - newP;
    }

    return newR;
  }

  /*
  public <T> void printArray(T [] elements, int size)
  {
    for(int i = 0; i < size; i++)
    {
      System.out.print(elements[i] + " ");
    }
    System.out.println();
  }
    */


  private static void printArray(char[] encryptedMessage, int size) {
    for(int i = 0; i < size; i++)
    {
      System.out.print(encryptedMessage[i]);
    }
    System.out.println();
  }


  private static void printArray(int[] locationOfLetters, int size) {
    for(int i = 0; i < size; i++)
    {
      System.out.print(locationOfLetters[i] + " ");
    }
    System.out.println();
  }

  static char [] toLowerArray(char [] message, int size)
  {
    char messageToLower[] = new char[size];

    for(int i = 0; i < size; i++) // This for loop focuses on converting character input to lower case values and it creates pairs for chracters and numerical values.
    {
      messageToLower[i] = Character.toLowerCase(message[i]);
    }

    return messageToLower;
  }

  static int [] numericalPairs(char [] message, int size)
  {
    int locationOfLetters[] = new int[size];

    for(int i = 0; i < size; i++)
    {
      for(int j = 0; j < 26; j++)
      {
        char grabChar = message[i];

        if(grabChar == alphabet[j])
        {
          locationOfLetters[i] = j;
        }
      }
    }

    return locationOfLetters;
  }

  static void encrypt(char [] message, int size, int shiftValue) throws customException
  {
    char messageToLower[] = toLowerArray(message, size);
    //messageToLower = toLowerArray(message, size);

    int locationOfLetters[] = numericalPairs(messageToLower, size);
    char encryptedMessage[] = new char[size];
    // First, convert all letters to their lower case value.

    System.out.print("Message in lower case: ");
    printArray(messageToLower, size);
    System.out.print("Letter and numerical pairs: ");
    printArray(locationOfLetters, size);

    /*
    *   Second, the function needs to be definined, which is C = E(k, letter) = (letter+k) mod 26
    *   Third, traverse the message. Grab the charcter value, find its numerical pair and add it to the shift value.
    *   Fourth, after finding the letter + shift plug that value and 26 into propermodlus and you will find the new shifted position.
    */

    for(int i = 0; i < size; i++)
    {
      if(message[i] == ' ')
      {
        encryptedMessage[i] = ' ';
      }else if(!Character.isLetter(message[i]))
      {
        encryptedMessage[i] = message[i];
      }else
      {

        int letterPShift = locationOfLetters[i] + shiftValue;
        int shiftedLocation = properModulus(letterPShift, 26);

        if(shiftedLocation < 0)
        {
          shiftedLocation = 26 + shiftedLocation;
        }else if(shiftedLocation >= 26)
        {
          shiftedLocation = shiftedLocation - 26;
        }

        encryptedMessage[i] = alphabet[shiftedLocation];
      }
    }

    System.out.print("Your encrypted message: ");
    printArray(encryptedMessage, size);
  }

  static void decrypt(char [] message, int size, int shiftValue) throws customException
  {
    char messageToLower[] = new char[size];
    messageToLower = toLowerArray(message, size);

    int locationOfLetters[] = new int[size];
    locationOfLetters = numericalPairs(messageToLower, size);
    char decryptedMessage[] = new char[size];

    System.out.print("Message in lower case: ");
    printArray(messageToLower, size);
    System.out.print("Letter and numerical pairs: ");
    printArray(locationOfLetters, size);

    /*
    *   Second, the function needs to be definined, which is C = E(k, letter) = (letter-k) mod 26
    *   Third, traverse the message. Grab the charcter value, find its numerical pair and add it to the shift value.
    *   Fourth, after finding the letter + shift plug that value and 26 into propermodlus and you will find the new shifted position.
    */

    for(int i = 0; i < size; i++)
    {
      if(message[i] == ' ')
      {
        decryptedMessage[i] = ' ';
      }else if(!Character.isLetter(message[i]))
      {
        decryptedMessage[i] = message[i];
      }else
      {
        int letterMShift = locationOfLetters[i] - shiftValue;
        int shiftedLocation = properModulus(letterMShift, 26);

        if(shiftedLocation < 0)
        {
          shiftedLocation = 26 + shiftedLocation;
        }else if(shiftedLocation >= 26)
        {
          shiftedLocation = shiftedLocation - 26;
        }

        decryptedMessage[i] = alphabet[shiftedLocation];
      }
    }

    System.out.print("Your decrypted message: ");
    printArray(decryptedMessage, size);
  }

  static void bruteforceAttack(char [] message, int size) throws customException
  {
    /*
    * All you have to do is use all 25 shift values with the message until you find something human readable.
    */

    // First, convert the message to lower case and find their numerical pairs, just like the other few times.
    char messageToLower[] = new char[size];
    messageToLower = toLowerArray(message, size);

    int locationOfLetters[] = new int[size];
    locationOfLetters = numericalPairs(messageToLower, size);

    // Second, now run every possibility.
    char decryptedMessage[] = new char[size];


    System.out.println("Message: ");
    printArray(messageToLower, size);
    printArray(locationOfLetters, size);


    for(int i = 0; i < 26; i++)
    {
      for(int j = 0; j < size; j++)
      {
        if(message[j] == ' ')
        {
          decryptedMessage[j] = ' ';
        }else if(!Character.isLetter(message[j]))
        {
          decryptedMessage[j] = message[j];
        }else
        {
          int letterPShift = locationOfLetters[j] + i;
          int shiftedLocation = properModulus(letterPShift, 26);

          if(shiftedLocation < 0)
          {
            shiftedLocation = 26 + shiftedLocation;
          }else if(shiftedLocation >= 26)
          {
            shiftedLocation = shiftedLocation - 26;
          }

          decryptedMessage[j] = alphabet[shiftedLocation];
        }
      }
      System.out.print("Possibility " + i + ": ");
      printArray(decryptedMessage, size);

    }
  }

  static void menu()
  {
    System.out.println("1) Encrypt");
    System.out.println("2) Decrypt");
    System.out.println("3) Bruteforce");
    System.out.println("4) Exit program");
  }


  public static void main(String[]args)
  {
    Scanner input = new Scanner(System.in);
    boolean mainLoop = true;
    int sizeOfMessage = 0;
    char [] toCharArray;
    int shiftVal;
    String tempShiftVal;
    String message;

    System.out.println("_______________");
    System.out.println("|Caesor Cipher|");
    System.out.println("|_____________|");
    System.out.println("By: Dylan Silva-Rivas");
    System.out.println();

    while(mainLoop)
    {
      menu();
      System.out.println();

      System.out.print("Input menu option: ");
      String menuOption = input.nextLine();
      int convert = Integer.parseInt(menuOption);

      try
      {
        switch(convert)
        {
          case 1:
            System.out.print("Input shift value: ");
            tempShiftVal = input.nextLine();
            shiftVal = Integer.parseInt(tempShiftVal);
            System.out.print("Input meessage to encrypt: ");
            message = input.nextLine();
            sizeOfMessage = message.length();
            toCharArray = message.toCharArray();

            encrypt(toCharArray, sizeOfMessage, shiftVal);

            break;
          case 2:
            System.out.print("Input shift value: ");
            tempShiftVal = input.nextLine();
            shiftVal = Integer.parseInt(tempShiftVal);
            System.out.print("Input meessage decrypt: ");
            message = input.nextLine();
            sizeOfMessage = message.length();
            toCharArray = message.toCharArray();

            decrypt(toCharArray, sizeOfMessage, shiftVal);

            break;
          case 3:
            System.out.print("Input meessage bruteforce: ");
            message = input.nextLine();
            sizeOfMessage = message.length();
            toCharArray = message.toCharArray();
            bruteforceAttack(toCharArray, sizeOfMessage);

            break;
          case 4:
            mainLoop = false;

            break;
          default:
            System.out.println("Input must be out of bounds. Please try again.");

            break;
        }
      }catch(customException ex)
      {
        System.out.println(ex.getMessage());
      }catch(InputMismatchException ex)
      {
        System.out.println("It seems like you input the wrong data type. Please try again.");
      }catch(NumberFormatException ex){
        System.out.println("It seems like you input a string for an integer. Please try again.");
      }
    }

    input.close();
    System.exit(0);
  }
}

class customException extends Exception
{
  public customException(String error)
  {
    super(error);
  }
}
