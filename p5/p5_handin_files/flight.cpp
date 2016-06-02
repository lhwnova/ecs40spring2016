// Author: Sean Davis

#include <cstring>
#include <iostream>
#include <fstream>
#include <iomanip>
#include "flight.h"

using namespace std;


ifstream& operator >> (ifstream& inf, Flight& flight)
{ 
  inf >> flight.flightNum;
  inf.ignore(Flight::TEN, ',');
  inf.getline(flight.origin, Flight::MAX_CITY_LENGTH, ',');
  inf.getline(flight.destination, Flight::MAX_CITY_LENGTH, ',');
  flight.plane = new Plane(flight.flightNum);
  inf >> *(flight.plane);
  return inf;
}  // operator


ostream& operator << (ostream& os, const Flight& flight)
{
  os << left << setw(Flight::FLIGHT_NUM_SPACE) << flight.flightNum 
     << ' ' << setw(Flight::MAX_CITY_LENGTH) << flight.origin 
     << ' ' << flight.destination << endl;
  return os;
} // operator


const Flight& Flight::operator++(int) const
{
  ++(*plane);
  return *this;
}  // operator


Flight::~Flight()
{
  ofstream outf("flights2.csv", ios::app);
  outf << flightNum << ',' << origin << ',' << destination << ',';
  plane->writePlane(outf);
  outf.close();
  delete plane;
}  // operator


void Flight::addFlight()
{
  cout << "\nFlight number to add: ";
  cin >> flightNum;
  cin.ignore(TEN, '\n');
  cout << "Origin: ";
  cin.getline(origin, MAX_CITY_LENGTH);
  cout << "Destination: ";
  cin.getline(destination, MAX_CITY_LENGTH);
  plane = new Plane(flightNum);
  plane->addFlight();
}  // operator


int Flight::getFlightNumber() const
{
  return flightNum;
}  // getFlightNumber()


const Flight& Flight::operator!() const
{
  !(*plane);
  return *this;
}  // operator


const Flight& Flight::operator--() const
{
  (*plane)-- ;
  return *this;
}  // operator

bool Flight::findPassenger(const char* passengerName) const
{
  bool found = false;
  found = plane->findPassenger(passengerName);
  return found;
} // findPassenger
