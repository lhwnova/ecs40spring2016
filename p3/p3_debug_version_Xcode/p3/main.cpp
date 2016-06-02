#include <iostream>
#include <fstream>

#include "flight.h"
#include "utilities.h"

#define DONE 0
#define MAX_CHOICE 1

using namespace std;

void writeFlights(Flight *flights, const int numFlights)
{
  int i;
  ofstream outf;
  outf.open("/Users/zhiyingli/Desktop/ECS 40/p3/reservations2.txt");
  
  outf << numFlights << endl;
  
  for(i = 0; i < numFlights; i++)
    flights[i].writeFlight(outf);
  
  outf.close();
}  // freeFlights()


Flight* readFlights(int *numFlights)
{
  Flight *flights;
  int i;
  
  ifstream inf;
  inf.open("/Users/zhiyingli/Desktop/ECS 40/p3/reservations.txt");
  
  inf >> *numFlights;
  flights = new Flight[*numFlights];
  
  for(i = 0; i < *numFlights; i++)
  {
    flights[i].construcFlight(inf);
  } //readFlight
  
  inf.close();
  return flights;
} // readFlights()


void deleteFlights(Flight *flights)
{
  delete [] flights;
}  // freeFlights()


int getChoice()
{
  int choice;
  cout << "\nECS Flight Reservation Menu\n";
  cout << "0. Exit.\n";
  cout << "1. Add Passenger.\n";
  
  do
  {
    cout << "\nPlease enter your choice: ";
    choice = (int) getNumber();
    
    if(choice == ERROR)
    {
      cout << "Your choice is invalid.\n";
      cout << "Please try again.\n";
    }  // if invalid format
    else // choice is a valid number
      if(choice < DONE || choice > MAX_CHOICE)
      {
        cout << choice << " is not an available choice.\n";
        cout << "Please try again.\n";
      }  // if choice out of range.
  } while(choice < DONE || choice > MAX_CHOICE  || choice == ERROR);
  
  if(choice == DONE)
    cout << "Goodbye.\n";
  
  return choice;
} // getChoice()


void addPassenger(Flight* flights, int numFlights)
{
  int i, flightNumber;
  
  cout << "Flt# Origin               Destination\n";
  
  for(i = 0; i < numFlights; i++)
    flights[i].printFlightInfo();
  
  do
  {
    cout << "\nFlight number (0 = exit): ";
    flightNumber = (int) getNumber();
    
    if(flightNumber > 0)
    {
      
      for(i = 0; i < numFlights; i++)
        if(flights[i].getFlightNumber() == flightNumber)
        {
          flights[i].addPassenger();
          break;
        }  // if found match of flight
      
      if(i == numFlights)
      {
        cout << "We do not have a flight number " << flightNumber << ".\n";
        cout << "Please try again.\n";
      }  // if flightNumber not found
    }  // if flightNumber > 0
    else // if flightNumer <= 0
      if(flightNumber == ERROR)
        cout << "That is an invalid flight number.\nPlease try again.\n";
  }  while((flightNumber != 0 && i == numFlights) || flightNumber == ERROR);
}  // addPassenger()


int main(int argc, char** argv)
{
  int numFlights;
  Flight *flights = readFlights(&numFlights);
  
  while(getChoice() != DONE)
    addPassenger(flights, numFlights);
  
  writeFlights(flights, numFlights);
  deleteFlights(flights);
  return 0;
} // main())