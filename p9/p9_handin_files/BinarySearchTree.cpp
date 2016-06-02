//author: Steven Li

#include "BinarySearchTree.h"
#include <cassert>
using namespace std;

template <typename T>
void BinarySearchTree<T>::insert(const T &value)
{
  if(root)
    insert(root, value);
  else // root is not NULL
    root = new BSTNode<T>(value, NULL, NULL);
} // insert()

template <typename T>
void BinarySearchTree<T>::find(const T &value) const
{
  assert(root != NULL);
  BSTNode<T>* result = find(root, value);
  
  if(!result) // not found
    cout << "Not found." << endl;
  else // found
    cout << "Found." << endl;
} // find()

template <typename T>
void BinarySearchTree<T>::remove(const T &value)
{
  assert(root);
  remove(root, value);
} // remove()

template <typename T>
void BinarySearchTree<T>::inOrder() const
{
  inOrder(root);
  cout << endl;
} // inOrder

template <typename T>
void BinarySearchTree<T>::postOrder() const
{
  postOrder(root);
  cout << endl;
} // postOrder

template <typename T>
void BinarySearchTree<T>::insert(BSTNode<T> *t, const T &value) const
{
  if(t->data < value)
  {
    if(!t->right)
      t->right = new BSTNode<T>(value, NULL, NULL);
    else // not null
      insert(t->right, value);
  } // right
  else // left
    if(value < t->data)
    {
      if(!t->left)
        t->left = new BSTNode<T>(value, NULL, NULL);
      else // not null
        insert(t->left, value);
    } // left
  else // equal
  {
    cout << "Found duplicate." << endl;
    assert(value < t->data || t->data < value);
  } // duplicate

} // recursive insert()

template <typename T>
BSTNode<T>* BinarySearchTree<T>::find(BSTNode<T>* t, const T &value) const
{
  if(!t)
    return NULL;
  else // no equal left
    if(value < t->data)
      t = find(t->left, value);
  else // not equal right
    if(t->data < value)
      t = find(t->right, value);
  
  return t;
} // recursive find()


template <typename T>
void BinarySearchTree<T>::remove(BSTNode<T> * &t, const T &value) const
{
  assert(t != NULL);
  
  if(!t)
  {
    cout << "Not found." << endl; return;
  } // t is NULL
  
  if(value < t->data) remove(t->left, value);
  else // no children
    if (t->data < value) remove(t->right, value);
    else // no children
      if(!t->left && !t->right)
      {
        delete t; t = NULL;
      } // no children
      else // one left is children
        if(!t->left && t->right)
        {
          BSTNode<T>* temp = t; t = t->right; delete temp;
        } // one left is children
        else // one right is children
          if(t->left && !t->right)
          {
            BSTNode<T>* temp = t; t = t->left; delete temp;
          } // one right is children
          else // two children
            if(t->left && t->right)
            {
              BSTNode<T>* temp = findMin(t->right); T foo = temp->data;
              remove(t, temp->data); t->data = foo;
            } // two children
  
} // recursive remove()


template <typename T>
void BinarySearchTree<T>::inOrder(BSTNode<T> *t) const
{
  if(!t) // t is NULL
    return;
  
  inOrder(t->left);
  cout << t->data << ", ";
  inOrder(t->right);
} // recursive inOrder

template <typename T>
void BinarySearchTree<T>::postOrder(BSTNode<T> *t) const
{
  if(!t) // t is NULL
    return;
  
  postOrder(t->left);
  postOrder(t->right);
  cout << t->data << ", ";
} // recursive postOrder

template <typename T>
void BinarySearchTree<T>::makeEmpty(BSTNode<T> *t) const
{
  if(!t) // t is NULL
    return;
  
  makeEmpty(t->left);
  makeEmpty(t->right);
  delete t;
} // makeEmpty()

template <typename T>
BinarySearchTree<T>::~BinarySearchTree()
{
  makeEmpty(root);
} //~BinarySearchTree()


template <typename T>
BSTNode<T>* BinarySearchTree<T>::findMin(BSTNode<T> *t) const
{
  if(!t->left)
    return t;
  
  t = findMin(t->left);
  return t;
} // findMin()

