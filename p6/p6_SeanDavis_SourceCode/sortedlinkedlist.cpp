// Author: Sean Davis

#include <iostream>
#include "sortedlinkedlist.h"

using namespace std;


int* SortedLinkedList::erase(int num)
{
  ListNode *prev = NULL;
  int *ptr;
  
  for(curr = head; curr && curr->data < num; curr = curr->next)
    prev = curr;
  
  if(!curr || num < curr->data)
    return NULL;
  
  size--;
  
  if(prev)
    prev->next = curr->next;
  else // erasing first node
    head = curr->next;
  
  if(curr->next)
  {
    curr->next->previous = prev;
    ptr = &curr->next->data;
  } // if something after num
  else // erased last node
    ptr = NULL;
      
  delete curr;
  
  return ptr;
}  // erase()


int* SortedLinkedList::find(int num)
{
  for(curr = head; curr && curr->data < num; curr = curr->next)
    cout << curr->data << ' ';
  
  if( !curr || num < curr->data)
    return NULL;
  
  return &curr->data;
}  // find()


int* SortedLinkedList::insert(int num)
{
  ListNode *prev = NULL;
  int *iptr;
  
  for(curr = head; curr && curr->data < num; curr = curr->next)
    prev = curr;
  
  if(prev)
  {
    prev->next = new ListNode(num, prev, curr);
    iptr = &prev->next->data;
    
    if(curr )
      curr->previous = prev->next;

    curr = prev->next;
  } // if not front of list
  else  // front of list
  {
    head = new ListNode(num, NULL, curr);
    iptr = &head->data;
    
    if(curr)
      curr->previous = head;

    curr = head;
  } // else front of list
  
  if(!tail)
    tail = head;

  size++;
  return iptr;
}  // insert()

