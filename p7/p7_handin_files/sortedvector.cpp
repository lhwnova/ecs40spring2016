
#include "sortedvector.h"

int* SortedVector::insert(int num)
{
  if(!(size < capacity || capacity < size)) // if size equal to capacity
    resize();
  
  int i, j;
  
  for(i = 0; i < size && array[i] < num; i++);
  
  if(i < size) // if it does not go to the end of the list
    for(j = size; j > i; j--) array[j] = array[j - 1];
  
  array[i] = num;
  size++;
  return &array[i];
} // insert()


int* SortedVector::erase(int num)
{
  int i, j;
  
  for(i = 0; i < size && array[i] < num; i++);
  
  if(i < size && !(array[i] < num || num < array[i]))
  {
    size--;

    for(j = i; j < size; j++) array[j] = array[j + 1];
    
    return &array[i];
  } // if found 
  else // not found
    return NULL;
} // erase()


int* SortedVector::find(int num)
{
  int i;
  
  for(i = 0; i < size && array[i] < num; i++) cout << array[i] << " ";
  
  if(i < size && !(array[i] < num || num < array[i]))
    return &array[i];
  else // not found
    return NULL;
} // find()


void SortedVector::resize()
{
  if (!capacity) // if capacity is originally zero
    capacity = 1;
  else  //if capcity is not originally zero
    capacity *= TWO;
  
  int* temp = new int[capacity];
  
  for(int i = 0; i < size; i++) temp[i] = array[i];
  
  delete [] array;
  
  array = temp;
} // resize()


SortedVector::~SortedVector()
{
  delete [] array;
} // ~SortedVector


const int& SortedVector::operator[](int index) const
{
  if (size - 1 < index || index < 0)
  {
    cout << "Virtual seg fault." << endl;
    return array[ZERO];
  } // if out of range
  
  return array[index];
} // operator


int SortedVector::getCapacity() const
{
  return capacity;
} // getCapacity

