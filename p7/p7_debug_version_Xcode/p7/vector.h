// Author: Steven Li

#ifndef VECTOR_H
#define VECTOR_H

#include <iostream>
using namespace std;


template <typename T> 
class Vector;


template <typename T> 
class VectorIterator
{
private:
  const Vector<T>* vectorPtr;
  int position;
public:
  VectorIterator(const Vector<T>* vecPt = NULL, int pos = 0);
  VectorIterator<T>& operator++(int);
  bool operator!=(const VectorIterator<T>& rhs) const;
  const T& operator*() const;
}; // VectorIterator


template <typename T>
class ReverseVectorIterator
{
private:
  const Vector<T>* vectorPtr;
  int position;
public:
  ReverseVectorIterator(const Vector<T>* vecPt = NULL, int pos = 0);
  ReverseVectorIterator<T>& operator++(int);
  bool operator!=(const ReverseVectorIterator<T>& rhs) const;
  const T& operator*() const;
}; //ReverseVectorIterator


template <typename T>
ostream& operator<< (ostream& os, const Vector<T>& vector);


template <typename T> 
class Vector
{
private:
  int storage;
  int count;
  T* array;
public:
  static const int TWO = 2;
  static const int ERROR = -1;
  
  Vector();
  Vector(const T* arr);
  Vector(const Vector<T>& vector);
  ~Vector();
  
  friend VectorIterator<T>;
  friend ReverseVectorIterator<T>;
  friend ostream& operator<< <T>(ostream& os, const Vector<T>& vector);
  
  int capacity() const;
  int size() const;
  Vector<T>& operator=(const Vector<T>& vector);
  Vector<T>& operator+=(const Vector<T>& vector);
  size_t find(const Vector<T>& vector) const;
  Vector<T> substr(int start, int length) const;
  Vector<T>& insert(int start, const Vector<T>& vector);
  Vector<T>& replace(int start, int length, const Vector<T>& vector,
                     int subStart, int subLength);
  
  typedef VectorIterator<T> iterator;
  VectorIterator<T> end() const;
  VectorIterator<T> begin() const;
  
  typedef ReverseVectorIterator<T> reverse_iterator;
  ReverseVectorIterator<T> rend() const;
  ReverseVectorIterator<T> rbegin() const;
}; // class Vector


#include "vector.cpp"
#endif // VECTOR_H
