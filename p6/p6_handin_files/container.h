
#ifndef CONTAINER_H
#define CONTAINER_H

#include <iostream>

class Container
{
protected:
  static const int ZERO = 0;
  int size;
public:
  virtual int* insert(int num) = 0;
  virtual int* erase(int num) = 0;
  virtual int* find(int num) = 0;
  Container(int siz);
  int getSize() const;
  virtual ~Container();
}; // class container

#endif // CONTAINER_H
