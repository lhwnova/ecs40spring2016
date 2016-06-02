
#include <string.h>
#include <iostream>
#include <fstream>
#include <iomanip>

#include "flight.h"

using namespace std;

void Flight::removeFlight(int const flightNumber)
{
  flightNum = TOUS;
  plane->removeFlight(flightNumber);
} //


void Flight::removePassenger(int const flightNumber) const
{
  char name[MAX_NAME_SIZE];
  cout << "Passengers on Flight #" << flightNumber << endl;
  plane->showPassenger();
  cout << "\nName of passenger to remove: ";
  cin.getline(name, MAX_NAME_SIZE);
  strtok(name, "\n\r");
  
  plane->removePassenger(flightNumber, name);
} //


void Flight::addFlight(int const flightNumber)
{
  flightNum = flightNumber;
  cout << "Origin: ";
  cin.getline(origin, MCILEN);
  cout << "Destination: ";
  cin.getline(destination, MCILEN);

  plane = new Plane();
  plane->addFlight();
} //


void Flight::addPassenger(int const flightNum) const
{
  if(!plane->addPassenger(flightNum))
    cout << "We are sorry but Flight #" << flightNum << " is full.\n";
}  // addPassenger()

Flight::~Flight()
{
  ofstream outf ("flights2.csv", ios::app);
  outf << flightNum << ',' << origin << ',' << destination << ',';
  plane->writePlane(outf, flightNum);

  outf.close();
  delete plane;
}  // freeFlight()


int Flight::getFlightNumber() const
{
  return flightNum;
}  // getFlightNumber()


void Flight::printFlightInfo() const
{
  cout << left << setw(4) << flightNum << ' ' << setw(20) 
    << origin << ' '  << destination << endl;
}  // printFlightInfo()


void Flight::readFlight(ifstream &inf)
{
  inf >> flightNum;
  inf.ignore(TEN, ',');
  inf.getline(origin, MCILEN, ',');
  inf.getline(destination, MCILEN, ',');
  plane = new Plane(inf, flightNum);
}  // readFlight()
