// Author: Sean Davis

#include <string.h>
#include <ctype.h>
#include <iostream>
#include <fstream>
#include <iomanip>
#include "plane.h"
#include "passenger.h"
#include "utilities.h"

using namespace std;


void Plane::removeFlight(int const flightNumber)
{
  int length;
  fstream inOutF("passengers2.dat", ios::binary | ios::in | ios::out);
  inOutF.seekg(INIT, inOutF.end);
  length = inOutF.tellg();
  inOutF.seekg(INIT, inOutF.beg);

  int currentPos;
  Passenger passe;

  while (inOutF.tellg() < length)
  {
    currentPos = inOutF.tellg();
    inOutF.read((char*)&passe, sizeof(Passenger));

    if(passe.flightNum == flightNumber)
    {
      passengers[passe.row - 1][passe.seat - FSEAT] = EMPTY;
      passe.flightNum = EMPTY;
      inOutF.seekp(currentPos);
      inOutF.write((char*)&passe, sizeof(Passenger));
    } //
  } //

  inOutF.close();
} //


void Plane::removePassenger(int const flightNumber, char* const name)
{
  int length;
  fstream inOutF("passengers2.dat", ios::binary | ios::in | ios::out);
  inOutF.seekg(INIT, inOutF.end);
  length = inOutF.tellg();
  inOutF.seekg(INIT, inOutF.beg);

  int currentPos;
  Passenger passe;

  while (inOutF.tellg() < length)
  {
    currentPos = inOutF.tellg();
    inOutF.read((char*)&passe, sizeof(Passenger));

    if(passe.flightNum == flightNumber)
    {
      if(strcmp(passe.name, name) == 0)
      {
        passengers[passe.row - 1][passe.seat - FSEAT] = EMPTY;
        passe.flightNum = EMPTY;
        inOutF.seekp(currentPos);
        inOutF.write((char*)&passe, sizeof(Passenger));
        break;
      }   //
    }  //
  } //

  inOutF.close();
} //


void Plane::showPassenger() const
{
  int row, seatNum;
  
  ifstream readIn;
  readIn.open("passengers2.dat", ios::binary | ios::in);

  Passenger passe;

  for(row = 0; row < rows; row++)
    for(seatNum = 0; seatNum < width; seatNum++)
    {
      if(passengers[row][seatNum] != EMPTY)
      {
        readIn.seekg(passengers[row][seatNum]);
        readIn.read((char*)&passe, sizeof(Passenger));
        cout <<  passe.name  << endl;      
      } //
    } //
  
  readIn.close();

} //

void Plane::addFlight()
{
  cout << "Rows: ";
  rows = getNumber();
  cout << "Width: ";
  width = getNumber();

  int row, seatNum;
  passengers = new int* [rows];
  
  for(row = 0; row < rows; row++)
  {
    passengers[row] = new int[width];
    
    for(seatNum = 0; seatNum < width; seatNum++)
      passengers[row][seatNum] = EMPTY;
  }// 
}//


Plane::Plane()
{
}; //

Plane::Plane( ifstream &inf, int const flightNum)
{
  int row, seatNum, pos;
  inf >> rows;
  inf.ignore(LENT, ',');
  inf >> width;
  passengers = new int* [rows];
  
  for(row = 0; row < rows; row++)
  {
    passengers[row] = new int[width];
    
    for(seatNum = 0; seatNum < width; seatNum++)
      passengers[row][seatNum] = EMPTY;
  } // for each row
  
  ifstream readIn;
  readIn.open("passengers2.dat", ios::binary | ios::in);
  readIn.seekg (INIT, readIn.end);
  int length = readIn.tellg();
  readIn.seekg (INIT, readIn.beg);
  Passenger passe;

  while(readIn.tellg() < length)
  {
    pos = readIn.tellg();
    readIn.read((char*)&passe, sizeof(Passenger));

    if (passe.flightNum == flightNum)
      passengers[passe.row - 1][passe.seat - FSEAT] = pos;

  }//

  readIn.close();
}  // Plane()


Plane::~Plane()
{
  for(int row = 0; row < rows; row++) delete [] passengers[row];
  
  delete [] passengers;
}  // ~Plane()

int Plane::totalPassenger() const
{
  int count = 0;

  for(int i = 0; i < rows; i++)
  {
    for(int j = 0; j < width; j++)
    {
      if(passengers[i][j] != EMPTY)
      {
        count++;
      }//
    }//
  }//

  return count;
} //

bool Plane::addPassenger(int const flightNum)
{
  int row, seatNum;
  char name[THIRTY];
  
  if(totalPassenger() == rows * width)
    return false;
  
  cout << "Please enter the name of the passenger: ";
  cin.getline(name, THIRTY);
  showGrid();
  
  while(true)
  {
    row = getRow();
    cout << "Please enter the seat letter you wish to reserve: ";
    seatNum = cin.get() - FSEAT;
    
    while(cin.get() != '\n');
    
    if(passengers[row - FROW][seatNum] == EMPTY)
      break;
    
    printf("That seat is already occupied.\nPlease try again.\n");
  } // while occupied seat
  
  Passenger passe(flightNum, row, seatNum + FSEAT, name);
  ofstream writeOut;
  writeOut.open("passengers2.dat", ios::binary | ios::app);
  writeOut.seekp(INIT, writeOut.end);
  int a = writeOut.tellp();
  writeOut.write((char*)&passe, sizeof(Passenger));
  passengers[row - FROW][seatNum] = a;
  writeOut.close();
  return true;
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
  
  printf("ROW# ");
  
  for(seatNum = 0; seatNum < width; seatNum++)
    cout << char(seatNum + FSEAT);
  
  putchar('\n');
  
  for(row = 0; row < rows; row++)
  {
    printf("%2d   ", row + 1);
    
    for(seatNum = 0; seatNum < width; seatNum++)
      if(passengers[row][seatNum] != EMPTY)
        putchar('X');
      else  // empty seat
        putchar('-');
    
    putchar('\n');
  }  // for each row
  
  printf("\nX = reserved.\n");
}  // showGrid()


void Plane::writePlane(ofstream &outf, int const flightNum) const
{
  int row, seatNum;

  outf << rows << ',' << width << endl;
  Passenger passe;

  ofstream writeOut;
  writeOut.open("passengers3.dat", ios::binary | ios::app);
  ifstream readIn;
  readIn.open("passengers2.dat", ios::binary | ios::in);

  for(row = 0; row < rows; row++)
    for(seatNum = 0; seatNum < width; seatNum++)
    {
      if(passengers[row][seatNum] != EMPTY)
      {
        readIn.seekg(passengers[row][seatNum]);
        readIn.read((char*)&passe, sizeof(Passenger));

        if (passe.flightNum != EMPTY)
          writeOut.write((char*)&passe, sizeof(Passenger));
      } //
    } //
  
  readIn.close();
  writeOut.close();
}  // readPlane()
