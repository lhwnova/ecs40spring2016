#ifndef PLANE_H
#define	PLANE_H
#define TRUE 1

#include <iostream>

#define MAX_NAME_SIZE 80
#define FIRST_ROW 1
#define FIRST_SEAT 'A'

using namespace std;

class Plane
{
private:
  int rows;
  int width;
  int reserved;
  char ***passengers;
  void displayGrid() const;
public:
  ~Plane();
  Plane(ifstream &inf);
  void writePlane(ofstream &outf) const;
  int addPassenger();
  int getRow() const;
}; // Plane class

#endif
