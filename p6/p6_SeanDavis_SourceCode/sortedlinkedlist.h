#ifndef SORTEDLINKEDLIST_H
#define	SORTEDLINKEDLIST_H
#include "linkedlist.h"

class SortedLinkedList : public LinkedList 
{
public:
  int* erase(int num);
  int* find(int num);
  int* insert(int num);
}; // class SortedLinkedList 

#endif	// LINIEDLIST_H

