
#ifndef SALE_H
#define SALE_H

#include <iostream>
#include <vector>
#include <string>

using namespace std;

class Sale
{
  float Sales_Tax;
  float total;
public:
  float getTotal() const {return total;};
  Sale(float sal, float tot): Sales_Tax(sal), total(tot){};
  virtual void display() const;
}; // class Sale


class CheckSale : public Sale
{
  int ABA_number;
  string Driver_License_number;
public:
  CheckSale(float sal, float tot, int aba, string dri):Sale(sal, tot), ABA_number(aba), Driver_License_number(dri){};
  void display() const;
}; // class CheckSale


#endif // SALE_H
