
#ifndef VECTOR_H
#define VECTOR_H

#include <iostream>
#include "sortedvector.h"

class Vector:public SortedVector
{
public:
  int* insert(int num);
  int* erase(int num);
  int* find(int num);
  int& operator[](int index);
}; // class Vector

#endif // VECTOR_H
