#ifndef PLANE_H
#define	PLANE_H
#include <fstream>

using namespace std;
#define MAX_NAME_SIZE 80
#define FIRST_ROW 1
#define FIRST_SEAT 'A'
#define ROW_SPACE 2

class Plane
{
  int rows;
  int width;
  int reserved;
  char ***passengers;
  int getRow() const;
  void showGrid() const;
public:
  Plane(ifstream &inf);
  ~Plane();
  int addPassenger();
  void writePlane(ofstream &outf) const;
}; // class Plane

#endif	// PLANE_H


