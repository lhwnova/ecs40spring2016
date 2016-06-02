// Author: Sean Davis

#include <iostream>
#include "linkedlist.h"

using namespace std;

ListNode::ListNode(int off, ListNode *n) : offset(off), next(n)
{
} // ListNode()


LinkedList::~LinkedList()
{
  for(ListNode *ptr = head; ptr; ptr = head)
  {
    head = ptr->next;
    delete ptr;
  }  // for each ListNode
}  // ~LinkedList


void LinkedList::initialize(int width)
{
  head = NULL;

  for(int i = 0; i < width; i++)
    head = new ListNode(EMPTY, head);
} // initialize()


int& LinkedList::operator[] (int seatNum)
{
  int i;
  ListNode *ptr = head;
  
  for(i = 0; i != seatNum; i++)
    ptr = ptr->next;
  
  return ptr->offset;
} // operator[]


int LinkedList::operator[] (int seatNum) const
{
  int i;
  ListNode *ptr = head;
  
  for(i = 0; i != seatNum; i++)
    ptr = ptr->next;
  
  return ptr->offset;
} // operator[]

ostream& operator << (ostream& os, const LinkedList &list)
{
  for(ListNode *ptr = list.head; ptr; ptr = ptr->next)
    if(ptr->offset != LinkedList::EMPTY)
        os << 'X';
      else  // empty seat
        os << '-';
    
    os << endl;
    return os;
}  // operator <<
