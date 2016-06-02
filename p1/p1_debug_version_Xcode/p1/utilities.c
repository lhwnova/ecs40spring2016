#include "utilities.h"
#include "flight.h"

int getNumber()
{
  char ch = getchar(), *numStr = NULL;
  
  if ((ch = skipLeadingWhite(ch)) && ch == '\n')
    return INVALID;
  ch = skipLeadingZero(ch);
  
  if(!isspace(ch))
  {
    if (isdigit(ch))
    {
      ch = getNumStr(ch, &(numStr));
      
      if (!allFollowingIsWhite(ch))
      {
        free(numStr);
        return skipAllTrailingChar(ch);
      } //if all the following is not whitespace
    } //if nextone is dight
    else //is nextone is nondight
      return skipAllTrailingChar(ch);
  } //if is not white space after it.
  else  // next one is whitespace or newline character
    if (allFollowingIsWhite(ch)) //if all the following is whitespace
      return 0;
    else //if all the following is not whtespace
      return INVALID;
  
  int num = strToint(numStr);
  free(numStr);
  return num;
} //get valid number that is not overflowed


char skipLeadingWhite(char ch)
{
  while(isspace(ch) && ch != NEWLINE_CHARACTER)
  {
    ch = getchar();
  } //continue getting char until whitespacees encounter
  
  return ch;
} //skip leading white


char skipLeadingZero(char ch)
{
  while(ch == ZERO_CHAR)
  {
    ch = getchar();
  } //continue getting char until first non-zero encounter
  
  return ch;
} //skip leading zeor


int allFollowingIsWhite(char ch)
{
  while (ch != NEWLINE_CHARACTER)
  {
    if (ch != WHITE_SPACE)
    {
      return 0;
    } //if it is not white space
    
    ch = getchar();
  } //iterate to the end
  
  return 1;
} //iterate to the end to see if it only contains whitespace


char getNumStr(char ch, char** numStr)
{
  int initial_size = INITIAL_NUM_SIZE, i = 0;
  int* buffer_size = &initial_size;
  *numStr = (char*) malloc(*buffer_size * sizeof(char));
  
  while (isdigit(ch))
  {
    (*numStr)[i] = ch;
    i++;
    
    if(i == *buffer_size)
    {
      increaseSize(&(*numStr), buffer_size);
    } //if the buffer size is met
    
    ch = getchar();
  } //keep getting the char until first nondight is met
  
  (*numStr)[i] = NULL_TERMINATOR;
  return ch;
} //get number in string format


void increaseSize(char** numStr, int* buffer_size)
{
  *buffer_size += SIZE_INCREASE;
  char* newNumStr = (char*) realloc(*numStr, *buffer_size * sizeof(char));
  *numStr = newNumStr;
} //if the size if full, increase its size


int strToint(char* numStr)
{
  int num = 0;
  int digit;
  
  for (int i = 0; i < (int)strlen(numStr); i++)
  {
    digit = numStr[i] - ZERO_CHAR;
    
    if (addWillCauseOverflow(num, digit))
    {
      return INVALID;
    } //if it will over flwo next
    
    num = DECIMAL * num + digit;
  } //iterate throught he string and get the integer number
  
  return num;
} //convert string to integer


int addWillCauseOverflow(int numA, int numB)
{
  if(numA > (INT_MAX - numB) / DECIMAL)
  {
    return 1;
  } //if numB > INT_MAX - numA
  else //if numB <= INT_MAX - numA
  {
    return 0;
  } //if numB <= INT_MAX - numA
} //to determine if adding two number will over flwo nex


void meun()
{
  printf("\nECS Flight Reservation Menu\n");
  printf("0. Exit.\n");
  printf("1. Add Passenger.\n");
} //print out ecs flight menu


int firstMeun(int* choice)
{
  printf("\nPlease enter your choice: ");
  *choice = getNumber();
  
  switch (*choice)
  {
    case EXIT:
      printf("Goodbye.\n");
      break;
    case CONTINUE:
      break;
    case INVALID:
      printf("Your choice is invalid.\n");
      printf("Please try again.\n");
      break;
    default:
      printf("%d is not an available choice.\n", *choice);
      printf("Please try again.\n");
      break;
  } // switch
  
  return *choice;
} // print the first meun

int skipAllTrailingChar (char ch)
{
  while(ch != NEWLINE_CHARACTER)
  {
    ch = getchar();
  } //keep getting char until meet the newline character
  
  return INVALID;
} //skip all the trailing chars