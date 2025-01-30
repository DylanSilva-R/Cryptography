#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include <ctype.h>
#define MAX_BUFFER_SIZE 1024

/*
Goals:
    - The program should be able to implement Caesor's algorithm to encrypt and decrypt messages/.
*/

char alphabet [] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n','o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z'};
int sizeOfMessage;

int properModulus(int a, int b)
{
  int r;
  int q;
  int newQ;
  int newP;
  int newR;

  // First, check for 0 value inputs.

  if(b == 0 || (a == 0 && b == 0))
  {
    perror("Result is undefined\n");
    exit(1);
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
    newQ = abs(newQ);
    newQ = newQ + 1;

    newP = newQ * b;
    newR = a - newP;
  }

  return newR;
}

void encrypt(char * message, int shiftValue)
{
  printf("size of message: %d\n", sizeOfMessage);

  printf("Message before encryption(in function): ");
  for(int i = 0; i < sizeOfMessage; i++)
  {
    printf("%c", message[i]);
  }
  printf("\n");
  char messageToLower[sizeOfMessage];
  int locationOfLetters[sizeOfMessage];

  for(int i = 0; i < sizeOfMessage; i++) // This for loop focuses on converting character input to lower case values and it creates pairs for chracters and numerical values.
  {
    char grabChar = tolower(message[i]);
    messageToLower[i] = grabChar;

    for(int j = 0; j < 26; j++)
    {
      if(grabChar == ' ')
      {
        locationOfLetters[i] = -1;
      }else if(grabChar == alphabet[j])
      {
        locationOfLetters[i] = j;
      }
    }
  }

  for(int i = 0; i < sizeOfMessage; i++)
  {
    printf("Numerical pair of %c is %d\n", message[i], locationOfLetters[i]);
  }
  printf("\n");

  /*
  *   First, the function needs to be definined, which is C = E(k, letter) = (letter+k) mod 26
  *   Second, traverse the message. Grab the charcter value, find its numerical pair and add it to the shift value.
  *   Third, after finding the letter + shift plug that value and 26 into propermodlus and you will find the new shifted position.
  */

  char encryptedMessage[sizeOfMessage];

  for(int i = 0; i < sizeOfMessage; i++)
  {
    if(messageToLower[i] == ' ')
    {
      encryptedMessage[i] == '0';
    }else
    {
      int letterPShift = locationOfLetters[i] + shiftValue;
      int shiftedLocation = properModulus(letterPShift, 26);
      encryptedMessage[i] = alphabet[shiftedLocation];
    }
  }

  printf("Your encrypted message: %s", encryptedMessage);
  encryptedMessage[strcspn(encryptedMessage, "\n")] = 0;
  printf("Size of encrypted message: %d\n", strlen(encryptedMessage));
  free(encryptedMessage);
  printf("\n"); printf("\n");
}

void decrypt(char message[], int shiftValue)
{
  char messageToLower[sizeOfMessage];
  int locationOfLetters[sizeOfMessage];

  printf("Message before decryption(in function): ");
  for(int i = 0; i < sizeOfMessage; i++)
  {
    printf("%c", message[i]);
  }

  for(int i = 0; i < sizeOfMessage; i++) // This for loop focuses on converting character input to lower case values and it creates pairs for chracters and numerical values.
  {
    char grabChar = tolower(message[i]);
    messageToLower[i] = grabChar;

    for(int j = 0; j < 26; j++)
    {
      if(grabChar == alphabet[j])
      {
        locationOfLetters[i] = j;
      }
    }
  }

  char decryptedMessage[sizeOfMessage];

  // For decryption, you have to follow the formula: p = D(C, k) mod 26. C being the encrypted letter location, and k being the shift value.

  for(int i = 0; i < sizeOfMessage; i++)
  {
    int letterPShift = locationOfLetters[i] - shiftValue;
    int shiftedLocation = properModulus(letterPShift, 26);
    decryptedMessage[i] = alphabet[shiftedLocation];
  }

  printf("Your encrypted message: ");
  for(int i = 0; i < sizeOfMessage; i++)
  {
    printf("%c", decryptedMessage[i]);
  }
  printf("\n"); printf("\n");
}

