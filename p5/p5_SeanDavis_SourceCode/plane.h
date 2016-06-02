#ifndef PLANE_H
#define	PLANE_H


#include <fstream>
#include "linkedlist.h"
using namespace std;


class Plane
{
 
  static const int FIRST_ROW = 1;
  static const int FIRST_SEAT = 'A';
  static const int TEN = 10;
  static const int ROW_SPACE = 2;
  int rows;
  int width;
  int reserved;
  int flightNumber;
  LinkedList *passengers;
  int getRow() const;
  void showGrid() const;
  friend ostream& operator<< (ostream &os, const Plane &plane);
public:
  Plane(int flightNumb);
  ~Plane();
  void addFlight();
  bool findPassenger(const char *name) const;
  Plane& operator++ ();
  friend ifstream& operator>> (ifstream &inf, Plane &plane);
  const Plane& operator! () const;
  Plane& operator-- (int);
  void writePlane(ofstream &outf) const;
}; // class Plane

#endif	// PLANE_H


