
#include "linkedlist.h"

using namespace std;

LinkedList::~LinkedList()
{
  for(ListNode* ptr = head; ptr; ptr = head)
  {
    head = ptr->next;
    delete ptr;
  } // for loop
} // delete linked list


int* LinkedList::insert(int num)
{
  curr = new ListNode(num, tail, NULL);
  
  if(!size)
    head = curr;
  else // size is not zero
    tail->next = curr;
  
  tail = curr;
  size++;
  return &(curr->data);
} // insert()


int* LinkedList::erase(int num)
{
  ListNode* ptr, *prev = NULL;
  
  for(ptr = head; ptr && (ptr->data < num || num < ptr->data); ptr = ptr->next)
    prev = ptr;
  
  if(ptr && !(ptr->data < num || num < ptr->data))
  {
    curr = ptr->next;
    delete ptr;
    size--;
    
    if(!prev)
      head = curr;
    else // prev is not null
      prev->next = curr;
    
    curr->previous = prev;
    return &(curr->data);
  } // if found
  else // if not found
    return NULL;
} // erase()


int* LinkedList::find(int num)
{
  for(curr = head; curr && (curr->data < num || num < curr->data); 
     curr = curr->next) cout << curr->data << " ";
  
  if(curr && !(curr->data < num || num < curr->data))
    return &(curr->data); // if found
  else // if not found
    return NULL;
} // find()


int* LinkedList::operator++()
{
  if(curr) // if curr is not NULL
    curr = curr->next;
  
  if(curr) // if updated curr or curr is not NULL
    return &(curr->data);
  else // if curr is NUll
    return NULL;
} // operator pre increment


int* LinkedList::operator--()
{
  if(curr) // if curr is not NULL
    curr = curr->previous;
  
  if(curr) // if updated curr or curr is not NULL
    return &(curr->data);
  else // if curr is NUll
    return NULL;
} // operator pre decrement
