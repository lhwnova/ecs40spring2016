#ifndef FLIGHTS_H
#define	FLIGHTS_H

#include "flight.h"

class Flights 
{
  static const int INITIAL_SIZE = 2;
  static const int RESIZE_MULTIPLIER = 2;
  static const int TEN = 10;
  Flight **flights;
  int size;
  int capacity;
public:
  Flights();
  ~Flights();
  void addPassenger() const;
  void addFlight();
  void insert(Flight *flight);
  int getSize() const;
  void readFlights();
  void removeFlight();
  void removePassenger() const;
}; // class flights 

#endif	// FLIGHTS_H

