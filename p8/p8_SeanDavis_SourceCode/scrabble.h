#ifndef SCRABBLE_H
  #define SCRABBLE_H

#include <string>
#include <map>

using namespace std;

class Word
{
  string word;
  short count;
public:
  Word(const string &w = "", short c = 0);
  short getCount() const;
  bool operator< (const Word &rhs) const;
  const string& getString() const;
}; // class Word


typedef map<char, short> LetterMap;

#endif
