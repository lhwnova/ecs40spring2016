#ifndef LINKED_LIST
#define LINKED_LIST

#include <iostream>
#include <fstream>
#include <iomanip>

using namespace std;

class LinkedList; // predecaleration

class ListNode
{
  int offset;
  ListNode* next;
  ListNode(int offse, ListNode* nex):offset(offse), next(nex){};
  friend class LinkedList;
  friend ostream& operator << (ostream& os, const LinkedList& list);
}; // ListNode

class LinkedList
{
  static const int EMPTY = -1;
  ListNode* head;
  friend ostream& operator << (ostream& os, const LinkedList& list);
public:
  LinkedList():head(NULL){};
  void initialize(int seatNum);
  ~LinkedList();
  //int operator[](int seatNum) const;
  int& operator[](int seatNum) const;
}; // LinkedList

#endif	// LINKED_LIST
