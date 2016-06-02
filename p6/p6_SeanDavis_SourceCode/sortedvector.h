#ifndef SORTEDVECTOR_H
#define	SORTEDVECTOR_H
#include "container.h"

class SortedVector : public Container
{
  static const int RESIZE_FACTOR = 2;
  int capacity;
protected:
  int *array;
  void resize();
public:
  SortedVector();
  ~SortedVector();
  virtual int* erase(int num);
  virtual int* find(int num);
  int getCapacity();
  virtual int* insert(int num);
  const int& operator[] (int index) const;
}; // class Vector 

#endif	// VECTOR_H


