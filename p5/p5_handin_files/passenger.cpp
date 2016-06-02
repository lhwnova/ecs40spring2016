// Author: Sean Davis
#include <cstring>
#include <ostream>
#include <fstream>
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


bool Passenger::operator==(int flightNumber) const
{
  return flightNum == flightNumber;
} // takes int as its parameter, and returns true or false


bool Passenger::operator==(const char* passengerName) const
{
  return !strcmp(name, passengerName);
} // takes a const char pointer as paramters, and returns ture or false


void Passenger::operator!()
{
  flightNum = CANCELLED;
} // sets flightNum to Passengers::CANCELLED


ostream& operator << (ostream& os, const Passenger& passen)
{
  os << passen.name << endl;
  return os;
} // prints the name of the passenger

