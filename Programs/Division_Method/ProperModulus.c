
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdbool.h>


bool continueOrNot()
{
  //Create a (char) buffer for user input
  char yesOrNO[4];
  bool loop = true;

  while(loop)
  {
    printf("Would you like to continue (Yes or No)? ");
    scanf("%s", &yesOrNO); // Take input

    yesOrNO[strcspn(yesOrNO, "\n")] = '\0';

    // Convert all characters to lowercase.
    for(int i = 0; i < 4; i++)
    {
      yesOrNO[i] = tolower(yesOrNO[i]);
    }

    if(strcmp(yesOrNO, "yes") == 0 || strcmp(yesOrNO, "y") == 0)
    {
      return false;
    }else if(strcmp(yesOrNO, "no") == 0 || strcmp(yesOrNO, "n") == 0)
    {
      return true;
    }else
    {
      printf("Looks like your input isn't yes or no. Please try again.\n");
    }
  }
}


int checkIfInt(char * type)
{
  /*
  * First, create a buffer for the user to input characters.
  * Second, check if the values in the buffer represent a number.
  */
  char input[100];
  int userNumInput = 0;
  bool mainLoop = true;

  while(mainLoop)
  {
    bool floatBool = false;
    bool charBool = false;

    printf("Enter your %s: ", type);
    scanf("%s", input);
    fflush(stdin); // Clear input buffer.

    // The for loop checks if the user inputs values 0-9 and a - sign. If there are characters
    // inputs or a decimal inputs, an error will be displayed.
    for(int i = 0; i < strlen(input); i++)
    {
      if(!((input[i] >= '0') && (input[i] <= '9')))
      {
        if(input[i] == '-')
        {
          continue;
        }
        if(input[i] == '.')
        {
          floatBool = true;
          break;
        }else
        {
          charBool = true;
          break;
        }
      }
    }

    if(charBool)
    {
      printf("It seems like you input characters instead of integers. Please try again.\n");
    }
    else if(floatBool)
    {
      printf("It seems like you input a floating point value. Please try again.\n");
    }else
    {
      userNumInput = atoi(input);
      break;
    }
  }

  return userNumInput;
}


void properModulus(int a, int b)
{
  int r;
  int q;
  int newQ;
  int newP;
  int newR;

  // First, check for 0 value inputs.

  if(b == 0 || (a == 0 && b == 0))
  {
    printf("Result is undefined\n");
    exit(EXIT_FAILURE);

  }

  if(a >= 0 && b > 0 || a > 0 && b < 0) // Second, check for positive inputs.
  {
    r = a % b;
    q = a / b;
    printf("%d = %d * %d + %d\n", a, b, q, r);
  }else if(a < 0 && b > 0) // Third, check for a negative -a input and +b input and +a and -b inputs.
  {
    newQ = a / b;
    newQ = newQ + -1;
    newP = newQ * b;
    newR = a - newP;

    printf("%d = %d * %d + %d\n", a, b, newQ, newR);
  }else if(a < 0 && b < 0) // Fourth, check for -a and -b input.
  {
    newQ = a / b;
    newQ = abs(newQ);
    newQ = newQ + 1;

    newP = newQ * b;
    newR = a - newP;

    printf("%d = %d * %d + %d\n", a, b, newQ, newR);
  }
}

int main()
{
  while (true)
  {
    printf("____________________ \n");
    printf("|  Proper Modulus  |\n");
    printf("|__________________|\n");
    printf("By: Dylan Silva-Rivas\n", );
    printf("Format: a = q*b + r \n");
    printf("a = Dividend\n");
    printf("q = Quotient\n");
    printf("b = Divisor\n");
    printf("r = Remainder\n");


    char dividendStr [] = "dividend";
    int dividend = checkIfInt(dividendStr);
    printf("\n");

    char divisorStr [] = "divisor";
    int divisor = checkIfInt(divisorStr);
    printf("\n");

    properModulus(dividend, divisor);

    bool exitOrNo = continueOrNot();

    if(exitOrNo)
    {
      break;
    }
  }

  return 0;
}
