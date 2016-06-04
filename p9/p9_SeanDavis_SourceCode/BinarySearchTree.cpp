// Author: Sean Davis

#include <iostream>
#include <cassert>
#include "BinarySearchTree.h"
using namespace std;

template <typename T>
BSTNode<T>:: BSTNode(const T &d, BSTNode <T> *lef, BSTNode <T> *r) : data(d), 
  left(lef), right(r)
{
}  // BSTNode()

 
template <typename T>
BinarySearchTree<T>::BinarySearchTree() : root(NULL)
{
} // BinarySearchTree()


template <typename T>
BinarySearchTree<T>::~BinarySearchTree() 
{
  if(root)
  {  
    makeEmpty(root);
    delete root;
  }  // if root
} // BinarySearchTree()


template <typename T>
void BinarySearchTree<T>::find(const T &value) const
{
  assert(root != NULL);
  
  find(root, value);
} // find()
 
template <typename T>
void BinarySearchTree<T>::find(const BSTNode<T> *t, const T &value) const
{
  if(! t)
    cout << "Not found.\n";
  else // not NULL 
    if(value < t->data)
      find(t->left, value);
    else  // t->data less than or equal to data
      if(t->data < value)
        find(t->right, value);
      else // t->data is data
        cout << "Found.\n";
} // find()


template <typename T>
const BSTNode <T> * BinarySearchTree<T>::findMin(const BSTNode<T> *t) const
{
  if(!t)
    return NULL;
  
  if(t->left)
    return findMin(t->left);
  else // if no left child, must be min
    return t;
}  // findMin()


template <typename T>
void BinarySearchTree<T>::inOrder() const
{
  inOrder(root);
  cout << endl;
} // inOrder ()


template <typename T>
void BinarySearchTree<T>::inOrder(const BSTNode<T> *t) const
{
  if(!t)
    return;
  
  inOrder(t->left);
  cout << t->data << ", ";
  inOrder(t->right);
} // inOrder ()

template <typename T>
void BinarySearchTree<T>::insert(const T &value)
{
  if(! root)
    root = new BSTNode<T>(value, NULL, NULL);
  else  // not empty tree
    insert(root, value);
} // insert()


template <typename T>
void BinarySearchTree<T>::insert(BSTNode<T> *t, const T &value)
{
  assert(value < t->data || t->data < value);
  
  if(value < t->data)
  {
    if(t->left)
      insert(t->left, value);
    else // No left child
      t->left = new BSTNode<T>(value, NULL, NULL);
  }  // if value < t->data
  else  // t->data less than or equal to data
    if(t->data < value)
    {
      if(t->right)
        insert(t->right, value);
      else // No t->right
        t->right = new BSTNode<T>(value, NULL, NULL);
    } // if t->data < right    
      else // t->data is data
        cout << "Found duplicate.\n";
} // insert()


template <typename T>
void BinarySearchTree<T>::makeEmpty(BSTNode<T> *t) 
{
  if(t->left)
  {
    makeEmpty(t->left);
    delete t->left;
  }  // if t->left
  
  if(t->right)
  {
    makeEmpty(t->right);
    delete t->right;
  } // if t->right
} // BinarySearchTree()

template <typename T>
void BinarySearchTree<T>::postOrder() const
{
  postOrder(root);
  cout << endl;
} // postOrder ()


template <typename T>
void BinarySearchTree<T>::postOrder(const BSTNode<T> *t) const
{
  if(!t)
    return;
  
  postOrder(t->left);
  postOrder(t->right);
  cout << t->data << ", ";
} // postOrder ()


template <typename T>
void BinarySearchTree<T>::remove(const T &value)
{
  assert(root);
  remove(root, value);
} // remove()


template <typename T>
void BinarySearchTree<T>::remove(BSTNode<T> * &t, const T &value)
{
  const BSTNode <T> *temp = t;
  
  assert(t != NULL);
  
  if(! t)
    cout << "Not found.\n";
  else // not NULL 
    if(value < t->data)
      remove(t->left, value);
    else  // t->data less than or equal to data
      if(t->data < value)
        remove(t->right, value);
      else // t->data is data
      {
        if(t->left && t->right) // two children
        {
          temp = findMin(t->right);
          t->data = temp->data;
          remove(t->right, temp->data);
        } // if has two children
        else // not two children
        {
          if(t->left) 
            t = t->left;
          else // if right child or none
            if(t->right)
              t = t->right;
            else // a leaf
              t = NULL;
              
          delete temp;
        } // else not two children
      }  // else found data
} // remove()
