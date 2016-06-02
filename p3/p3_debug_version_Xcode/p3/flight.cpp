#include <cstring>
#include <fstream>
#include <iomanip>

#include "flight.h"
#define IGNORE_TIMES 256
#define SH_FLIGHT_NUM 5
#define SH_ORGIN 21

using namespace std;

void Flight::construcFlight(ifstream &inf)
{
  inf >> flightNum;
  inf.ignore(IGNORE_TIMES, '\n');
  inf.getline(origin, MAX_NAME_SIZE);
  strtok(origin, "\r\n");
  inf.getline(destination, MAX_NAME_SIZE);
  strtok(destination, "\r\n");
  plane = new Plane(inf);
} // accessFlight


void Flight::printFlightInfo() const
{
  cout << left << setw(SH_FLIGHT_NUM) << flightNum
       << left << setw(SH_ORGIN) << origin
       << destination << endl;
} // printFlightInfo()


void Flight::writeFlight(ofstream &outf) const
{
  outf << flightNum << endl;
  outf << origin << endl;
  outf << destination << endl;
  
  plane->writePlane(outf);
} // writeFlight()

Flight::~Flight()
{
  delete plane;
} // Flight destruc

int Flight::getFlightNumber() const
{
  return flightNum;
}  // getFlightNumber()


void Flight::addPassenger()
{
  if(!plane->addPassenger())
    cout << "We are sorry but Flight #" << flightNum << " is full.\n";
}  // addPassenger()