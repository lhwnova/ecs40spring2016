#ifndef FLIGHT_H
#define	FLIGHT_H

#include <iostream>
#include "plane.h"

#define MAX_CITY_LENGTH 20

using namespace std;

class Flight
{
private:
  int flightNum;
  char origin[MAX_CITY_LENGTH];
  char destination[MAX_CITY_LENGTH];
  Plane *plane;
public:
  ~Flight();
  void construcFlight(ifstream &inf);
  void printFlightInfo() const;
  void writeFlight(ofstream &outf) const;
  int getFlightNumber() const;
  void addPassenger();
}; // Flight class


#endif	// FLIGHT_H