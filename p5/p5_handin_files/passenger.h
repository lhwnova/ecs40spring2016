#ifndef PASSENGER_H
#define	PASSENGER_H

#include <iostream>
#include <fstream>
#include "plane.h"

class Passenger 
{
public:
  static const int NAME_LENGTH = 30;
  static const int CANCELLED = -1;
private:
  short flightNum;
  short row; 
  char seat;
  char name[NAME_LENGTH];
  friend ifstream& operator >> (ifstream& inf, Plane& plane);
  friend ostream& operator << (ostream& os, const Passenger& passen);
public:
  Passenger();
  Passenger(short flightNu, short ro, char sea, const char nam[]);
  static void copyPassengers();
  bool operator==(int flightNumber) const; 
  bool operator==(const char* passengerName) const;
  void operator!();
}; // class passengers 

#endif	// PASSENGERS_H
