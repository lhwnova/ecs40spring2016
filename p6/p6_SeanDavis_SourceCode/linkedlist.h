#ifndef LINKEDLIST_H
#define	LINKEDLIST_H
#include "container.h"

class LinkedList;
class SortedLinkedList;

class ListNode
{
  int data;
  ListNode *previous;
  ListNode *next;
  ListNode(int d, ListNode *p, ListNode *n);
  friend class LinkedList;
  friend class SortedLinkedList;
}; // class ListNode

class LinkedList : public Container 
{
protected:
  ListNode *head;
  ListNode *tail;
  ListNode *curr;
public:
  LinkedList();
  ~LinkedList();
  virtual int* erase(int num);
  virtual int* find(int num);
  virtual int* insert(int num);
  int* operator-- ();
  int* operator++ ();
}; // class LinkedList 

#endif	// LINIEDLIST_H

