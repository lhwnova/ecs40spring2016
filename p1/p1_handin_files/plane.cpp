#include "plane.h"
#include "flight.h"
#include "utilities.h"

void readPlane (FILE* fp_in, Plane** plane)
{
  int rowNum, rowI, colI, length;
  char colLetter, passenger_name[MAX_PASSENGER_NAME_LENGTH];
  fscanf(fp_in, "%d ", &((*plane)->rows));
  fscanf(fp_in, "%d ", &((*plane)->width));
  fscanf(fp_in, "%d\n", &((*plane)->reserved));
  (*plane)->passengers = (char***)malloc((*plane)->reserved * sizeof(char**));
  
  for (int row = 0; row < (*plane)->rows; row++)
  {
    (*plane)->passengers[row] = (char**)malloc((*plane)->width * sizeof(char*));
    
    for (int col = 0; col < (*plane)->width; col++)
    {
      (*plane)->passengers [row][col] = (char*) NULL;
    } //initialize all the passenger name to null
  } //malloc the space passenger[row][col]
  
  for (int i = 0; i < (*plane)->reserved; i++)
  {
    fscanf(fp_in, "%d%c ", &rowNum, &colLetter);
    fgets(passenger_name,  MAX_PASSENGER_NAME_LENGTH , fp_in);
    strtok(passenger_name, "\r\n");
    
    rowI = rowNum - 1;
    colI = colLetter - SEAT_BASE;
    length = (int) strlen(passenger_name) + 1;
    (*plane)->passengers[rowI][colI] = (char*)malloc(length * sizeof(char));
    strcpy((*plane)->passengers [rowI][colI], passenger_name);
  } //add reserved people to the matrix
} //read plane from file


void writePlane(FILE* fp_out, Plane* plane)
{
  int rowI, colI, rowN, colN;
  fprintf(fp_out, "%d %d %d\n", plane->rows, plane->width, plane->reserved);
  
  for (rowI = 0; rowI < plane->rows; rowI++)
  {
    for (colI = 0; colI < plane->width; colI++)
    {
      if (plane->passengers[rowI][colI] != (char*) NULL)
      {
        rowN = rowI + 1;
        colN = colI + SEAT_BASE;
        fprintf(fp_out, "%d%c %s\n", rowN, colN, plane->passengers[rowI][colI]);
      } //write passenger[rowI][colI] to the output file
    } //iterate each col
  } //iterate each row
} //write plane to file


void deletePlane(Plane* plane)
{
  for (int row = 0; row < plane->rows; row++)
  {
    for (int col = 0; col < plane->width; col++)
    {
      free(plane->passengers[row][col]);
    } //iterate each col to free passenger[row][col]
    
    free(plane->passengers[row]);
  } //iterate each row to free passenger[row]
  
  free(plane->passengers);
  free(plane);
} //free plane that has been malloced in memory


void displayBoardPlane(Plane* plane)
{
  printf("ROW# ");
  
  for(int i = 0; i < plane->width; i++)
  {
    printf("%c", i + SEAT_BASE);
  }//print the seat letter in the first row
  
  printf("\n");
  
  for (int row = 0; row < plane->rows; row++)
  {
    printf(" %d   ", row + 1);
    
    for (int col = 0; col < plane->width; col++)
    {
      if (plane->passengers[row][col] == (char*)NULL)
      {
        printf("-");
      } //if the seat is not reserved
      else //if the seat is reserved
      {
        printf("X");
      } //if the seat is reserved
    } //iterate each col to print the seat
    
    printf("\n");
  }//iterate each row to print out the seat
  
  printf("\nX = reserved.\n\n");
  return;
} //display the plane board


void changePlane(Plane** plane)
{
  char width, passengerName[MAX_PASSENGER_NAME_LENGTH];
  int rowNum, rowI, colI, nameLength;
  printf("Please enter the name of the passenger: ");
  fgets(passengerName, MAX_PASSENGER_NAME_LENGTH , stdin);
  strtok(passengerName, "\r\n");
  nameLength = (int) strlen(passengerName) + 1;
  displayBoardPlane(*plane);
  getRowAndWidth(&rowNum, &width, *plane);
  rowI = rowNum - 1;
  colI = width - SEAT_BASE;
  
  while((*plane)->passengers[rowI][colI] != (char*)NULL)
  {
    printf("That seat is already occupied.\nPlease try again.\n\n");
    getRowAndWidth(&rowNum, &width, *plane);
    rowI = rowNum - 1;
    colI = width - SEAT_BASE;
  } //if the passenger seat is NULL then ask again
  
  (*plane)->passengers[rowI][colI] = (char*) malloc(nameLength * sizeof(char));
  strcpy((*plane)->passengers[rowNum - 1][width - SEAT_BASE], passengerName);
  (*plane)->reserved += 1;
} //change those unreserved seats to be reserved


void getRowAndWidth(int* row, char* width, Plane* plane)
{
  int max_row = plane->rows;
  printf("Please enter the row of the seat you wish to reserve: ");
  *row = getNumber();
  
  while(!(*row > 0 && *row < max_row + 1))
  {
    if (*row == INVALID) //if user enter invalid
      printf("This is an invalid row number.\n");
    else //if user enter a number but out of range
      printf("There is no row #%d on this flight.\n", *row);
    printf("Please try again.\n\n");
    printf("Please enter the row of the seat you wish to reserve: ");
    *row = getNumber();
  } //if the row is out of board, it will ask again
  
  printf("Please enter the seat letter you wish to reserve: ");
  *width = getchar();
  skipAllTrailingChar(*width);
} //ask users for row number and width letter


int isFullPlane(int flightNumber, Plane* plane)
{
  for(int row = 0; row < plane->rows; row++)
  {
    for (int col = 0; col < plane->width; col++)
    {
      if (plane->passengers[row][col] == (char*) NULL)
      {
        return 0;
      } //if this seat is not occupied
    } //iterate every col
  } //iterate every row
  
  printf("We are sorry but Flight #%d is full.\n", flightNumber);
  return 1;
} //determine if a plane is full or not

