#ifndef FLIGHT_H
#define	FLIGHT_H

#include <iostream>
#include <fstream>
#include "plane.h"

using namespace std;


class Flight
{
private:
  static const int MAX_CITY_LENGTH = 20;
  static const int TEN = 10;
  static const int MAX_NAME_SIZE = 30;
  static const int MCILEN = 20;
  static const int TOUS = 10000;
  int flightNum;
  char origin[MAX_CITY_LENGTH];
  char destination[MAX_CITY_LENGTH];
  Plane *plane;
public:
  void removeFlight(int const flightNumber);
  void removePassenger(int const flightNumber) const;
  void addFlight(int const flightNumber);
  void addPassenger(int const flightNum) const;
  ~Flight();
  int getFlightNumber() const;
  void printFlightInfo() const;
  void readFlight(ifstream &inf);
  void writeFlight(ofstream &outf) const;
} ; // flights
 



#endif	// FLIGHT_H

