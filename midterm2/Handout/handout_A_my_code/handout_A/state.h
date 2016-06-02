#ifndef __STATE_H__
#define __STATE_H__

#include <iostream>
#include <fstream>
#include <cstring>

using namespace std;

class StateCode {
  char state[3];
protected:
  short areaCode;
public:
  StateCode(){}
  
  StateCode(const StateCode &sc)
  {
    strcpy(state, sc.state);
    areaCode = sc.areaCode;
  }
  
  const char* getState() const {return state;};
  
  istream& read(istream &is)
  {
    is >> state >> areaCode;
    return is;
  }
  
  short getAreaCode() const {return areaCode;};
  bool operator< (const StateCode &sc) const {return strcmp(state, sc.state) < 0;};
  bool operator== (const StateCode &sc) const {return strcmp(state, sc.state) == 0;};
    
};

class StateCodeLong: public StateCode {
  short count;
  short codes[40];
public:
  StateCodeLong(const StateCode &sc):StateCode(sc){
    count = 0;
    codes[0] = sc.getAreaCode();
  }
  
  const StateCodeLong& operator+=(const StateCode &sc)
  {
    count++;
    codes[count] = sc.getAreaCode();
    return *this;
  }
  
  friend ofstream& operator<<(ofstream& os, const StateCodeLong &scl)
  {
    os << scl.getState();
    for (int i=0; i <= scl.count; i++)
      os << " " << scl.codes[i];
    os << endl;
    return os;
  }
};

#endif