void bruteforceAttack(char * message, int sizeOfMessage)
{
  /*
  * All you have to do is use all 25 shift values with the message until you find something human readable.
  */

  // First, convert the message to lower case and find their numerical pairs, just like the other few times.
  char messageToLower[sizeOfMessage];
  int locationOfLetters[sizeOfMessage];

  for(int i = 0; i < sizeOfMessage; i++) // This for loop focuses on converting character input to lower case values and it creates pairs for chracters and numerical values.
  {
    char grabChar = tolower(message[i]);
    messageToLower[i] = grabChar;

    for(int j = 0; j < 26; j++)
    {
      if(grabChar == alphabet[j])
      {
        locationOfLetters[i] = j;
      }
    }
  }

  for(int i = 0; i < sizeOfMessage; i++)
  {
    printf("%c ", locationOfLetters[i]);
  }

  // Second, now run every possibility.
  char encryptedMessage[sizeOfMessage];

  for(int i = 0; i < 26; i++)
  {
    for(int j = 0; j < sizeOfMessage; j++)
    {
      int letterPShift = locationOfLetters[j] + i;
      int shiftedLocation = properModulus(letterPShift, 26);
      encryptedMessage[i] = alphabet[shiftedLocation];
    }

    for(int k = 0; k < sizeOfMessage; k++)
    {
      printf("%c", encryptedMessage[k]);
    }

    printf("\n");
    free(encryptedMessage);
  }

}

int checkIfInt()
{
  int userInt;

  if (scanf("%d", &userInt) != 1) {
    fprintf(stderr, "Invalid input\n");
    exit(1);
  }

  return userInt;
}

char * inputMessage()
{
  char InputBuffer[100];
  fgets(InputBuffer, MAX_BUFFER_SIZE, stdin);
  printf("%s\n", InputBuffer);
  int size = 100;
  printf("Length of buffer: %d", size);

  char * message = (char*)malloc(size * sizeof(char));

  return message;
}

void menu()
{
  printf("1) Encrypt\n");
  printf("2) Decrypt\n");
  printf("3) Bruteforce\n");
  printf("4) Exit program\n");
}

int main()
{
  printf("_______________\n");
  printf("|Caesor Cipher|\n");
  printf("|_____________|\n");
  printf("By Dylan Silva-Rivas\n");
  printf("\n");

  bool mainLoop = true;

  while(mainLoop)
  {
    menu();
    printf("\n");
    printf("Enter Menu option: ");
    int menuOption = checkIfInt();

    printf("%d\n", menuOption);

    if(menuOption == 1)
    {
      printf("Input a shift value: ");
      int shiftValue = checkIfInt();
      printf("Input a messsage to encrypt: ");
      char * plainMessage = inputMessage();

      for(int i = 0; i < sizeOfMessage; i++)
      {
        printf("%c", plainMessage[i]);
      }

      printf("\n");
      encrypt(plainMessage, shiftValue);
      //free(plainMessage);
    }else if(menuOption == 2)
    {
      printf("Input a shift value: ");
      int shiftValue = checkIfInt();
      printf("Input a messsage to decrypt: ");
      //const char * encryptedMessage = inputMessage();
      //int size = strlen(encryptedMessage);

      //decrypt(encryptedMessage, size, shiftValue);
    }else if(menuOption == 3)
    {
      char type[] = "bruteforce";
      printf("Input a messsage to bruteforce: ");
      //char * bruteforceMessage = inputMessage();
      //int size = strlen(bruteforceMessage);

      //bruteforceAttack(bruteforceMessage, size);
    }else if(menuOption == 4)
    {
      mainLoop = false;
    }
  }

  return 0;
}
