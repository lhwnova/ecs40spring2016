// Author: Sean Davis

#include <string.h>
#include <iostream>
#include <fstream>
#include <iomanip>
#include "flight.h"

using namespace std;
#define TEN 10

void Flight::addPassenger()
{
  if(!plane->addPassenger())
    cout << "We are sorry but Flight #" << flightNum << " is full.\n";
  
}  // addPassenger()


Flight::~Flight()
{
  delete plane;
}  // freeFlight()


int Flight::getFlightNumber() const
{
  return flightNum;
}  // getFlightNumber()


void Flight::printFlightInfo() const
{
  cout << left << setw(FLIGHT_NUM_SPACE) << flightNum << ' ' 
    << setw(MAX_CITY_LENGTH) << origin << ' '  << destination << endl;
}  // printFlightInfo()


void Flight::readFlight( ifstream &inf)
{
  inf >> flightNum;
  inf.ignore(TEN, '\n');
  inf.getline(origin, MAX_CITY_LENGTH);
  inf.getline(destination, MAX_CITY_LENGTH);
  plane = new Plane(inf);
}  // readFlight()


void Flight::writeFlight( ofstream &outf) const
{
  outf << flightNum << endl << origin << endl << destination << endl;
  plane->writePlane(outf);
}  // readFlight()
