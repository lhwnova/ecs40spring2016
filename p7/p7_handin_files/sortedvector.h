
#ifndef SORTEDVECTOR_H
#define SORTEDVECTOR_H

#include <iostream>
#include "container.h"

using namespace std;

class Container;

class SortedVector:public Container
{
private:
  int capacity;
protected:
  static const int TWO = 2;
  int* array;
  void resize();
public:
  int getCapacity() const;
  SortedVector():Container(ZERO), capacity(ZERO), array(NULL){};
  virtual int* insert(int num);
  virtual int* erase(int num);
  virtual int* find(int num);
  ~SortedVector();
  const int& operator[](int index) const;
}; // class SortedVector

#endif // SORTEDVECTOR_H
