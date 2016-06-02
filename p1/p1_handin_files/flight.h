#ifndef FLIGHT_H

#define FLIGHT_H
#define EXIT 0
#define CONTINUE 1
#define INVALID -1
#define MAX_ORIGIN_LENGTH 20
#define MAX_DESTINATION_LENGTH 20
#define MAX_PASSENGER_NAME_LENGTH 80
#define INPUT_FILE "reservations.txt"
#define OUTPUT_FILE "reservations2.txt"
#define FLIGHT_NUM_PLACEHOLDER "%-5d"
#define ORIGIN_PLACEHOLDER "%-21s"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "plane.h"

typedef struct
{
  int flightNum;
  char origin[MAX_ORIGIN_LENGTH];
  char destination[MAX_DESTINATION_LENGTH];
  Plane *plane;
} Flight;

void readAllFlights (Flight** flights, int* numFlights);


void readFlight (FILE* fp_in, Flight* flight);


void displayAllFlight(Flight* flights, int numFlights);


void writeAllFlights (int numFlights, Flight* flights);


void writeFlight(FILE* fp_out, Flight flight);


void deleteAllFlights (int numFlights, Flight* flights);


void deleteFlight(Flight flight);


void addPassenger(Flight** flights, int numFlights);


int isValidFlightNumber(int flightNumber, Flight* flights, int numFlights);


int getFlightIndex(int flightNumber, Flight* flights, int numFlights);


#endif
