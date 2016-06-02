// Author: Sean Davis 

#include <stdio.h>
#include <stdlib.h>
#include "flight.h"
#include "utilities.h"

#define DONE 0
#define MAX_CHOICE 1


void addPassenger(Flight* flights, int numFlights)
{
  int i, flightNumber;
  
  printf("Flt# Origin               Destination\n");

  for(i = 0; i < numFlights; i++)
    printFlightInfo(&flights[i]);

  do
  {
    printf("\nFlight number (0 = exit): ");
    flightNumber = getNumber();

    if(flightNumber > 0)
    {
      
      for(i = 0; i < numFlights; i++)
        if(getFlightNumber(&flights[i]) == flightNumber)
        {
          addPassenger(&flights[i]);
          break;
        }  // if found match of flight

      if(i == numFlights)
      {
        printf("We do not have a flight number %d.\n", flightNumber);
        printf("Please try again.\n");
      }  // if flightNumber not found
    }  // if flightNumber > 0
    else // if flightNumer <= 0
      if(flightNumber == ERROR)
        printf("That is an invalid flight number.\nPlease try again.\n"); 
  }  while((flightNumber != 0 && i == numFlights) || flightNumber == ERROR);
}  // addPassenger()


void freeFlights(Flight *flights, int numFlights)
{
  int i;
  
  for(i = 0; i < numFlights; i++)
    freeFlight(&flights[i]);
  
  free(flights);
}  // freeFlights()


int getChoice()
{ 
  int choice;
  printf("\nECS Flight Reservation Menu\n");
  printf("0. Exit.\n");
  printf("1. Add Passenger.\n");
  
  do
  {
    printf("\nPlease enter your choice: ");
    choice = getNumber();
    
    if(choice == ERROR)
    {
      printf("Your choice is invalid.\n");
      printf("Please try again.\n");
    }  // if invalid format
    else // choice is a valid number
      if(choice < DONE || choice > MAX_CHOICE)
      {
        printf("%d is not an available choice.\n", choice);
        printf("Please try again.\n");
      }  // if choice out of range.
  } while(choice < DONE || choice > MAX_CHOICE  || choice == ERROR);
  
  if(choice == DONE)
    printf("Goodbye.\n");
  
  return choice;
} // getChoice()


Flight* readFlights(int *numFlights)
{
  Flight *flights;
  int i;
  FILE *fp = fopen("reservations.txt", "r");
  fscanf(fp, "%d", numFlights);
  flights = (Flight*) malloc(*numFlights * sizeof(Flight));
  
  for(i = 0; i < *numFlights; i++)
    readFlight(&flights[i], fp);
  
  fclose(fp);
  return flights;
} // readFlights()

void writeFlights(Flight *flights, int numFlights)
{
  int i;
  FILE *fp = fopen("reservations2.txt", "w");
  fprintf(fp, "%d\n", numFlights);
  
  for(i = 0; i < numFlights; i++)
    writeFlight(&flights[i], fp);
  
  fclose(fp);
}  // freeFlights()

int main(int argc, char** argv)
{
  int numFlights;
  Flight *flights = readFlights(&numFlights);
  
  while(getChoice() != DONE)
    addPassenger(flights, numFlights);
  
  writeFlights(flights, numFlights);
  freeFlights(flights, numFlights);

  return 0;
} // main())

