#include "list.h"
#include "food.h"

using namespace std;

template <class T>
ListNode<T>::ListNode(T &d, ListNode<T> *p, ListNode<T> *n) : data(d), prev(p), next(n)
{
  
}

template <class T>
List<T>::List():head(NULL)
{
  
}

template <class T>
void List<T>::insert(T data)
{
  ListNode<T> *ptr, *prev = NULL;
  
  
  for(ptr = head; ptr && (data->getName() < ptr->data->getName()); ptr = ptr->next)
    prev = ptr;
  
  if(!prev)
  {
    head = new ListNode<T>(data, prev, ptr);
    
    if(ptr)
      ptr->prev = head;
  }
  else
  {
    prev->next = new ListNode<T>(data, prev, ptr);
    
    if(ptr)
      ptr->prev = prev->next;
  }
}


template <class T>
const T List<T>::find(const ListNode<T> *ptr, const string &foodName) const
{
  if(ptr == NULL)
    return NULL;
  
  if(ptr->data->getName() == foodName)
    return ptr->data;
  
  return find(ptr->next, foodName);
}

template <class T>
const T List<T>::findFood(const string &foodName) const
{
  return find(head, foodName);
}

template <class T>
List<T>::~List()
{
  for(ListNode<T>* ptr = head; ptr; ptr = head)
  {
    head = ptr->next;
    delete ptr;
  }
}