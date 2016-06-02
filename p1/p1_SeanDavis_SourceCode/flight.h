#ifndef FLIGHT_H
#define	FLIGHT_H

#include <stdio.h>
#include "plane.h"

#define MAX_CITY_LENGTH 20

typedef struct
{
  int flightNum;
  char origin[MAX_CITY_LENGTH];
  char destination[MAX_CITY_LENGTH];
  Plane *plane;
} Flight;
 
void addPassenger(Flight *flight);
void freeFlight(Flight *flight);
int getFlightNumber(Flight *flight);
void printFlightInfo(Flight *flight);
void readFlight(Flight *flight, FILE *fp);
void writeFlight(Flight *flight, FILE *fp);


#endif	// FLIGHT_H

