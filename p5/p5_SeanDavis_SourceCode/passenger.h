#ifndef PASSENGER_H
#define	PASSENGER_H

#include <fstream>
#include <iostream>
#include "plane.h"

using namespace std;

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
public:
  Passenger();
  Passenger(short flightNu, short ro, char sea, const char nam[]);
  static void copyPassengers(); 
  bool operator== (int flightNumber) const;
  bool operator== (const char *nam) const;
  friend ostream& operator<< (ostream &os, const Passenger &rhs);
  friend ifstream& operator>> (ifstream &inf, Plane &plane);
  Passenger& operator! ();
}; // class passengers 

#endif	// PASSENGERS_H

