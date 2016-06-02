// Author: Sean Davis
#include <iostream>
#include "vector.h"

using namespace std;


int* Vector::erase(int num)
{
  int i;
  
  for(i = 0; i < size && (array[i] < num || array[i] > num); i++);
  
  if(i < size)
  {
    for(int j = i; j < size - 1; j++)
      array[j] = array[j + 1];
    
    size--;
  }  // if found
  else  // not found
    return NULL;

  if(i < size)
    return &array[i];
  else // erased last value
    return NULL;
} // erase()


int* Vector::find(int num)
{
  int i;
  
  for(i = 0; i < size && (array[i] < num || num < array[i]); i++)
    cout << array[i] << ' ';
  
  if(i < size)
    return &array[i];
  else // not found
    return NULL;
} // find()


int* Vector::insert(int num)
{
  if(! (size <  getCapacity()))
    resize();
  
  array[size++] = num;
  return &array[size - 1];
}  // insert()


int& Vector::operator[](int index)
{
  if(index >= 0 && index < size)
    return array[index];
  else // index out of range
  {
    cout << "Virtual seg fault.\n";
    return array[ 0 ];
  }  // else bad index
} // operator[] non-const


