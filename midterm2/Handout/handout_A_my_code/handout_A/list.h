#ifndef LISTH
#define LISTH

#include "state.h"

class LinkedList;

class ListNode{
  StateCodeLong data;
  ListNode *prev, *next;
  ListNode(const StateCodeLong &d, ListNode *p, ListNode *n):data(d), prev(p), next(n){}
  friend class LinkedList;
};

class LinkedList{
  ListNode *head;
  int size;
public:
  LinkedList():head(NULL), size(0){}
  int getSize() const {return size;}
  void read(const char* filename);
  const StateCodeLong& operator[] (int index) const;
};

#endif