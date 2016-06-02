#ifndef FLIGHTS_H
#define	FLIGHTS_H

#include <fstream>
#include <iostream>
#include "flight.h"

using namespace std;

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
  void findPassenger() const;
  Flights& operator++ ();
  Flights& operator+= (Flight *flight);
  int getSize() const;
  friend ifstream& operator>> (ifstream &inf, Flights &flights);
  Flights& operator-- (int);
  void removePassenger() const;
}; // class flights 

#endif	// FLIGHTS_H

