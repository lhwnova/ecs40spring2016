// Author: Sean Davis
#include <cstring>
#include <fstream>
#include <iostream>
#include "plane.h"
#include "passenger.h"
using namespace std;


Passenger::Passenger() 
{
} // Passenger()


Passenger::Passenger(short flightNu, short ro, char sea, const char nam[]) : 
  flightNum(flightNu), row(ro), seat(sea)
{
  strcpy(name, nam);
}  // Passenger()


void Passenger::copyPassengers()
{
  Passenger passenger;

  ifstream inf("passengers.dat", ios::binary);
  ofstream outf("passengers2.dat", ios::binary);

  while(inf.read( (char*) &passenger, sizeof(Passenger)))
    outf.write((char*) &passenger, sizeof(Passenger));

  outf.close();
  inf.close();
}  // copyPassengers()


bool Passenger::operator== (int flightNumber) const
{
  return flightNumber == flightNum;
}  // operator==


bool Passenger::operator== (const char *nam) const
{
  return strcmp(name, nam) == 0;
}  // operator==


Passenger& Passenger::operator! ()
{
  flightNum = CANCELLED;
  return *this;
}  // operator!


ostream& operator<< (ostream &os, const Passenger &rhs)
{
  os << rhs.name;
  return os;
}  // operator<<
