
#include "sale.h"
#include <iomanip>

using namespace std;

void Sale::display() const
{
  cout << setw(8) << total << setw(8) << Sales_Tax;
}

void CheckSale::display() const
{
  Sale::display();
  cout << setw(9) << ABA_number << " " << Driver_License_number;
}