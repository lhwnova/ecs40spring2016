// Author: Sean Davis
#include <iostream>
#include "vector.h"

using namespace std;

template <typename T>
VectorIterator<T>::VectorIterator(Vector<T> *ptr, int pos) : vectorPtr(ptr),
  position(pos)
{
}  // VectorIterator()



template <typename T>
T& VectorIterator<T>::operator* ()
{
  return vectorPtr->array[position];
}  // operator*


template <typename T>
VectorIterator<T>& VectorIterator<T>::operator++ (int)
{
  if(++position >= vectorPtr->count)
    position = ERROR;
  
  return *this;
}  // operator++


template <typename T>
bool VectorIterator<T>::operator!= (const VectorIterator <T> &rhs)
{
  return vectorPtr != rhs.vectorPtr || position != rhs.position;
}  // operator !=


template <typename T>
ReverseVectorIterator<T>::ReverseVectorIterator(Vector<T> *ptr, int pos) : 
  vectorPtr(ptr), position(pos)
{
}  // ReverseVectorIterator()



template <typename T>
T& ReverseVectorIterator<T>::operator* ()
{
  return vectorPtr->array[position];
}  // operator*


template <typename T>
ReverseVectorIterator<T>& ReverseVectorIterator<T>::operator++ (int)
{
  if(--position < 0)
    position = ERROR;
  
  return *this;
}  // operator++


template <typename T>
bool ReverseVectorIterator<T>::operator!= (const ReverseVectorIterator <T> &rhs)
{
  return vectorPtr != rhs.vectorPtr || position != rhs.position;
}  // operator !=



template <typename T>
Vector<T>::Vector():count( 0 ), storage( 0 ), array(NULL)
{
} // Vector()


template <typename T>
Vector<T>::Vector(const Vector<T> &rhs):count(rhs.count), storage(rhs.storage)
{
  array = new T[storage];
  
  for(int i = 0; i < count; i++)
    array[i] = rhs.array[i];
} // Vector(Vector&)



template <typename T>
Vector<T>::Vector (const T *rhs)
{
  for(count = 0; rhs[count] != 0; count++);

  array = new T[count];
  storage = count;
  
  for(int i = 0; i < count; i++)
    array[i] = rhs[i];
  
} // Vector(T*)


template <typename T>
Vector<T>::~Vector()
{
  if(array)
    delete [] array;
} // ~Vector



template <typename T>
VectorIterator<T> Vector<T>::begin()
{
  return VectorIterator<T>(this, 0);
}  // begin()


template <typename T>
VectorIterator<T> Vector<T>::end()
{
  return VectorIterator<T>(this, VectorIterator<T>::ERROR);
}  // begin()


template <typename T>
size_t Vector<T>::find(const Vector<T> &rhs) const
{
  int i, j;
  
  for(i = 0; i <= count - rhs.count; i++)
  {
    for(j = 0; j < rhs.count && rhs.array[j] == array[i + j] ; j++);
    
    if(j == rhs.count)
      return i;
  } // for i
  
  return (size_t) - 1;  // LLONG_MAX; // INT_MAX;
}  // find()





template <typename T>
Vector<T>& Vector<T>::insert(int start, const Vector <T> &vector)
{

  
  if(count + vector.count > storage)
  {
    while(storage < count + vector.count)
      storage *= RESIZE_FACTOR;
    
    T *temp = array;
    array = new T[storage];
    
    for(int i = 0; i < count; i++)
      array[i] = temp[i];
    
    delete [] temp;
  }  // if new count not storage

  for(int i = count + vector.count - 1; i >= start; i--)
    array[i] = array[i - vector.count];

  for(int i = 0; i < vector.count; i++)
    array[start + i] = vector.array[i];
  
  count += vector.count;
  return *this;
}  // insert()


template <typename T>
Vector<T>& Vector<T>::operator= (const Vector<T> &rhs)
{
  if(this == &rhs)
    return *this;
  
  if(storage != rhs.count)
  {
    delete [] array;
    storage = count = rhs.count;
    array = new T[storage];
  } // if storage not the same.
  
  for(int i = 0; i < count; i++)
    array[i] = rhs.array[i];
  
  return *this;  
} // operator=


template <typename T>
Vector<T>& Vector<T>::operator+= (const Vector <T> &rhs)
{
  if(count + rhs.count > storage)
  {
    T *temp = array;
     
    if(rhs.count <= count)
      storage = storage * RESIZE_FACTOR;
    else // greater than double the storage
      storage = count + rhs.count;

    array = new T[storage];
    
    for(int i = 0; i < count; i++)
      array[i] = temp[i];
    
    delete [] temp;
  }  // if new count not storage
  
  for(int i = 0; i < rhs.count; i++)
    array[i + count] = rhs.array[i];
  
  count += rhs.count;

   return *this;  
} // operator+=


template <typename T>
int Vector<T>::capacity() const
{
  return storage;
} // capacity()


template <typename T>
ostream& operator<< (ostream &os, const Vector<T> &v)
{
  for(int i = 0; i < v.count; i++)
    cout << v.array[i];
  return os;
}  // operator<<

 
template <typename T>
Vector<T>& Vector<T>::replace(int start, int length, const Vector <T> &vector, 
                              int subStart, int subLength)
{
  int thirdStart = start + length, newCount = count - length + subLength;
  T *temp = array;
 
  if(newCount > storage)
  {
    if(newCount <=  RESIZE_FACTOR * storage)
      storage *= RESIZE_FACTOR;
    else // newCount > RESIZE_FACTOR * storage 
        storage = newCount;

    array = new T[storage];

    for(int i = 0; i < start; i++)
      array[i] = temp[i];
      
    for(int i = start + subLength; i < newCount; i++)
      array[i] = temp[thirdStart++];

    delete temp;
  } // if storage must be resized
  else // storage large enough
    if(newCount < count) // shrinking so moving array to left
      for(int i = start + subLength; i < newCount; i++)
        array[i] = array[thirdStart++]; 
    else // enlarging so moving array to right
      for(int i = newCount - 1; i >= start + subLength; i--)
        array[i] = array[--count];

  for(int i = 0; i < subLength; i++)
    array[start + i] = vector.array[i + subStart];
  
  count = newCount;
  return *this;
}  // replace()
 
template <typename T>
ReverseVectorIterator<T> Vector<T>::rbegin()
{
  return ReverseVectorIterator<T>(this, count - 1);
}  // begin()


template <typename T>
ReverseVectorIterator<T> Vector<T>::rend()
{
  return ReverseVectorIterator<T>(this, ReverseVectorIterator<T>::ERROR);
}  // begin()

 
template <typename T>
int Vector<T>::size() const
{
  return count;
} // size()


template <typename T>
Vector<T> Vector<T>::substr(int start, int length)
{
  Vector<T> temp;
  
  temp.array = new T[length];
  temp.count = temp.storage = length;
  
  for(int i = 0; i < length; i++)
    temp.array[i] = array[start + i];
  
  return temp;
} // substr()
