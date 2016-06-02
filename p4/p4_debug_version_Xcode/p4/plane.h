//author: Steven Li

#ifndef PLANE_H
#define	PLANE_H
#include <fstream>

using namespace std;

class Plane
{
private:
  static const int EMPTY = -1;
  static const int INIT = 0;
  static const int LENT = 256;
  static const int THIRTY = 30;
  static const int FROW = 1;
  static const char FSEAT = 'A';
  int rows;
  int width;
  int reserved;
  int** passengers;
  int getRow() const;
  void showGrid() const;
  int totalPassenger() const;
public:
  void removeFlight(int const flightNumber);
  void removePassenger(int const flightNumber, char* const name);
  Plane();
  Plane(ifstream &inf, int const flightNum);
  ~Plane();
  void addFlight();
  bool addPassenger(int const flightNum);
  void writePlane(ofstream &outf, int const flightNum) const;
  void showPassenger() const; 
}; // class Plane

#endif	// PLANE_H


