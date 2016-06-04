#ifndef BINARYSEARCHTREE_H
#define	BINARYSEARCHTREE_H

template <typename T>
class BinarySearchTree;


template <typename T>
class BSTNode
{
  T data;
  BSTNode <T> *left;
  BSTNode <T> *right;
  BSTNode(const T &d, BSTNode <T> *lef, BSTNode <T> *r);
  friend class BinarySearchTree <T>;
};  // class BSTNode;



template <typename T>
class BinarySearchTree 
{
  BSTNode <T> *root;
  void find(const BSTNode<T> *t, const T &value) const;
  const BSTNode <T> * findMin(const BSTNode<T> *t) const;
  void inOrder(const BSTNode<T> *t) const;
  void insert(BSTNode<T> *t, const T &value);
  void makeEmpty(BSTNode<T> *t);
  void postOrder(const BSTNode<T> *t) const;
  void remove(BSTNode<T> * &t, const T &value);
public:
  BinarySearchTree();
  ~BinarySearchTree();
  void find(const T &value) const;
  void inOrder() const;
  void insert(const T &value);
  void postOrder() const;
  void remove(const T &value);
  
}; // class BinarySearchTree 


#include "BinarySearchTree.cpp"
#endif	// BINARYSEARCHTREE_H

