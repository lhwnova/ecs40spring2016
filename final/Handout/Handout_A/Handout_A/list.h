
#ifndef LIST_H
#define LIST_H

#include <iostream>
#include "sale.h"

class ListNode
{
  Sale *sale;
  ListNode *prev;
  ListNode *next;
  ListNode (Sale *s, ListNode *p, ListNode *n);
  friend class List;
};  // class ListNode


class List
{
  ListNode *head;
  void printAll(ListNode *ptr) const;
public:
  List();
  ~List();
  void print() const {printAll(head);}
  void insert(Sale *s);
}; // class List

#endif // LIST_H
