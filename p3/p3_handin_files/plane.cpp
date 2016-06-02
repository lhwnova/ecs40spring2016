#include <cstring>
#include <fstream>

#include "utilities.h"
#include "plane.h"

#define SPACE_OCCURE 1

using namespace std;

Plane::Plane(ifstream &inf)
{
  int row, numPassenger, seatNum;
  char seat, name[MAX_NAME_SIZE];
  inf >> rows >> width >> reserved;
  passengers = new char**[rows];
  
  for(row = 0; row < rows; row++)
  {
    passengers[row] = new char*[width];
    
    for(seatNum = 0; seatNum < width; seatNum++)
      passengers[row][seatNum] = NULL;
  } // for each row
  
  for(numPassenger = 0; numPassenger < reserved; numPassenger++)
  {
    inf >> row >> seat;
    inf.ignore(SPACE_OCCURE);
    inf.getline(name, MAX_NAME_SIZE);
    strtok(name, "\r\n");
    seatNum = seat;
    passengers[row - FIRST_ROW][seatNum - FIRST_SEAT]
    = new char[strlen(name) + 1];
    strcpy(passengers[row - FIRST_ROW][seatNum - FIRST_SEAT], name);
  }  // for each passenger
  
} // accessPlane

void Plane::displayGrid() const
{
  int row, seatNum = 0;
  
  cout << "ROW# ";
  
  for(seatNum = 0; seatNum < width; seatNum++)
    putchar(seatNum + FIRST_SEAT);
  
  putchar('\n');
  
  for(row = 0; row < rows; row++)
  {
    printf("%2d   ", row + 1);
    
    for(seatNum = 0; seatNum < width; seatNum++)
      if(passengers[row][seatNum])
        putchar('X');
      else  // empty seat
        putchar('-');
    
    putchar('\n');
  }  // for each r
  
  cout << "\nX = reserved." << endl;
} // displayGrid()

void Plane::writePlane(ofstream &outf) const
{
  int row, seatNum;
  outf << rows << " " << width << " " << reserved << endl;
  
  for(row = 0; row < rows ; row++)
    for(seatNum = 0; seatNum < width; seatNum++)
    {
      if(passengers[row][seatNum] != NULL)
      {
        outf << row + FIRST_ROW;
        outf << (char) (FIRST_SEAT + seatNum) << " ";
        outf << passengers[row][seatNum] << endl;
      } // if it is null
    } // a loop to delete menmory
} // writePlane()

Plane::~Plane()
{
  int row, seatNum;
  
  for(row = 0; row < rows; row++)
  {
    
    for(seatNum = 0; seatNum < width; seatNum++)
    {
      if(passengers[row][seatNum] != NULL)
      {
        delete [] passengers[row][seatNum];
      } // if NULL
    } // for to cheak null pointer
    
    delete [] passengers[row];
  }  // for row
  
  delete [] passengers;
}  // destruc Plane


int Plane::addPassenger()
{
  int row, seatNum;
  char name[MAX_NAME_SIZE];
  
  if(reserved == rows * width)
    return 0;  // false
  
  cout << "Please enter the name of the passenger: ";
  cin.getline(name, MAX_NAME_SIZE);
  strtok(name, "\r\n");
  displayGrid();
  
  while(TRUE)
  {
    row = getRow();
    cout << "Please enter the seat letter you wish to reserve: ";
    seatNum = cin.get() - FIRST_SEAT;
    
    while(cin.get() != '\n');
    
    if(passengers[row - FIRST_ROW][seatNum] == NULL)
      break;
    
    cout << "That seat is already occupied.\nPlease try again.\n";
  } // while occupied seat
  
  passengers[row - FIRST_ROW][seatNum] = new char[strlen(name) + 1];
  strcpy(passengers[row - FIRST_ROW][seatNum], name);
  reserved++;
  return 1;
}  // addPassenger()


int Plane::getRow() const
{
  int row;
  
  do
  {
    cout << "\nPlease enter the row of the seat you wish to reserve: ";
    row = (int) getNumber();
    
    if(row == ERROR)
      cout << "That is an invalid row number.\nPlease try again.\n";
    else  // valid row number
      if(row < 1 || row > rows)
        cout << "There is no row #" << row
        << " on this flight.\nPlease try again.\n";
  }  while(row < 1 || row > rows); // while to ask user
  
  return row;
} // getRow()
