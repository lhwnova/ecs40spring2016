// Author: Sean Davis

#include <iostream>
#include "linkedlist.h"

using namespace std;


ListNode::ListNode(int d, ListNode *p, ListNode *n) : data(d), previous(p),
  next(n)
{
}  // ListNode


LinkedList::LinkedList() : Container( 0 ), head(NULL), tail(NULL), curr(NULL)
{
} // LinkedList()


LinkedList::~LinkedList()
{
  for(curr = head; curr; curr = head)
  {
    head = curr->next;
    delete curr;
  }  // for every ListNode
}  // ~LinkedList()


int* LinkedList::erase(int num)
{
  ListNode *prev = NULL;
  int *ptr;
  
  for(curr = head; curr && (curr->data < num || num < curr->data); 
    curr = curr->next)
    prev = curr;
  
  if(!curr)
    return NULL;
  
  size--;
  
  if(prev)
    prev->next = curr->next;
  else // erased front of list
    head = curr->next;
  
  if(curr->next)
  {
    curr->next->previous = prev;
    ptr = &curr->next->data;
  } // if something after
  else // erased last item in the list
    ptr = NULL;
      
  delete curr;
  
  return ptr;
}  // erase()


int* LinkedList::find(int num)
{
  for(curr = head; curr && (curr->data < num || num < curr->data);
    curr = curr->next)
    cout << curr->data << ' ';
  
  if(!curr)
    return NULL;
  
  return &curr->data;
}  // find()


int* LinkedList::insert(int num)
{
  if(tail)
    tail = tail->next = new ListNode(num, tail, NULL);
  else // inserting into an empty list
    head = tail = new ListNode(num, NULL, NULL);
  
  curr = tail;
  size++;
  return &tail->data;
}  // insert()


int*  LinkedList::operator-- ()
{
  if(curr)
    curr = curr->previous;
  
  if(curr)
    return &curr->data;
  
  return NULL;
}  // operator--


int*  LinkedList::operator++ ()
{
  if(curr)
    curr = curr->next;
  
  if(curr)
    return &curr->data;
  
  return NULL;
}  // operator++
