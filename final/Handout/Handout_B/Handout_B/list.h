#ifndef LIST_H
#define LIST_H

#include <iostream>
#include <string>
#include "food.h"

using namespace std;

template <class T> class List;

template <class T> class ListNode
{
  T data;
  ListNode<T> *prev;
  ListNode<T> *next;
  friend class List<T>;
public:
  ListNode(T &d, ListNode<T> *p, ListNode<T> *n);
}; // class ListNode

template <class T> class List
{
  ListNode<T> *head;
  const T find(const ListNode<T> *ptr, const string &foodName) const;
public:
  List();
  ~List();
  const T findFood(const string &foodName) const;
  void insert(T data);
}; // class List

#include "list.cpp"
#endif // LIST_H
