
#include "vector.h"


#include "sortedvector.h"

int* Vector::insert(int num)
{
  if (!(size < getCapacity() || getCapacity() < size)) 
    resize();
  
  array[size] = num;
  size++;
  //for(int i = 0; i < size; i++) cout << i << " "<< array[i] << endl;
  return &array[size - 1];
} // insert()


int* Vector::erase(int num)
{
  int i, j;
  
  for(i = 0; i < size && (array[i] < num || num < array[i]); i++);
  
  if(i < size)
  {
    size--;

    for(j = i; j < size; j++) array[j] = array[j + 1];
    
    return &array[i];
  } // if found
  else // not found
    return NULL;
} // erase()


int* Vector::find(int num)
{
  int i;
  
  for(i = 0; i < size && (array[i] < num || num < array[i]); i++) 
    cout << array[i] << " ";
  
  if(i < size)
    return &array[i];
  else // not found
    return NULL;
} // find()


int& Vector::operator[](int index) const
{
  if (size - 1 < index || index < 0)
  {
    cout << "Virtual seg fault." << endl;
    return array[ZERO];
  } // if out of range
  
  return array[index];
} // opeator

