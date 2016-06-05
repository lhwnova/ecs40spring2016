
#include "list.h"

ListNode::ListNode (Sale *s, ListNode *p, ListNode *n) : sale(s), prev(p), next(n)
{
}


List::List() : head(NULL)
{
}


void List::insert(Sale *s)
{
  ListNode *ptr, *prev = NULL;
  
  for(ptr = head; ptr && ptr->sale->getTotal() < s->getTotal(); ptr = ptr->next)
    prev = ptr;
  
  if(!prev)
  {
    head = new ListNode(s, prev, ptr);
    
    if(ptr)
      ptr->prev = head;
  }
  else
  {
    prev->next = new ListNode(s, prev, ptr);
    
    if(ptr)
      ptr->prev = prev->next;
  }
}


void List::printAll(ListNode *ptr) const
{
  if(!ptr)
    return;
  
  printAll(ptr->next);
  ptr->sale->display();
  cout << endl;
}

List::~List()
{
  for(ListNode* ptr = head; ptr; ptr = head)
  {
    head = ptr->next;
    delete ptr;
  }
    
}