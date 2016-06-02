#ifndef LINKEDLIST_H
#define	LINKEDLIST_H

#include <iostream>
using namespace std;

class LinkedList;

class ListNode
{
  int offset;
  ListNode *next;
  ListNode(int off, ListNode *n) ;
  friend class LinkedList;
  friend ostream& operator << (ostream& os, const LinkedList &list);
};  // class ListNode

class LinkedList 
{
  ListNode *head;
public:
  static const int EMPTY = -1;
  ~LinkedList();
  void initialize(int width);
  int& operator[] (int seatNum);
  int operator[] (int seatNum) const;
  friend ostream& operator << (ostream& os, const LinkedList &list);
}; // class LinkedList 

#endif	// LINKEDLIST_H

