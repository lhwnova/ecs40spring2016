#ifndef FLIGHT_H
#define	FLIGHT_H

#include <iostream>
#include <fstream>
#include "plane.h"

using namespace std;

class Flight
{
  static const int MAX_CITY_LENGTH = 20;
  static const int TEN = 10;
  static const int FLIGHT_NUM_SPACE = 4;
  int flightNum;
  char origin[MAX_CITY_LENGTH];
  char destination[MAX_CITY_LENGTH];
  Plane *plane;
public:
  void addPassenger() const;
  ~Flight();
  void addFlight();
  int getFlightNumber() const;
  void printFlightInfo() const;
  void readFlight( ifstream &inf);
  void removeFlight();
  void removePassenger() const;
} ;  // class Flight
#endif	// FLIGHT_H

