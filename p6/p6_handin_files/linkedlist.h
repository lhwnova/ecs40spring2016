
#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include <iostream>
#include "container.h"

class SortedLinkedList;
class LinkedList;
class ListNode
{
  int data;
  ListNode* previous;
  ListNode* next;
  ListNode(int dat, ListNode* prev, ListNode* nex):
  data(dat), previous(prev), next(nex){};
  friend LinkedList;
  friend SortedLinkedList;
}; // ListNode()


class LinkedList:public Container
{
protected:
  ListNode* head;
  ListNode* tail;
  ListNode* curr;
public:
  LinkedList():Container(ZERO), head(NULL), tail(NULL), curr(NULL){};
  ~LinkedList();
  virtual int* insert(int num);
  virtual int* erase(int num);
  virtual int* find(int num);
  int* operator++();
  int* operator--();
}; // LinkedList()

#endif // LINKEDLIST_H
