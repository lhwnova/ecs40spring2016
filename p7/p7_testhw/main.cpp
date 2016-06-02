// Author: Sean Davis 
// Created on May 10, 2016, 9:49 AM
#include <string>
#include <iostream>
#include <fstream>
// #include "vector.h"
using namespace std;
const int ARRAY_SIZE = 200;

void charsToInts(const char s[ARRAY_SIZE], int nums[ARRAY_SIZE])
{
  int i;
  
  for(i = 0; s[i] != '\0'; i++)
    nums[i] = s[i] + 500;
  
  nums[i] = 0;  // adding sentinel terminator
}  // charsToInts

int main(int argc, char** argv) 
{
  string str, str2;
  char operation, s[ARRAY_SIZE];
  int nums[ARRAY_SIZE], start, length, subStart, subLength;
  string::iterator sitr;
  string::reverse_iterator sRitr;
//  Vector<char>::iterator vcItr;
//  Vector<int>::iterator viItr;
//  Vector<char>::reverse_iterator vcRitr;
//  Vector<int>::reverse_iterator viRitr;
  Vector<char> vectorC, vectorC2;
  Vector<int> vectorI, vectorI2;
  ifstream inf(argv[1]);
  
  while(inf >> operation)
  {
    switch(operation)
    {
      case 'A' :
        cout << "\nAssignment operator:\n";
        inf.getline(s, ARRAY_SIZE);
        charsToInts(s, nums);
        str = str2 = s;
        str = str;
        cout << str.size() << ' ' << str.capacity() << ' ' << str << endl;
        vectorC = vectorC2 = s;
        vectorC = vectorC;
        cout << vectorC.size() << ' ' << vectorC.capacity() << ' ' << vectorC << endl;
        vectorI =  vectorI2 = nums;
        vectorI = vectorI;
        cout << vectorI.size() << ' ' << vectorI.capacity() << ' ' << vectorI << endl;
        break;
      case '+' :
        cout << "+= operator:\n";
        inf.getline(s, ARRAY_SIZE);
        charsToInts(s, nums);
        str += s;
 //       vectorC += s;
 //       vectorI += nums;
        cout << str.size() << ' ' << str.capacity() << ' ' << str << endl;
        cout << vectorC.size() << ' ' << vectorC.capacity() << ' ' << vectorC << endl;
        cout << vectorI.size() << ' ' << vectorI.capacity() << ' '  << vectorI << endl;
        break;
      case 'F' :
        cout << "\nFind:\n";
        inf.getline(s, ARRAY_SIZE);
        charsToInts(s, nums);
        cout << str.find(s) << endl;
//        cout << vectorC.find(s) << endl;
//        cout << vectorI.find(nums) << endl;
        break;
      case 'S' :
        cout << "\nSubstring:\n";
        inf >> start >> length;
        str2 = str.substr(start, length);
//        vectorC2 = vectorC.substr(start, length);
//        vectorI2 =  vectorI.substr(start, length);
        cout << str2 << endl;
        cout << vectorC2 << endl;
        cout << vectorI2 << endl;
        break;
      case 'I' :
        cout << "\nInsert:\n";
        inf >> start;
        inf.getline(s, ARRAY_SIZE);
        charsToInts(s, nums);
        str.insert(start, s);
 //       vectorC.insert(start, s);
 //       vectorI.insert(start, nums);
        cout  << str.size() << ' ' << str.capacity() << ' '  << str <<endl;
        cout  << vectorC.size() << ' ' << vectorC.capacity() << ' ' <<  vectorC << endl;
        cout  << vectorI.size() << ' ' << vectorI.capacity() << ' ' << vectorI << endl;
        break;
      case 'R' :
        cout << "\nReplace:\n";
        inf >> start >> length >> subStart >> subLength;
        inf.getline(s, ARRAY_SIZE);
        charsToInts(s, nums);
        str.replace(start, length, s, subStart, subLength);
//        vectorC.replace(start, length, s, subStart, subLength);
//        vectorI.replace(start, length, nums, subStart, subLength);
        cout << str.size() << ' ' << str.capacity() << ' ' << str << endl;
        cout << vectorC.size() << ' ' << vectorC.capacity() << ' ' << vectorC << endl;
        cout  << vectorI.size() << ' ' << vectorI.capacity() << ' ' << vectorI << endl;
        break;
      case 'L' :
        cout << "\nForward iterator:\n";
        for(sitr = str.begin(); sitr != str.end(); sitr++)
          cout << *sitr;
        
        cout << endl;
        
//        for( vcItr = vectorC.begin(); vcItr != vectorC.end(); vcItr++)
//          cout << *vcItr;
        
        cout << endl;
        
//        for( viItr = vectorI.begin(); viItr != vectorI.end(); viItr++)
//          cout << *viItr;
        
        cout << endl;
       
        break;
      case 'M' :
        cout << "\nReverse iterator:\n";
        for(sRitr = str.rbegin(); sRitr != str.rend(); sRitr++)
          cout << *sRitr; 
        
        cout << endl;
        
//        for( vcRitr = vectorC.rbegin(); vcRitr != vectorC.rend(); vcRitr++)
//          cout << *vcRitr;
        
        cout << endl;
        
//        for( viRitr = vectorI.rbegin(); viRitr != vectorI.rend(); viRitr++)
//          cout << *viRitr;
        
        cout << endl;
        break;
    } // switch
  }  // while more in file
  return 0;
} // main())

