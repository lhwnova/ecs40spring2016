// author: Steven Li

#include <iostream>
#ifndef BINARYSEARCHTREE_H
#define BINARYSEARCHTREE_H

template <typename T>
class BinarySearchTree;


template <typename T>
class BSTNode
{
  friend BinarySearchTree<T>;
  T data;
  BSTNode* left;
  BSTNode* right;
  BSTNode(T dat, BSTNode* lef, BSTNode* ri): data(dat), left(lef), right(ri){}
}; // class BSTNode


template <typename T>
class BinarySearchTree
{
  BSTNode<T>* root;
  void insert(BSTNode<T> *t, const T &value) const;
  BSTNode<T>* find(BSTNode<T>* t, const T &value) const;
  void remove(BSTNode<T> * &t, const T &value) const;
  void inOrder(BSTNode<T> *t) const;
  void postOrder(BSTNode<T> *t) const;
  void makeEmpty(BSTNode<T> *t) const;
  BSTNode<T>* findMin(BSTNode<T> *t) const;
public:
  BinarySearchTree():root(NULL){};
  ~BinarySearchTree();
  
  void insert(const T& value);
  void find(const T& value) const;
  void remove(const T& value);
  void inOrder() const;
  void postOrder() const;
  
}; // class BinarySearchTree


#include "BinarySearchTree.cpp"
#endif // BinarySearchTree_h
