// Author: Sean Davis 

#include <iostream>
#include <fstream>
#include "container.h"
//#include "vector.h"                         // uncomment for Vector
//#include "sortedvector.h"                   // uncomment for SortedVector
#include "linkedlist.h"                     // uncomment for LinkedList
//#include "sortedlinkedlist.h"               // uncomment for SortedLinkedList

using namespace std;

int main(int argc, char** argv) 
{
  char operation;
  int num, *intPtr, containerNum, index;
  Container *containers[4] = {NULL, NULL, NULL, NULL};

// SortedVector *vectors[2];                       // uncomment for SortedVector
// containers[0] = vectors[0] = new SortedVector;  // uncomment for SortedVector
// Vector *vectorPtr = new Vector;                 // uncomment for Vector
// containers[1] = vectors[1] = vectorPtr;         // uncomment for Vector
   LinkedList *lists[2];                           //  uncomment for LinkedList
   containers[2] = lists[0] = new LinkedList;      //  uncomment for LinkedList
// containers[3] = lists[1] = new SortedLinkedList; //uncomment SortedLinkedList
  
  ifstream inf(argv[1]);
  
  while(inf >> containerNum >> operation)
  {  
    switch(operation)
    {
/*      case 'C' :   // uncomment for SortedVector 
        cout << "Capacity: " << vectors[containerNum]->getCapacity() << endl; 
        break;
*/                  // uncomment for SortedVector
      case 'E' : 
        inf >> num;
        intPtr = containers[containerNum]->erase(num); 
        cout << "Erase " << num << " : ";

        if(intPtr)
          cout << *intPtr << endl;
        else // nothing after num
          cout << "NULL\n";

        break;
      case 'F' :
        inf >> num;
        cout << "Find " << num << " : ";  
        intPtr = containers[containerNum]->find(num); 

        if(intPtr)
          cout << *intPtr << endl;
        else // not found
          cout << "NULL\n";

        break; 
      case 'I' : 
        inf >> num; 
        intPtr = containers[containerNum]->insert(num); 
        cout << "Insert " << num << " : " << *intPtr << endl;
        break;
      case 'S' :
        cout << "Size: " << containers[containerNum]->getSize() << endl;
        break; 
      case 'R' :                       
        inf >> index;
//        num = (*vectors[containerNum])[index]; // uncomment for 2.12
        cout << "Read [" << index << "] : " << num << endl;
        break;
      case 'W' : 
        inf >> index >> num;
        cout << "Write [" << index << "] = " << num << endl;
//      (*vectorPtr)[index] = num;  // uncomment for Vector
        break;
    case 'M' : 
        intPtr = --(*lists[containerNum - 2]); 
        cout << "-- : ";
        
        if(intPtr)
          cout << *intPtr << endl;
        else  // moved beyound front of container
          cout << "NULL\n";
        
        break;
      case 'P' :
        intPtr = ++(*lists[containerNum - 2]) ; 
        cout << "++ : ";
        
        if(intPtr)
          cout << *intPtr << endl;
        else  // moved beyond end of container
          cout << "NULL\n";
        
        break;
    // uncomment for LinkedList
    }  // switch
  }  // while more in file
    
  for(int i = 0; i < 4; i++)
    if(containers[i])
      delete containers[i];

  return 0;
} // main())

