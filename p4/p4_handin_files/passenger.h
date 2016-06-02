//author: Steven Li

#ifndef PASSENGER_H
#define	PASSENGER_H
#include <fstream>
#include "plane.h"

using namespace std;

class Passenger
{
  friend class Plane;
private:
  static const int NAME_L = 30;
  static const int ZERO = 0;
  short flightNum;
  short row;
  char seat;
  char name[NAME_L];
public:
  static void copyPassengers();
  Passenger();
  Passenger(short flightNum, short row, char seat, char* name);
}; // class Plane

#endif	// PASSENGER_H