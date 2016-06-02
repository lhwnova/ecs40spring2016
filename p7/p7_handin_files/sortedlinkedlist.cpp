
#include "sortedlinkedlist.h"

using namespace std;

int* SortedLinkedList::insert(int num)
{
  ListNode *ptr, *prev = NULL;
  
  for(ptr = head; ptr && ptr->data < num; ptr = ptr->next)
    prev = ptr;
  
  size++;
  curr = new ListNode(num, prev, ptr);
  
  if(!prev) // insert at the front of the list
    head = curr;
  else // insert in the middle
    prev->next = curr;
  
  if(ptr) // if next term is not null
    ptr->previous = curr;
  
  return &(curr->data);
} // insert()


int* SortedLinkedList::erase(int num)
{
  ListNode* ptr, *prev = NULL;
  
  for(ptr = head; ptr && ptr->data < num; ptr = ptr->next)
    prev = ptr;
  
  if(ptr && !(ptr->data < num || num < ptr->data))
  {
    curr = ptr->next;
    delete ptr;
    size--;
    
    if(!prev)
      head = curr;
    else // if prev is not null
      prev->next = curr;
    
    curr->previous = prev;
    return &(curr->data);
  } // if found
  else // if not found
    return NULL;
} // erase()


int* SortedLinkedList::find(int num)
{
  //ListNode *ptr;

  for(curr = head; curr && curr->data < num; curr = curr->next)
    cout << curr->data << " ";
  
  if(curr && !(curr->data < num || num < curr->data))
    return &(curr->data); // if found
  else // if not found
    return NULL;
} // find()
