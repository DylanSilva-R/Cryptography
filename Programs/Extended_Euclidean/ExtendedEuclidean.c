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
      //printf("%d = %d * %d + %d\n", a, b, q, r);

    }else if(a < 0 && b > 0) // Third, check for a negative -a input and +b input and +a and -b inputs.
    {
      newQ = a / b;
      newQ = newQ + -1;
      newP = newQ * b;
      newR = a - newP;

      holdAnswers[0] = newQ;
      holdAnswers[1] = newR;

      //printf("%d = %d * %d + %d\n", a, b, newQ, newR);
    }else if(a < 0 && b < 0) // Fourth, check for -a and -b input.
    {
      newQ = a / b;
      newQ = abs(newQ);
      newQ = newQ + 1;

      newP = newQ * b;
      newR = a - newP;

      holdAnswers[0] = newQ;
      holdAnswers[1] = newR;

      //printf("%d = %d * %d + %d\n", a, b, newQ, newR);
    }

    return holdAnswers;
  }
}

int euclidean(int a, int b)
{
  // Division values =
  int * answers = properModulus(a, b);
  int quotient = answers[0];
  int remainder = answers[1];

  if(remainder == 0)
  {
    return b;
  }else
  {
    return euclidean(b, remainder);
  }
}

void extendedEuclidean(int a, int b, int s1, int s2, int t1, int t2)
{
  int * answers = properModulus(a, b);
  int quotient = answers[0];
  int remainder = answers[1];
  int s = s1 - s2 * quotient;
  int t = t1 - t2 * quotient;
  if(remainder == 0)
  {
    int gcdOut = euclidean(originalA, originalB);
    printf("GCD(%d, %d) = %d\n", originalA, originalB, b);
    printf("Multiplictive inverse: %d = (%d * %d) + (%d * %d)\n", b, originalA, s2, originalB, t2);
    return;
  }else
  {
    printf("a = %d, b = %d, q = %d, r = %d, s1 = %d, s2 = %d, s = %d, t1 = %d, t2 = %d, t = %d\n", a, b, quotient, remainder, s1, s2, s, t1, t2, t);
    extendedEuclidean(b, remainder, s2, s, t2, t);
  }
}

void menu()
{
  printf("1) Input your a value\n");
  printf("2) Input your b value\n");
  printf("3) Calculate multiplictive inverse\n");
  printf("4) Exit\n");
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
      break;
    }
  }

  return userNumInput;
}

int main()
{
  printf("_____________________________\n");
  printf("|Extended Euclidean Algorithm|\n");
  printf("|____________________________|\n");
  printf("By: Dylan Silva-Rivas\n");

  bool mainLoop = true;
  int s1 = 1;
  int s2 = 0;
  int t1 = 0;
  int t2 = 1;

  while(mainLoop)
  {
    printf("\n");
    menu();

    printf("Input a menu option: ");
    int menuOption = checkIfInt();

    if(menuOption == 1)
    {
      printf("Input your a value: ");
      originalA = checkIfInt();
      ptrA = &originalA;

    }else if(menuOption == 2)
    {
      printf("Input your b value: ");
      originalB = checkIfInt();
      ptrB = &originalB;
    }else if(menuOption == 3)
    {
      if(ptrA == NULL || ptrB == NULL)
      {
        printf("It seems like you haven't inputted an a or b value yet. Please try again.\n");
      }else
      {
        extendedEuclidean(originalA, originalB, s1, s2, t1, t2);
      }

    }else if(menuOption == 4)
    {
      mainLoop = false;
    }else
    {
        printf("It seems like your input is out of bounds. Please try again.\n");
    }
  }

  return 0;
}
