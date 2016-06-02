#ifndef PLANE_H
#define	PLANE_H

#include <stdio.h>

#define MAX_NAME_SIZE 80
#define FIRST_ROW 1
#define FIRST_SEAT 'A'

typedef struct
{
  int rows;
  int width;
  int reserved;
  char ***passengers;
} Plane;

#endif	// PLANE_H

int addPassenger(Plane *plane);
void freePlane(Plane* plane);
int getRow(Plane *plane);
void readPlane(Plane* plane, FILE *fp);
void showGrid(Plane *plane);
void writePlane(Plane* plane, FILE *fp);
