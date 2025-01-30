#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdbool.h>



int originalA;
int originalB;
int * ptrA = NULL;
int * ptrB = NULL;

int * properModulus(int a, int b)
{
  int * holdAnswers = (int*)malloc(2 * sizeof(int));
  int r;
  int q;
  int newQ;
  int newP;
  int newR;

  // First, check for 0 value inputs.

  if(b == 0 || (a == 0 && b == 0))
  {
    printf("Result is undefined\n");
    exit(1);
  }else
  {
    if(a >= 0 && b > 0 || a > 0 && b < 0) // Second, check for positive inputs.
    {
      r = a % b;
      q = a / b;
      holdAnswers[0] = q;
      holdAnswers[1] = r;
      printf("%d = %d * %d + %d\n", a, b, q, r);

    }else if(a < 0 && b > 0) // Third, check for a negative -a input and +b input and +a and -b inputs.
    {
      newQ = a / b;
      newQ = newQ + -1;
      newP = newQ * b;
      newR = a - newP;

      holdAnswers[0] = newQ;
      holdAnswers[1] = newR;

      printf("%d = %d * %d + %d\n", a, b, newQ, newR);
    }else if(a < 0 && b < 0) // Fourth, check for -a and -b input.
    {
      newQ = a / b;
      newQ = abs(newQ);
      newQ = newQ + 1;

      newP = newQ * b;
      newR = a - newP;

      holdAnswers[0] = newQ;
      holdAnswers[1] = newR;

      printf("%d = %d * %d + %d\n", a, b, newQ, newR);
    }

    return holdAnswers;
  }
}

int checkIfInt()
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

    scanf("%s", input);

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

      if(userNumInput < 0)
      {
        userNumInput = abs(userNumInput);
      }

      break;
    }
  }

  return userNumInput;
}

void euclidean(int a, int b)
{
  // Division values =
  int * answers = properModulus(a, b);
  int quotient = answers[0];
  int remainder = answers[1];

  if(remainder == 0)
  {
    printf("GCD(%d, %d) = %d\n", originalA, originalB, b);
    return;
  }else
  {
    euclidean(b, remainder);
  }

}

void menu()
{
  printf("1) Input a\n");
  printf("2) Input b\n");
  printf("3) Calculate GCD\n");
  printf("4) Exit Program\n");
}

int main()
{
  printf("_____________________\n");
  printf("|Euclidean Algorithm|\n");
  printf("|___________________|\n");
  printf("By: Dylan Silva-Rivas\n");
  /*
  * RULES:
  *   - Must accept postive and negative integers.
  *   - Zero inputs must be correct.
  *   - Inputs a and b must fulfill |a| < |b|
  *   - gcd(a, b) == gcd(|a|, |b|)
  */

  bool mainLoop = true;

  while(mainLoop)
  {
    printf("\n");
    menu();

    printf("Menu choice: ");
    int menuChoice = checkIfInt();
    printf("\n");

    if(menuChoice == 1)
    {
      printf("Input your a value: ");
      originalA = checkIfInt();
      ptrA = &originalA;
    }else if(menuChoice == 2)
    {
      printf("Input your b value: ");
      originalB = checkIfInt();
      ptrB = &originalB;
    }else if(menuChoice == 3)
    {
      if(ptrA == NULL || ptrB == NULL)
      {
        printf("You didn't create an a or b value. Please try again.");
      }else
      {
        printf("Calculating GCD(%d, %d)\n", originalA, originalB);

        if(originalB > originalA)
        {
          euclidean(originalB, originalA);
        }else
        {
          euclidean(originalA, originalB);
        }
      }

    }else if(menuChoice == 4)
    {
      mainLoop = false;
    }
  }

  return 0;
}
