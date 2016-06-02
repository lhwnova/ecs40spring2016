// Author: Sean Davis

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "flight.h"


void addPassenger(Flight *flight)
{
  if(!addPassenger(flight->plane))
    printf("We are sorry but Flight #%d is full.\n", flight->flightNum);
  
}  // addPassenger()


void freeFlight(Flight *flight)
{
  freePlane(flight->plane);
  free(flight->plane);
}  // freeFlight()


int getFlightNumber(Flight *flight)
{
  return flight->flightNum;
}  // getFlightNumber()


void printFlightInfo(Flight *flight)
{
  printf("%-4d %-20s %s\n", flight->flightNum, flight->origin, 
    flight->destination);
}  // printFlightInfo()


void readFlight(Flight *flight, FILE *fp)
{
  fscanf(fp, "%d\n", &flight->flightNum);
  fgets(flight->origin, MAX_CITY_LENGTH, fp);
  strtok(flight->origin, "\r\n");  // get rid of '\n' and/or '\r'
  fgets(flight->destination, MAX_CITY_LENGTH, fp);
  strtok(flight->destination, "\r\n");  // get rid of '\n'
  flight->plane = (Plane*) malloc(sizeof(Plane));
  readPlane(flight->plane, fp);
}  // readFlight()


void writeFlight(Flight *flight, FILE *fp)
{
  fprintf(fp, "%d\n%s\n%s\n", flight->flightNum, flight->origin,
    flight->destination);
  writePlane(flight->plane, fp);
}  // readFlight()
