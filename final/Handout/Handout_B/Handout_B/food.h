#ifndef FOOD_H
#define FOOD_H

#include <iostream>
#include <fstream>
#include <string>

using namespace std;

class Food
{
protected:
  int calories;
  int Dietary_Fiber;
  string name;
public:
  Food():calories(0), Dietary_Fiber(0), name("\0"){};
  ~Food();
  string getName() const {return name;};
  virtual void read(ifstream& inf);
  virtual void display();
  friend ifstream& operator>> (ifstream& inf, Food& food);
}; // class Food


class FattyFood : public Food
{
  float Saturate_Fat;
public:
  FattyFood():Food(), Saturate_Fat(0){};
  void read(ifstream& inf);
  void display();
  friend ifstream& operator>> (ifstream& inf, FattyFood& fattyFood);
}; // class FattyFood

#endif // FOOD_H
