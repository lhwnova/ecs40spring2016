#ifndef PLANE_H
#define	PLANE_H
#include <fstream>

#include "linkedlist.h"
using namespace std;


class Plane
{
  static const int NONE = -1;
  static const int FIRST_ROW = 1;
  static const int FIRST_SEAT = 'A';
  static const int TEN = 10;
  static const int ROW_SPACE = 2;
  static const int INIT_RE = 0;
  int flightNumber;
  int rows;
  int width;
  int reserved;
  LinkedList* passengers;
  int getRow() const;
  void showGrid() const;
  void showPassengers() const;
  friend ostream& operator << (ostream& os, const Plane& plane);
  friend ifstream& operator >> (ifstream& inf, Plane& plane);
public:
  Plane(int flightNum):flightNumber(flightNum), reserved(INIT_RE){};
  ~Plane();
  void addFlight();
  Plane& operator++();
  Plane& operator--(int);
  const Plane& operator!() const;
  void writePlane(ofstream &outf) const;
  bool findPassenger(const char* passengerName) const;
}; // class Plane

#endif	// PLANE_H


