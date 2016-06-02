// author: Steven Li
#include <iostream>
#include "flight.h"

#ifndef FLIGHTS_H
#define FLIGHTS_H

using namespace std;

class Flights
{
private:
  static const int NONE = -1;
  static const int TWO = 2;
  static const int ISIZE = 0;
  static const int ICAPCITY = 2;
  Flight** flights;
  int size;
  int capacity;
public:
  void removeFlight();
  void removePassenger() const;
  Flights();
  void readFlights();
  void addPassenger() const;
  ~Flights();
  void addFlight();
  void insert(Flight* flight);
}; //flights



#endif // flights_hpp
