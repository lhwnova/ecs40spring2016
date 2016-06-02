// Author: Sean Davis

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "plane.h"
#include "utilities.h"

#define TRUE 1


int addPassenger(Plane *plane)
{
  int row, seatNum;
  char name[MAX_NAME_SIZE];
  
  if(plane->reserved == plane->rows * plane->width)
    return 0;  // false
  
  printf("Please enter the name of the passenger: ");
  fgets(name, MAX_NAME_SIZE, stdin);
  strtok(name, "\r\n");
  showGrid(plane);
  
  while(TRUE)
  {
    row = getRow(plane);
    printf("Please enter the seat letter you wish to reserve: ");
    seatNum = getchar() - FIRST_SEAT;

    while(getchar() != '\n');

    if(plane->passengers[row - FIRST_ROW][seatNum] == NULL)
      break;

    printf("That seat is already occupied.\nPlease try again.\n");
  } // while occupied seat
  
  plane->passengers[row - FIRST_ROW][seatNum] 
    = (char*) malloc(strlen(name) + 1);
  strcpy( plane->passengers[row - FIRST_ROW][seatNum], name);
  plane->reserved++;
  return 1;
}  // addPassenger()

void freePlane(Plane* plane)
{
  int row, seatNum;
  
  for(row = 0; row < plane->rows; row++)
  {
    for(seatNum = 0; seatNum < plane->width; seatNum++)
      if(plane->passengers[row][seatNum] != NULL)
        free(plane->passengers[row][seatNum]);
    
    free (plane->passengers[row]);
  }  // for row
  
  free (plane->passengers);
}  // freePlane


int getRow(Plane *plane)
{
  int row;
  
  do
  {
    printf("\nPlease enter the row of the seat you wish to reserve: ");
    row = getNumber();

    if(row == ERROR)
      printf("That is an invalid row number.\nPlease try again.\n");
    else  // valid row number
      if(row < 1 || row > plane->rows)
        printf("There is no row #%d on this flight.\nPlease try again.\n", 
          row);
  }  while(row < 1 || row > plane->rows);
  
  return row;
} // getRow()

  
void readPlane(Plane* plane, FILE *fp)
{
  int row, numPassenger, seatNum;
  char seat, name[MAX_NAME_SIZE];
  fscanf(fp, "%d %d %d", &plane->rows, &plane->width, &plane->reserved);
  plane->passengers = (char***) malloc(plane->rows * sizeof(char**));
  
  for(row = 0; row < plane->rows; row++)
  {
    plane->passengers[row] = (char**) malloc(plane->width * sizeof (char*));
    
    for(seatNum = 0; seatNum < plane->width; seatNum++)
      plane->passengers[row][seatNum] = NULL;
  } // for each row
  
  for(numPassenger = 0; numPassenger < plane->reserved; numPassenger++)
  {
    fscanf(fp, "%d%c ", &row, &seat);
    fgets(name, MAX_NAME_SIZE, fp);
    strtok(name, "\r\n");
    seatNum = seat;
    plane->passengers[row - FIRST_ROW][seatNum - FIRST_SEAT] 
      = (char*) malloc(strlen(name) + 1);
    strcpy(plane->passengers[row - FIRST_ROW][seatNum - FIRST_SEAT], name);
  }  // for each passenger
}  // readPlane()


void showGrid(Plane *plane)
{
  int row, seatNum = 0;
  
  printf("ROW# ");
  
  for(seatNum = 0; seatNum < plane->width; seatNum++)
    putchar(seatNum + FIRST_SEAT);
  
  putchar('\n');
  
  for(row = 0; row < plane->rows; row++)
  {
    printf("%2d   ", row + 1);
    
    for(seatNum = 0; seatNum < plane->width; seatNum++)
      if(plane->passengers[row][seatNum])
        putchar('X');
      else  // empty seat
        putchar('-');
    
    putchar('\n');
  }  // for each row
  
  printf("\nX = reserved.\n");
}  // showGrid()


void writePlane(Plane* plane, FILE *fp)
{
  int row, seatNum;
  fprintf(fp, "%d %d %d\n", plane->rows, plane->width, plane->reserved);

  for(row = 0; row < plane->rows; row++)
    for(seatNum = 0; seatNum < plane->width; seatNum++)
      if(plane->passengers[row][seatNum] != NULL)
        fprintf(fp, "%d%c %s\n", row + FIRST_ROW, seatNum + FIRST_SEAT,
          plane->passengers[row][seatNum]);
}  // readPlane()
