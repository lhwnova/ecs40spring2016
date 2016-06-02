#include "list.h"
#include "state.h"
#include <iostream>
#include <fstream>

void LinkedList::read(const char* filename){
  ifstream inf(filename); //, ios::in|ios::binary);
  StateCode *sc = new StateCode();
  StateCodeLong *scl;
  
  while (sc->read(inf))
  {
    ListNode *ptr, *prev = NULL;
    
    for (ptr = head; ptr && ptr->data < *sc; ptr = ptr->next)
      prev = ptr;
    
    if (ptr && ptr->data == *sc)
      ptr->data += *sc;
    else
      if (prev && prev->data == *sc)
        prev->data += *sc;
      else
        if (prev)
        {
          size++;
          scl = new StateCodeLong(*sc);
          prev->next = new ListNode(*scl, prev, ptr);
          if (ptr)
            ptr->prev = prev->next;
        }
        else
        {
          size++;
          scl = new StateCodeLong(*sc);
          head = new ListNode(*scl, NULL, ptr);
          
          if (ptr)
            ptr->prev = head;
        }
    sc = new StateCode();
  }
}

const StateCodeLong& LinkedList::operator[] (int index) const
{
  ListNode *ptr = head;
  
  for (int i=0; i < index; i++)
    ptr = ptr->next;
  
  return ptr->data;
}

