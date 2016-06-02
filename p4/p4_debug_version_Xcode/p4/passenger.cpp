#include <fstream>
#include <ostream>
#include <cstring>
#include "passenger.h"

void Passenger::copyPassengers()
{
  ifstream readIn;
  readIn.open("passengers.dat", ios::binary | ios::in);
  ofstream writeOut;
  writeOut.open("passengers2.dat", ios::binary | ios::out);
  readIn.seekg (ZERO, readIn.end);
  int length = readIn.tellg();
  readIn.seekg (ZERO, readIn.beg);
  writeOut.seekp(ZERO, writeOut.beg);
  Passenger pas;

  while(readIn.tellg() < length)
  {
  	readIn.read((char*)&pas, sizeof(Passenger));
  	writeOut.write((char*)&pas, sizeof(Passenger));
  } //

  readIn.close();
  writeOut.close();
} //

Passenger::Passenger()
{
}; //

Passenger::Passenger(short fN, short ro, char se, char* nam)
{
  flightNum = fN;
  row = ro;
  seat = se;
  strcpy(name, nam);
} //
