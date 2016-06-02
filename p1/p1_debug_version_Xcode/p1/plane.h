#ifndef PLANE_H

#define PLANE_H
#define SEAT_BASE 'A'

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct
{
  int rows;
  int width;
  int reserved;
  char ***passengers;
} Plane;

void readPlane (FILE* fp_in, Plane** plane);
void writePlane(FILE* fp_out, Plane* plane);
void displayBoardPlane(Plane* plane);
void deletePlane(Plane* plane);
void changePlane(Plane** plane);
void getRowAndWidth(int* row, char* width, Plane* plane);
int isFullPlane(int flightNumber, Plane* plane);

#endif
