#include "flight.h"
#include "utilities.h"

void readAllFlights (Flight** flights, int* numFlights)
{
  FILE* fp_in = fopen(INPUT_FILE, "r");
  
  if (fp_in == (FILE*) NULL)
  {
    printf("error reading file\n");
    exit(EXIT_FAILURE);
  } //if error reading file
  
  fscanf(fp_in, "%d", numFlights);
  *flights = (Flight*) malloc (*numFlights * sizeof(Flight));
  
  for (int i = 0; i < *numFlights; i++)
  {
    readFlight(fp_in, &(*flights)[i]);
  } //iterate every flight to read them from file
  
  fclose(fp_in);
} //read the first line and to create Flight array


void readFlight (FILE* fp_in, Flight* flight)
{
  fscanf(fp_in, "%d\n", &(flight->flightNum));
  fgets(flight->origin , MAX_ORIGIN_LENGTH, fp_in);
  fgets(flight->destination, MAX_DESTINATION_LENGTH, fp_in);
  
  strtok(flight->origin, "\r\n");
  strtok(flight->destination, "\r\n");

  flight->plane = (Plane*) malloc(sizeof(Plane));
  readPlane(fp_in, &(flight->plane));
} //read each flight from file


void displayAllFlight(Flight* flights, int numFlights)
{
  printf("Flt# ");
  printf(ORIGIN_PLACEHOLDER, "Origin\0");
  printf("Destination\n");
  
  for (int i = 0; i < numFlights; i++)
  {
    printf(FLIGHT_NUM_PLACEHOLDER, flights[i].flightNum);
    printf(ORIGIN_PLACEHOLDER, flights[i].origin);
    printf("%s\n", flights[i].destination);
  } //iterate each fight and display them
  
  return;
} //display all the flight in file


void writeAllFlights (int numFlights, Flight* flights)
{
  FILE* fp_out = fopen(OUTPUT_FILE, "w");
  
  if (fp_out == (FILE*) NULL)
  {
    printf("error writing file\n");
    exit(EXIT_FAILURE);
  } //if error reading file
  
  fprintf(fp_out, "%d\n", numFlights);
  
  for (int i = 0; i < numFlights; i++)
  {
    writeFlight(fp_out, flights[i]);
  } //iterate through the flight and call writeFlight
  
  deleteAllFlights(numFlights, flights);
  fclose(fp_out);
} //write all flight


void writeFlight(FILE* fp_out, Flight flight)
{
  fprintf(fp_out, "%d\n", flight.flightNum);
  fprintf(fp_out, "%s\n", flight.origin);
  fprintf(fp_out, "%s\n", flight.destination);
  writePlane(fp_out, flight.plane);
} //write one flight and call writePlane


void deleteAllFlights (int numFlights, Flight* flights)
{
  
  for (int i = 0; i < numFlights ; i++ )
  {
    deletePlane(flights[i].plane);
  } //iterate trought the file to delete the plane in each flight
  
  free(flights);
} //deleat the flight array that has been created in heaps


void addPassenger(Flight** flights, int numFlights)
{
  displayAllFlight(*flights, numFlights);
  printf("\nFlight number (0 = exit): ");
  int flightNumber = getNumber();
  int flightIndex;
  
  while(!isValidFlightNumber(flightNumber, *flights, numFlights))
  {
    
    if (flightNumber == EXIT)
    {
      return;
    } //if the flight number is exit, then exit
    
    printf("\nFlight number (0 = exit): ");
    flightNumber = getNumber();
  } //add passenger to the passenger matrix in plane struct
  
  flightIndex = getFlightIndex(flightNumber, *flights, numFlights);
  
  if(!isFullPlane(flightNumber, (*flights)[flightIndex].plane))
  {
    changePlane(&((*flights)[flightIndex].plane));
  } //if the plane is full, skip
  
} //make cange to char*** passenger


int isValidFlightNumber(int flightNumber, Flight* flights, int numFlights)
{
  
  if (flightNumber == EXIT)
  {
    return 0;
  } //if the filght nubmer is eixt, then exit
  
  if (flightNumber == INVALID)
  {
    printf("That is an invalid flight nunber.\n");
    printf("Please try again.\n");
    return 0;
  } //if the flight number is invalid, print error message
  
  for(int i = 0; i < numFlights; i++)
  {
    if(flightNumber == flights[i].flightNum)
    {
      return 1;
    } //if the flight nubmer exist
  } //iterate every flight in the array
  
  printf("We do not have a flight number %d.\n", flightNumber);
  printf("Please try again.\n");
  return 0;
} //to check if the flight number is valid or not


int getFlightIndex(int flightNumber, Flight* flights, int numFlights)
{
  for(int i = 0; i < numFlights; i++)
  {
    if(flightNumber == flights[i].flightNum)
    {
      return i;
    } //if the flighter number is found
  } //iterate every flight in the array
  
  return 0;
} //get the index of the flight
