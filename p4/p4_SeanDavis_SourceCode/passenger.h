#ifndef PASSENGER_H
#define	PASSENGER_H

#include "plane.h"

class Passenger 
{
public:
  static const int NAME_LENGTH = 30;
private:
  short flightNum;
  short row; 
  char seat;
  char name[NAME_LENGTH];
  friend class Plane;
public:
  Passenger();
  Passenger(short flightNu, short ro, char sea, const char nam[]);
  static void copyPassengers(); 
}; // class passengers 

#endif	// PASSENGERS_H

