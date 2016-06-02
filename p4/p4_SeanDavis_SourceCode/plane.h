#ifndef PLANE_H
#define	PLANE_H
#include <fstream>

using namespace std;


class Plane
{
  static const int EMPTY = -1;
  static const int FIRST_ROW = 1;
  static const int FIRST_SEAT = 'A';
  static const int TEN = 10;
  static const int ROW_SPACE = 2;
  int rows;
  int width;
  int reserved;
  int **passengers;
  int getRow() const;
  void showGrid() const;
  void showPassengers() const;
public:
  Plane();
  Plane(ifstream &inf, int flightNumber);
  ~Plane();
  void addFlight();
  int addPassenger(int flightNumber);
  void removePassenger(int flightNumber);
  void removePlane() const;
  void writePlane(ofstream &outf, int flightNumber) const;
}; // class Plane

#endif	// PLANE_H


