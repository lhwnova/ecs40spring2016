
#ifndef SORTEDLINKEDLIST_H
#define SORTEDLINKEDLIST_H

#include <iostream>
#include "linkedlist.h"

using namespace std;

class SortedLinkedList:public LinkedList
{
public:
  int* insert(int num);
  int* erase(int num);
  int* find(int num);
}; // class SortedLinkedList

#endif // SORTEDLINKEDLIST_H
