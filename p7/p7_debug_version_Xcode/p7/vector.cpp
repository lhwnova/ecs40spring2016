// Author: Steven Li

#include "vector.h"

template <typename T> 
int Vector<T>::capacity() const
{
  return storage;
} // capacity()


template <typename T> 
int Vector<T>::size() const
{
  return count;
} // size()


template <typename T>
ostream& operator<<(ostream& os, const Vector<T>& vector)
{
  for(int i = 0; i < vector.size(); i++) os << vector.array[i];
  
  return os;
} // operator << 


template <typename T>
Vector<T>::Vector() : storage( 0 ), count( 0 ), array(NULL)
{
} // Vector() default


template <typename T>
Vector<T>::~Vector()
{
  if(array)
    delete [] array;
} // ~Vector()


template <typename T>
Vector<T>::Vector(const T* arr)
{
  for(count = 0; arr[count] != '\0'; count++);
  
  storage = count;
  array = new T[storage];

  for(int i = 0; i < count; i++)
    array[i] = arr[i];
} // Vector(arr) standard


template <typename T>
Vector<T>& Vector<T>::operator=(const Vector<T>& vector)
{
  if(this != &vector)
  {
    count = vector.size();
    storage = vector.capacity();
    
    if(array)
      delete [] array;
    
    array = new T[storage];
    
    for(int i = 0; i < count; i++)
      array[i] = vector.array[i];
  } // if it is not assigning itself
  
  return *this;
} // Vector<T>::operator=()


template <typename T>
Vector<T>& Vector<T>::operator+=(const Vector<T>& vector)
{
  int changedLength = vector.size();
  int newCount = count + changedLength;
  
  if(newCount > storage && newCount < TWO * storage)
    storage *= TWO;
  else // storage is two times more bigger
    if (newCount > TWO * storage)
      storage = newCount;
  
  T* temp = new T[storage];
  int i;

  for(i = 0; i < count; i++)
  	temp[i] = array[i];

  for(i = count; i < newCount; i++)
    temp[i] = vector.array[i - count];

  if(array)
    delete [] array;

  array = temp;
  count = newCount;
  return *this;
} // Vector<T>::operator+=()


template <typename T>
size_t Vector<T>::find(const Vector<T>& vector) const
{
  int i, j; bool found;
  
  if(vector.size() <= count) // if the one to be finded is legal, not longer
    for(i = 0; i < count - vector.size() + 1; i++)
    {
      found = true;
      
      for(j = 0; j < vector.size(); j++)
        if (array[i + j] != vector.array[j])
        {
          found = false;
          break;
        } // fi
      
      if(found)
        return (size_t) i;
    } // nested loop
  
  return (size_t) ERROR;
} // find()


template <typename T>
Vector<T> Vector<T>::substr(int start, int length) const
{
  Vector<T> temp;
  temp.count = length;
  temp.storage = length;
  temp.array = new T[temp.storage];
  
  for(int i = 0; i < temp.count; i++)
    temp.array[i] = array[i + start];
  
  return temp;
} // substr()


template <typename T>
Vector<T>::Vector(const Vector<T>& vector) :
  storage(vector.capacity()), count(vector.size())
{
  array = new T[vector.capacity()];
  
  for(int i = 0; i < vector.size(); i++)
    array[i] = vector.array[i];
} // Vector() copy


template <typename T>
Vector<T>& Vector<T>::insert(int start, const Vector<T>& vector)
{
  int newCount = count + vector.size();
  
  if(newCount > storage && newCount < TWO * storage)
    storage *= TWO;
  else // storage is two times more bigger
    if (newCount > TWO * storage)
      storage = newCount;
  
  T* temp = new T[storage];
  
  for(int i = 0; i < count; i++)
    temp[i] = array[i];
  
  delete [] array;
  array = temp;
  
  for(int i = newCount - 1; i > start - 1; i--)
    array[i] = array[i - vector.size()];
  
  for(int i = 0; i < vector.size(); i++)
    array[i + start] = vector.array[i];
  
  count = newCount; return *this;
} // insert()


template <typename T> Vector<T>& Vector<T>::replace
(int start, int length, const Vector<T>& vector, int subStart, int subLength)
{
  int newCount = count - length + subLength;
  
  if (newCount <= count)
  {
    for(int i = start + subLength; i < newCount; i++)
      array[i] = array[i + subLength];
    
  } // if it is shrink
  else // if it is not shrink
  {
    if(newCount > storage && newCount < TWO * storage)
      storage *= TWO;
    else // storage is two times more bigger
      if (newCount > TWO * storage)
        storage = newCount;
    
    T* temp = new T[storage];
    
    for(int i = 0; i < count; i++) temp[i] = array[i];
    
    delete [] array; array = temp;
    
    for(int i = newCount - 1; i > start + subLength - 1; i--)
      array[i] = array[i - (subLength - length)];

  } // it is not shrink

  for(int i = 0; i < subLength; i++)
    array[i + start] = vector.array[i + subStart];

  count = newCount; return *this;
} // replace()


template <typename T> 
VectorIterator<T>::VectorIterator(const Vector<T>* vecPt, int pos)
  : vectorPtr(vecPt), position(pos)
{
} // VectorIterator()


template <typename T>
ReverseVectorIterator<T>::ReverseVectorIterator(const Vector<T>* vecPt, int pos)
  : vectorPtr(vecPt), position(pos)
{
} // ReverseVectorIterator()


template <typename T> 
VectorIterator<T> Vector<T>::end() const
{
  return VectorIterator<T>(this, ERROR);
} // end()


template <typename T> 
VectorIterator<T> Vector<T>::begin() const
{
  return VectorIterator<T>(this, 0);
} // begin()


template <typename T>
ReverseVectorIterator<T> Vector<T>::rend() const
{
  return ReverseVectorIterator<T>(this, ERROR);
} // rend()


template <typename T>
ReverseVectorIterator<T> Vector<T>::rbegin() const
{
  return ReverseVectorIterator<T>(this, count - 1);
} // rbegin()


template <typename T> 
VectorIterator<T>& VectorIterator<T>::operator++(int)
{
  if(position < vectorPtr->size() - 1)
    position++;
  else // at the end
    position = Vector<T>::ERROR;
  
  return *this;
} // VectorIterator<T>::operator++()


template <typename T>
ReverseVectorIterator<T>& ReverseVectorIterator<T>::operator++(int)
{
  position--; // if it at zero, it will be minus one next
  return *this;
} // ReverseVectorIterator<T>::operator++()


template <typename T> 
bool VectorIterator<T>::operator!=(const VectorIterator<T>& rhs) const
{
  return(vectorPtr != rhs.vectorPtr || position != rhs.position);
} // VectorIterator<T>::operator!=()


template <typename T>
bool ReverseVectorIterator<T>::operator!=
  (const ReverseVectorIterator<T>& rhs) const
{
  return(vectorPtr != rhs.vectorPtr || position != rhs.position);
} // ReverseVectorIterator<T>::operator!=()


template <typename T>
const T& VectorIterator<T>::operator*() const
{
  return vectorPtr->array[position];
} // VectorIterator<T>::operator*()


template <typename T>
const T& ReverseVectorIterator<T>::operator*() const
{
  return vectorPtr->array[position];
} // ReverseVectorIterator<T>::operator*()
