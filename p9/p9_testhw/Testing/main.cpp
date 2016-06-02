// Author: Sean Davis 

//#include <iostream>
#include <fstream>
#include "BinarySearchTree.h"

using namespace std;

int main(int argc, char** argv)
{
  BinarySearchTree<int> tree;
  ifstream inf(argv[1]);
  char operation;
  int value;
  
  while(inf >> operation >> value)
  {
    switch(operation)
    {
      case 'I' : tree.insert(value); break;
      case 'R' : tree.remove(value); break;
      case 'F' : tree.find(value); break;
      case 'i' : tree.inOrder(); break;
      case 'p' : tree.postOrder(); break;
    }  // switch()
    
    inf.ignore(100, '\n');
  } // while more in file
  
  return 0;
} // main())

