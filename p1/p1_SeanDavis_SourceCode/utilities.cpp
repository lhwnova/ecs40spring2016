// Author: Sean Davis

#include <ctype.h>
#include <stdio.h>
#include <limits.h>
#include "utilities.h"

#define TEN 10
#define ASCII_ZERO '0'

int getNumber()
{
  long long number = 0, OK = 1;
  char c;

  for(c = getchar(); isspace(c) && c != '\n'; c = getchar());

  if(isdigit(c))
  {
    do
    {
      number = number * TEN + c - ASCII_ZERO;
      c = getchar();
    }  while(isdigit(c) && number <= INT_MAX);

    while(c != '\n' && isspace(c))
      c = getchar();

    if(c != '\n' || number > INT_MAX)
      OK = 0;
  }  // if first non-space is a digit
  else // first non-space is not a digit
    OK = 0;  // false

  while(c != '\n')
    c = getchar();
    
  if(OK)
    return number;
  else  // invalid number
    return ERROR;
  
} // getNumber()

