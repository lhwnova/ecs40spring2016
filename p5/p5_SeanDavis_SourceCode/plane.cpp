// Author: Sean Davis

#include <string.h>
#include <ctype.h>
#include <iostream>
#include <fstream>
#include <iomanip>
#include "plane.h"
#include "utilities.h"
#include "passenger.h"
#include "linkedlist.h"

using namespace std;


Plane::Plane(int flightNumb) : reserved( 0 ), flightNumber(flightNumb)
{
}  // Plane()


ifstream& operator>> (ifstream &inf, Plane &plane)
{
  int row;
  char comma;
  Passenger passenger;
  inf >> plane.rows >> comma >> plane.width;
  plane.passengers = new LinkedList [plane.rows];
  
  for(row = 0; row < plane.rows; row++)
    plane.passengers[row].initialize(plane.width);
  
  ifstream inf2("passengers.dat", ios::binary);
  
  while(inf2.read((char*) &passenger, sizeof(Passenger)))
  {
    if(passenger == plane.flightNumber)
    {
      plane.passengers[passenger.row - Plane::FIRST_ROW]
        [passenger.seat - Plane::FIRST_SEAT] 
        = (int) inf2.tellg() - sizeof(Passenger);
      plane.reserved++;
    }  // if the passenger is on this flight
  }  // while more in file
  
  inf2.close();
  return inf;
}  // Plane()


Plane::~Plane()
{
  delete [] passengers;
}  // ~Plane()


void Plane::addFlight()
{
  cout << "Rows: ";
  cin >> rows;
  cout << "Width: ";
  cin >> width;
  cin.ignore(TEN, '\n');  
  passengers = new LinkedList [rows];
  
  for(int row = 0; row < rows; row++)
    passengers[row].initialize(width);
}  // addFlight()


bool Plane::findPassenger(const char *name) const
{
  Passenger passenger;
  ifstream inf("passengers2.dat", ios::binary);
  
  for(int row = 0; row < rows; row++)
    for(int seatNum = 0; seatNum < width; seatNum++)
    {
      if(passengers[row][seatNum] != LinkedList::EMPTY)
      {
        inf.seekg(passengers[row][seatNum], ios::beg);
        inf.read((char*) &passenger, sizeof(Passenger));
        
        if(passenger == name)
        {
          cout << "Flight #" << flightNumber << " Row: " << row + FIRST_ROW 
            << " Seat: " << char(seatNum + FIRST_SEAT) << endl;
          return true;
        }  // if matched name
      } // if seat not empty
    }  // for each seat in row
      
  inf.close();
  return false;
}  // findPassenger()


Plane& Plane::operator++ ()
{
  int row, seatNum;
  char name[Passenger::NAME_LENGTH], seat;
  
  if(reserved == rows * width)
  {
    cout << "We are sorry but Flight #" << flightNumber << " is full.\n";
    return *this;
  } // if plane full 
  
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

    if(passengers[row - FIRST_ROW][seatNum] == LinkedList::EMPTY)
      break;

    printf("That seat is already occupied.\nPlease try again.\n");
  } // while occupied seat
  
  ofstream outf("passengers2.dat", ios::binary | ios::app);
  passengers[row - FIRST_ROW][seatNum] = outf.tellp();
  Passenger passenger(flightNumber, row, seat, name);
  outf.write((char*) &passenger, sizeof(Passenger));
  reserved++;
  return *this;
}  // opertor++


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
  int row, seatNum;
  cout << "ROW# ";
  
  for(seatNum = 0; seatNum <  width; seatNum++)
    cout << char (seatNum + FIRST_SEAT);
  
  cout << endl;
  
  for(row = 0; row < rows; row++)
  {
    cout << right << setw(ROW_SPACE) << row + FIRST_ROW;
    cout << "   " <<  passengers[row];
  }  // for each row
  
  cout << "\nX = reserved.\n";
}  // showGrid()




Plane& Plane::operator-- (int)
{
  char name[Passenger::NAME_LENGTH];
  Passenger passenger;
  cout << "Passengers on Flight #" << flightNumber << endl;
  cout << *this;
  fstream inOutf("passengers2.dat", ios::binary | ios::in | ios::out);
  cout << "\nName of passenger to remove: ";
  cin.getline(name, Passenger::NAME_LENGTH);
  bool found = false;
  
  for(int row = 0; !found && row < rows; row++)
    for(int seatNum = 0; !found && seatNum < width; seatNum++)
      if(passengers[row][seatNum] != LinkedList::EMPTY)
      {
        inOutf.seekg(passengers[row][seatNum], ios::beg);
        inOutf.read((char*) &passenger, sizeof(Passenger));
        
        if(passenger == name)
        {
          !passenger;
          inOutf.seekp(passengers[row][seatNum], ios::beg);
          inOutf.write((char*) &passenger, sizeof(Passenger));
          passengers[row][seatNum] = LinkedList::EMPTY;
          found = true;
          reserved--;
        }  // if found name
      }  // if seat not empty
  
  inOutf.close();
  return  *this;
}  // removePassenger()


const Plane& Plane::operator! () const
{
  Passenger passenger;
  fstream inOutf("passengers2.dat", ios::binary | ios::in | ios::out);

  for(int row = 0; row < rows; row++)
    for(int seatNum = 0; seatNum < width; seatNum++)
      if(passengers[row][seatNum] != LinkedList::EMPTY)
      {
        inOutf.seekg(passengers[row][seatNum], ios::beg);
        inOutf.read((char*) &passenger, sizeof(Passenger));
        !passenger;
        inOutf.seekp(passengers[row][seatNum], ios::beg);
        inOutf.write((char*) &passenger, sizeof(Passenger));
      }  // if seat not empty

  return *this;
}  // operator!()


ostream& operator<< (ostream &os, const Plane &plane)
{
  Passenger passenger;
  ifstream inf("passengers2.dat", ios::binary);
  
  for(int row = 0; row < plane.rows; row++)
    for(int seatNum = 0; seatNum < plane.width; seatNum++)
      if(plane.passengers[row][seatNum] != LinkedList::EMPTY)
      { 
        inf.seekg(plane.passengers[row][seatNum], ios::beg);
        inf.read((char*) &passenger, sizeof(Passenger));
        os << passenger << endl;
      }  // if not LinkedList::EMPTY

   inf.close();
   
   return os;
}  // operator<<


void Plane::writePlane(ofstream &outf) const
{
  int row, seatNum;
  Passenger passenger;
  outf << rows << ',' << width << endl;
  
  ifstream inf("passengers2.dat", ios::binary);
  ofstream outf2("passengers3.dat", ios::binary | ios::app);

  for(row = 0; row < rows; row++)
    for(seatNum = 0; seatNum < width; seatNum++)
      if(passengers[row][seatNum] != LinkedList::EMPTY)
      {
        inf.seekg(passengers[row][seatNum], ios::beg);
        inf.read((char*) &passenger, sizeof(Passenger));
        outf2.write((char*) &passenger, sizeof(Passenger));
      }  // if seat not empty
}  // writePlane()

