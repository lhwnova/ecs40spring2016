#include "food.h"

using namespace std;


void Food::read(ifstream& inf)
{
  inf >> *this;
} // read()


ifstream& operator>> (ifstream& inf, Food& food)
{
  inf >> food.calories >> food.Dietary_Fiber >> food.name;
  return inf;
}


void Food::display()
{
  cout << calories << " calories, " << Dietary_Fiber << "g fiber, and no fat. " << endl;
}


void FattyFood::read(ifstream& inf)
{
  inf >> *this;
  
} // read()


ifstream& operator>> (ifstream& inf, FattyFood& fattyFood)
{
  inf >> fattyFood.calories >> fattyFood.Dietary_Fiber >> fattyFood.Saturate_Fat >> fattyFood.name;
  return inf;
}


void FattyFood::display()
{
  cout << calories << " calories, " << Dietary_Fiber << "g fiber, " << Saturate_Fat << "g saturated fat. " << endl;
}

