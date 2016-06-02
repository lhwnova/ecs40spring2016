// Author: Sean Davis

#include <cstring>
#include <iostream>
#include <fstream>
#include <iomanip>
#include "flight.h"

using namespace std;


void Flight::operator++() const
{
  ++(*plane);
}  // addPassenger()


Flight::~Flight()
{
  ofstream outf("flights2.csv", ios::app);
  outf << flightNum << ',' << origin << ',' << destination << ',';
  plane->writePlane(outf);
  outf.close();
  delete plane;
}  // freeFlight()


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
}  // addFlight()


int Flight::getFlightNumber() const
{
  return flightNum;
}  // getFlightNumber()


ostream& operator << (ostream& os, Flight& flight)
{
  os << left << setw(Flight::FLIGHT_NUM_SPACE) << flight.flightNum 
     << ' ' << setw(Flight::MAX_CITY_LENGTH) << flight.origin 
     << ' '  << flight.destination << endl;
  return os;
}


ifstream& operator >> (ifstream& inf, Flight& flight)
{ 
  inf >> flight.flightNum;
  inf.ignore(Flight::TEN, ',');
  inf.getline(flight.origin, Flight::MAX_CITY_LENGTH, ',');
  inf.getline(flight.destination, Flight::MAX_CITY_LENGTH, ',');
  flight.plane = new Plane(flight.flightNum);
  inf >> *(flight.plane);
  return inf;
}  // readFlight()


void Flight::operator!()
{
  !(*plane);
}  // removePassenger();


void Flight::operator--(int) const
{
  (*plane)--;
}  // removePassenger();

bool Flight::findPassenger(const char* passengerName) const
{
  bool found = false;
  found = plane->findPassenger(passengerName);
  return found;
} // findPassenger