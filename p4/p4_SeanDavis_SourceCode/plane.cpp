// Author: Sean Davis

#include <cstring>
#include <cctype>
#include <iostream>
#include <fstream>
#include <iomanip>
#include "plane.h"
#include "utilities.h"
#include "passenger.h"

using namespace std;


Plane::Plane()
{
}  // Plane()


Plane::Plane( ifstream &inf, int flightNumber) :reserved( 0 )
{
  int row, seatNum;
  char comma;
  Passenger passenger;
  inf >> rows >> comma >> width;
  passengers = new int* [rows];
  
  for(row = 0; row < rows; row++)
  {
    passengers[row] = new int[width];
    
    for(seatNum = 0; seatNum < width; seatNum++)
      passengers[row][seatNum] = EMPTY;
  } // for each row
  
  ifstream inf2("passengers.dat", ios::binary);
  
  while(inf2.read((char*) &passenger, sizeof(Passenger)))
  {
    if(passenger.flightNum == flightNumber)
    {
      passengers[passenger.row - FIRST_ROW][passenger.seat - FIRST_SEAT] 
        = (int) inf2.tellg() - sizeof(Passenger);
      reserved++;
    }  // if the passenger is on this flight
  }  // while more in file
  
  inf2.close();
}  // Plane()


Plane::~Plane()
{
  int row;
  
  for(row = 0; row < rows; row++)
    delete passengers[row];
  
  delete [] passengers;
}  // ~Plane()


void Plane::addFlight()
{
  cout << "Rows: ";
  cin >> rows;
  cout << "Width: ";
  cin >> width;
  cin.ignore(TEN, '\n');  
  passengers = new int* [rows];
  
  for(int row = 0; row < rows; row++)
  {
    passengers[row] = new int[width];
    
    for(int seatNum = 0; seatNum < width; seatNum++)
      passengers[row][seatNum] = EMPTY;
  } // for each row
}  // addFlight()


int Plane::addPassenger(int flightNumber)
{
  int row, seatNum;
  char name[Passenger::NAME_LENGTH], seat;
  
  if(reserved == rows * width)
    return 0;  // false
  
  cout << "Please enter the name of the passenger: ";
  cin.getline(name, Passenger::NAME_LENGTH);
  showGrid();
  
  while(true)
  {
    row = getRow();
    cout << "Please enter the seat letter you wish to reserve: ";
    seat = cin.get();
    seatNum = seat - FIRST_SEAT;

    while(cin.get() != '\n');

    if(passengers[row - FIRST_ROW][seatNum] == EMPTY)
      break;

    printf("That seat is already occupied.\nPlease try again.\n");
  } // while occupied seat
  
  ofstream outf("passengers2.dat", ios::binary | ios::app);
  passengers[row - FIRST_ROW][seatNum] = outf.tellp();
  Passenger passenger(flightNumber, row, seat, name);
  outf.write((char*) &passenger, sizeof(Passenger));
  reserved++;
  return 1;
}  // addPassenger()


int Plane::getRow() const
{
  int row;
  
  do
  {
    cout << "\nPlease enter the row of the seat you wish to reserve: ";
    row = getNumber();

    if(row == ERROR)
      cout << "That is an invalid row number.\nPlease try again.\n";
    else  // valid row number
      if(row < 1 || row > rows)
        cout << "There is no row #" << row 
          << " on this flight.\nPlease try again.\n"; 
          
  }  while(row < 1 || row > rows);
  
  return row;
} // getRow()


void Plane::showGrid() const
{
  int row, seatNum = 0;
  
  cout << "ROW# ";
  
  for(seatNum = 0; seatNum < width; seatNum++)
    cout << char(seatNum + FIRST_SEAT);
  
  cout << endl;
  
  for(row = 0; row < rows; row++)
  {
    cout << right << setw(ROW_SPACE) << row + 1 << "   ";
    
    for(seatNum = 0; seatNum < width; seatNum++)
      if(passengers[row][seatNum] != EMPTY)
        cout << 'X';
      else  // empty seat
        cout << '-';
    
    cout << endl;
  }  // for each row
  
  cout << "\nX = reserved.\n";
}  // showGrid()


void Plane::removePassenger(int flightNumber)
{
  char name[Passenger::NAME_LENGTH];
  Passenger passenger;
  cout << "Passengers on Flight #" << flightNumber << endl;
  showPassengers();
  fstream inOutf("passengers2.dat", ios::binary | ios::in | ios::out);
  cout << "\nName of passenger to remove: ";
  cin.getline(name, Passenger::NAME_LENGTH);
  bool found = false;
  
  for(int row = 0; !found && row < rows; row++)
    for(int seatNum = 0; !found && seatNum < width; seatNum++)
      if(passengers[row][seatNum] != EMPTY)
      {
        inOutf.seekg(passengers[row][seatNum], ios::beg);
        inOutf.read((char*) &passenger, sizeof(Passenger));
        
        if(strcmp(passenger.name, name) == 0)
        {
          passenger.flightNum = EMPTY;
          inOutf.seekp(passengers[row][seatNum], ios::beg);
          inOutf.write((char*) &passenger, sizeof(Passenger));
          passengers[row][seatNum] = EMPTY;
          found = true;
        }  // if found name
      }  // if seat not empty
  
  inOutf.close();
}  // removePassenger()


void Plane::removePlane() const
{
  Passenger passenger;
  fstream inOutf("passengers2.dat", ios::binary | ios::in | ios::out);

  for(int row = 0; row < rows; row++)
    for(int seatNum = 0; seatNum < width; seatNum++)
      if(passengers[row][seatNum] != EMPTY)
      {
        inOutf.seekg(passengers[row][seatNum], ios::beg);
        inOutf.read((char*) &passenger, sizeof(Passenger));
        passenger.flightNum = EMPTY;
        inOutf.seekp(passengers[row][seatNum], ios::beg);
        inOutf.write((char*) &passenger, sizeof(Passenger));
      }  // if seat not empty
  
}  // removePlane()


void Plane::showPassengers() const
{
  Passenger passenger;
  ifstream inf("passengers2.dat", ios::binary);
  
  for(int row = 0; row < rows; row++)
    for(int seatNum = 0; seatNum < width; seatNum++)
      if(passengers[row][seatNum] != EMPTY)
      { 
        inf.seekg(passengers[row][seatNum], ios::beg);
        inf.read((char*) &passenger, sizeof(Passenger));
        cout << passenger.name << endl;
      }  // if not EMPTY

   inf.close();
}  // showPassengers()


void Plane::writePlane(ofstream &outf, int flightNumber) const
{
  int row, seatNum;
  Passenger passenger;
  outf << rows << ',' << width << endl;
  
  ifstream inf("passengers2.dat", ios::binary);
  ofstream outf2("passengers3.dat", ios::binary | ios::app);

  for(row = 0; row < rows; row++)
    for(seatNum = 0; seatNum < width; seatNum++)
      if(passengers[row][seatNum] != EMPTY)
      {
        inf.seekg(passengers[row][seatNum], ios::beg);
        inf.read((char*) &passenger, sizeof(Passenger));
        outf2.write((char*) &passenger, sizeof(Passenger));
      }  // if seat not empty
}  // readPlane()

