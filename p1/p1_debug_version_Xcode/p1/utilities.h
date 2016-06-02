#ifndef UTILITIES_H
#define UTILITIES_H
#define INITIAL_NUM_SIZE 10
#define SIZE_INCREASE 2
#define DECIMAL 10
#define NEWLINE_CHARACTER '\n'
#define WHITE_SPACE ' '
#define NULL_TERMINATOR '\0'
#define ZERO_CHAR '0'

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <limits.h>
#include <string.h>

int getNumber();
char skipLeadingWhite(char ch);
char skipLeadingZero(char ch);
int allFollowingIsWhite(char ch);
char getNumStr(char ch, char** numStr);
void increaseSize(char** numStr, int* buffer_size);
int strToint(char* numStr);
int addWillCauseOverflow(int numA, int numB);
void meun();
int firstMeun(int* choice);
int skipAllTrailingChar (char ch) ;

#endif
