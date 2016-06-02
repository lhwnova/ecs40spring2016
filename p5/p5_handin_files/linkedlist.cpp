// author: Steven Li

#include <iostream>
#include <fstream>

#include "linkedlist.h"

using namespace std;

void LinkedList::initialize(int seatNum)
{
  for (int i = 0; i < seatNum; i++)
    head = new ListNode(EMPTY, head);
} // initialize linked list to EMPTY


LinkedList::~LinkedList()
{
  for(ListNode* ptr = head; ptr; ptr = head)
  {
    head = ptr->next;
    delete ptr;
  } // for loop
} // delete linked list

//int LinkedList::operator[](int seatNum) const
//{
//  ListNode* ptr = head;

//  for(int i = 0; i < seatNum; i++)
//    ptr = ptr->next;

//  return ptr->offset;
//} // const bracket operator

int& LinkedList::operator[](int seatNum) const
{
  ListNode* ptr = head;

  for(int i = 0; i < seatNum; i++)
  	ptr = ptr->next;

  return ptr->offset;
} // non const bracket operator

ostream& operator << (ostream& os, const LinkedList& list)
{
  for(ListNode* ptr = list.head; ptr; ptr = ptr->next)
  {
    if(ptr->offset != LinkedList::EMPTY)
        cout << 'X';
    else  // empty seat
        cout << '-';
  } // for loop

  return os;
} // operator
