// Author: Sean Davis
#include <iostream>
#include "container.h"
#include "sortedvector.h"

using namespace std;

SortedVector::SortedVector() : Container( 0 ), capacity( 0 ), array(NULL)
{
} // SortedVector()


SortedVector::~SortedVector()
{
  if(array)
    delete [] array;
} // SortedVector()


int* SortedVector::erase(int num)
{
  int i;
  
  for(i = 0; i < size && array[i] < num; i++);
  
  if(i < size && ! (num < array[i]) )
  {
    for(int j = i; j < size - 1; j++)
      array[j] = array[j + 1];
    
    size--;
  }  // if found
  else // not found
    return NULL;

  if(i < size)
    return &array[i];
  else // erased last item
    return NULL;
} // erase()


int* SortedVector::find(int num)
{
  int i;
  
  for(i = 0; i < size && array[i] < num; i++)
    cout << array[i] << ' ';
  
  if(i < size && ! (num < array[i]) )
    return &array[i];
  else // not found
    return NULL;
} // find()


int SortedVector::getCapacity()
{
  return capacity;
}  // getCapacity()  


int* SortedVector::insert(int num)
{
  int i;
  
  if(! (size <  capacity) && ! (capacity < size))
    resize();
  
  for(i = 0; i < size && array[i] < num; i++);
 
  if(i < size)
    for(int j = size; j > i; j--)
      array[j] = array[j - 1];
  
  array[i] = num;
  size++;
  return &array[i];
}  // insert()



const int& SortedVector::operator[] (int index) const
{
  if( ! (index < 0) && index < size)
    return array[index];
  else // index out of range
  {
    cout << "Virtual seg fault.\n";
    return array[ 0 ];
  }  // else bad index
}  // operator[] const



void SortedVector::resize()
{
  if( ! (capacity < 0) && ! (0 < capacity))
    array = new int[++capacity];
  else // not first resize
  {
    int *temp = array;
    array = new int[capacity *= RESIZE_FACTOR];

    for(int i = 0; i < size; i++)
      array[i] = temp[i];

    delete [] temp;
  }  // else resize other than first 
}  // resize()



