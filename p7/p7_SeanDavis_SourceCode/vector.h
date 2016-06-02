#ifndef VECTOR_H
#define	VECTOR_H

#include <iostream>
using namespace std;

template <typename T>
class Vector;

template <typename T>
class VectorIterator
{
  Vector<T> *vectorPtr;
  int position;
public:
  static const int ERROR = -1;
  VectorIterator(Vector<T> *ptr = NULL, int pos = ERROR);
  VectorIterator<T>& operator++ (int);
  bool operator!= (const VectorIterator <T> &rhs);
  T& operator* ();
};  // class VectorIterator


template <typename T>
class ReverseVectorIterator
{
  Vector<T> *vectorPtr;
  int position;
public:
  static const int ERROR = -1;
  ReverseVectorIterator(Vector<T> *ptr = NULL, int pos = ERROR);
  ReverseVectorIterator<T>& operator++ (int);
  bool operator!= (const ReverseVectorIterator <T> &rhs);
  T& operator* ();
};  // class ReverseVectorIterator


template <typename T>
ostream& operator<< (ostream &os, const Vector<T> &v);

template <typename T>
class Vector 
{
  static const int RESIZE_FACTOR = 2;
  int count;
  int storage;
  T *array;
public:
  typedef VectorIterator<T> iterator; 
  typedef ReverseVectorIterator<T> reverse_iterator;
  friend class VectorIterator<T>;
  friend class ReverseVectorIterator<T>;
  Vector();
  Vector (const T *rhs);
  Vector(const Vector &rhs);
  ~Vector();
  int capacity() const;
  VectorIterator<T> begin();
  VectorIterator<T> end();
  size_t find(const Vector<T> &rhs) const;
  Vector<T>& insert(int start, const Vector <T> &vector);
  Vector<T>& operator= (const Vector<T> &rhs);
  Vector<T>& operator+= (const Vector<T> &rhs);
  friend ostream& operator<< <T> (ostream &os, const Vector<T> &v);
  Vector<T>& replace(int start, int length, const Vector <T> &vector, 
                     int subStart, int subLength);
  ReverseVectorIterator<T> rbegin();
  ReverseVectorIterator<T> rend();
  int size() const;
  Vector<T> substr(int start, int length);
}; // class vector 

#include "vector.cpp"
#endif	// VECTOR_H

