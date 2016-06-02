#ifndef VECTOR_H
#define	VECTOR_H
#include "sortedvector.h"

class Vector : public SortedVector
{
public:
  int* erase(int num);
  int* find(int num);
  int* insert(int num);
  int& operator[] (int index);
}; // class Vector 

#endif	// VECTOR_H


