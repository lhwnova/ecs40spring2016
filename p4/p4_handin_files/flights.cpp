#include <iostream>
#include <fstream>

#include "flights.h"
#include "flight.h"
#include "utilities.h"

using namespace std;

void Flights::removeFlight()
{
  int i, flightNumber;
  cout << "Existing Flights:\n";
  cout << "\nFlt# Origin               Destination\n";
  
  for(i = 0; i < size; i++)
    flights[i]->printFlightInfo();

  cout << "\nFlight number to remove: ";
  flightNumber = getNumber();
  int j, k;

  for (j = 0; j < size; j++)
    if (flights[j]->getFlightNumber() == flightNumber)
      break;
  
  flights[j]->removeFlight(flightNumber);
  //Flight* temp = flights[j];
  delete flights[j];

  for(k = j + 1; k < size; k++) flights[k - 1] = flights[k];
  
  size--;
} //


void Flights::removePassenger() const
{
  int i, flightNumber;
  cout << "Existing Flights:\n";
  cout << "\nFlt# Origin               Destination\n";
  
  for(i = 0; i < size; i++)
    flights[i]->printFlightInfo();

  cout << "\nFlight number of passenger remove: ";
  flightNumber = getNumber();
  int j;

  for (j = 0; j < size; j++)
  {
    if (flights[j]->getFlightNumber() == flightNumber)
      break;
  } //

  flights[j]->removePassenger(flightNumber);
} //


void Flights::addFlight()
{
  int i, flightNumber;
  cout << "Existing Flights:\n";
  cout << "\nFlt# Origin               Destination\n";
  
  for(i = 0; i < size; i++)
    flights[i]->printFlightInfo();

  cout << "\nFlight number to add: ";
  flightNumber = getNumber();
  Flight* pFlight = new Flight();
  pFlight->addFlight(flightNumber);
  insert(pFlight);
} //

void Flights::addPassenger() const
{
  int i, flightNumber;
  cout << "Flt# Origin               Destination\n";
  
  for(i = 0; i < size; i++)
    flights[i]->printFlightInfo();
  
  do
  {
    cout << "\nFlight number (0 = exit): ";
    flightNumber = getNumber();
    
    if(flightNumber > 0)
    {
      
      for(i = 0; i < size; i++)
        if(flights[i]->getFlightNumber() == flightNumber)
        {
          flights[i]->addPassenger(flightNumber);
          break;
        }  // if found match of flight
      
      if(i == size)
      {
        cout << "We do not have a flight number " << flightNumber << ".\n";
        cout << "Please try again.\n";
      }  // if flightNumber not found
    }  // if flightNumber > 0
    else // if flightNumer <= 0
      if(flightNumber == NONE)
        cout << "That is an invalid flight number.\nPlease try again.\n";
  }  while((flightNumber != 0 && i == size) || flightNumber == NONE);
} //

Flights::Flights()
{
  size = ISIZE;
  capacity = ICAPCITY;
  flights = new Flight*[capacity];

  for(int j = 0; j < capacity; j++)
    flights[j] = NULL;
  
  ofstream outf("passengers3.dat");
  outf.close();
} //

void Flights::readFlights()
{
  int i, numFlights;
  ifstream inf  ("flights.csv");
  inf >> numFlights;

  for(i = 0; i < numFlights; i++)
  {
    Flight* pFlight = new Flight();
    pFlight->readFlight(inf);
    insert(pFlight);
  } //
  
  inf.close();
} //


Flights::~Flights()
{
  int i;
  ofstream outf ("flights2.csv");
  outf << size << endl;
  outf.close();
  
  for(i = 0; i < size; i++) delete flights[i];

  delete [] flights;
} //

void Flights::insert(Flight* flight)
{
  size++;

  while (size > capacity)
  {
    capacity = capacity * TWO; // double the capacity
    Flight** temp = new Flight*[capacity];
    
    for(int k = 0; k < capacity; k++) temp[k] = NULL;

    for (int j = 0; j < size ; j++) temp[j] = flights[j];

    delete [] flights;
    flights = temp;
  } //
  
  int i, j;

  for(i = 0; i < size ; i++)
  {
    if(flights[i] == NULL)
    {
      flights[i] = flight;
      break;
    } //
    
    if (flight->getFlightNumber() < flights[i]->getFlightNumber())
    {
      for (j = size - 1 ; j >= i ; j--)
        flights[j + 1] = flights[j];
      
      flights[i] = flight;
      break;
    } //
  } //
} //
