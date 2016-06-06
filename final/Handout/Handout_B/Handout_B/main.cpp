#include <fstream>
#include <iostream>
#include <map>
#include <algorithm>
#include "food.h"
#include "list.h"

using namespace std;

int main()
{
  //ifstream inf("/Users/zhiyingli/Desktop/Handout_B/Handout_B/food.txt");
  ifstream inf("food.txt");
  
  char type;
  Food* food;
  List<Food*> list;
  typedef map<string, Food*> FoodMap;
  FoodMap foodMap;
  
  inf >> type;
  
  while(!inf.eof())
  {
    if(type == 'N')
      food = new Food();
    else
      food = new FattyFood;
    
    food->read(inf);
    foodMap.insert(pair<string, Food*>(food->getName(), food));
    list.insert(food);
    inf >> type;
  }
  
  inf.close();
  
  string userInput;
  //********** use map  to find **************
  do{
    cout << "Food (Done to end): " ;
    cin >> userInput;
    
    if(userInput == "Done")
      break;
    
    food = list.findFood(userInput);
    
    if(food)
      food->display();
    else
      cout << "Name nof found." << endl;
  } while(true);
  
  //********** use list to find **************
  FoodMap::iterator itr;
  
  do{
    cout << "Food (Done to end): " ;
    cin >> userInput;
    itr = foodMap.find(userInput);
    
    if(userInput == "Done")
      break;
    
    if(itr != foodMap.end() && itr->first == userInput)
      itr->second->display();
    else
      cout << "Name nof found." << endl;
    
  } while(true);
  
  return 0;
}
