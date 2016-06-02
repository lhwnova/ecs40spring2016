#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "flight.h"
#include "plane.h"
#include "utilities.h"

int main()
{
  int numFlights, choice;
  Flight* flights;
  readAllFlights(&flights, &numFlights);
  meun();
  
  while(firstMeun(&choice))
  {
    if(choice == CONTINUE) // chose CONTINUE
    {
      addPassenger(&flights, numFlights);
      meun();
    } // if, it will call addPassenger()
  } // while, the program will keep if CONTINUE or QUIT is not chosen
  
  writeAllFlights(numFlights, flights);
  
  return 0;
} // main