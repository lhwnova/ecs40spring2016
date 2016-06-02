#ifndef FLIGHT_H
#define	FLIGHT_H

#include <iostream>
#include <fstream>
#include "plane.h"

using namespace std;
#define MAX_CITY_LENGTH 20
#define FLIGHT_NUM_SPACE 4

class Flight
{
  int flightNum;
  char origin[MAX_CITY_LENGTH];
  char destination[MAX_CITY_LENGTH];
  Plane *plane;
public:
  void addPassenger();
  ~Flight();
  int getFlightNumber() const;
  void printFlightInfo() const;
  void readFlight(ifstream &inf);
  void writeFlight(ofstream &outf) const;
} ;
 



#endif	// FLIGHT_H

