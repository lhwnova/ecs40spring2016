
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>
#include <iterator>
#include "list.h"
#include "sale.h"

using namespace std;

int main() {
  ifstream inf("/Users/zhiyingli/Desktop/final_handout_A/final_handout_A/input.txt");
  //ifstream inf("input.txt");
  
  vector<Sale*> v;
  Sale* sale;
  float type, temp, tax, total = 0;
  int abaNum = 0;
  string driverLicense;
  List list;
  
  inf >> type;
  
  while(type == 0 || type == 1)
  {
    if(type == 1)
      inf >> abaNum >> driverLicense;
    
    inf >> tax;

    while(inf >> temp && temp != 0 && temp != 1)
      total += temp;
    
    total += tax;
    
    if(type == 1)
      sale = new CheckSale(tax, total, abaNum, driverLicense);
    else
      sale = new Sale(tax, total);
    
    type = temp;
    v.insert(v.end(), sale);
    total = 0;
  }
  
  for(vector<Sale*>::iterator itr = v.begin(); itr != v.end(); itr++)
    list.insert(*itr);
  
  list.print();
  inf.close();
  return 0;
}
