
// Steven Li

#include <map>
#include <set>
#include <string>
#include <fstream>
#include <iostream>
#include <algorithm>
#include <iomanip>

using namespace std;

void initializeLetterMap(map<char, int>& letterMap);
void initializeWordMap(map<string, int>& wordMap, const
                       map<char, int>& letterMap);
int noSpaceScramble(string& line, set<string>& result, const
                    map<string, int>& wordMap);
int spaceScramble(string& line, set<string>& result, const map<string,
                  int>& wordMap, const map<char, int>& letterMap);
void printResult(string& line, const set<string>& result, int sum);
int insertSet(string& line, string& tempLine, set<string>& result, const
              map<string, int>& wordMap, const map<char, int>& letterMap,
              int temp, int occurrence, int i);

int main(int argc, const char * argv[])
{
  typedef map<char, int> LetterMap;
  LetterMap letterMap;
  initializeLetterMap(letterMap);
  typedef map<string, int> WordMap;
  WordMap wordMap;
  initializeWordMap(wordMap, letterMap);
  set<string> result;
  ifstream inf(argv[1]); string line, tempLine; int sum = 0;
  
  while(getline(inf, line, '\n'))
  {
    tempLine = line;
    
    if(line.length() <= 7 && line.find(" ") == string::npos)
      sum = noSpaceScramble(line, result, wordMap);
    else // if it has space
      if(line.length() <= 7 && line.find(" ") != string::npos)
        sum = spaceScramble(line, result, wordMap, letterMap);
    
    printResult(tempLine, result, sum);
    result.clear();
  } // while loop

  inf.close();
  return 0;
} // main()


void initializeLetterMap(map<char, int>& letterMap)
{
  int letterValueArr[26] = {1, 3, 3, 2, 1, 4, 2, 4, 2, 8, 5, 1, 3,
    1, 1, 3, 10, 1, 1, 1, 1, 4, 4, 8, 4, 10};
  
  for(int i = 0; i < 26; i++)
    letterMap.insert(pair<char, int>('a' + i, *(letterValueArr + i)));
} // initializeLetterMap()


void initializeWordMap(map<string, int>& wordMap, const
                       map<char, int>& letterMap)
{
  ifstream inf("words.txt"); string line;
  bool isValidWord; string::iterator sitr; int sum;
  
  while(getline(inf, line, '\n'))
  {
    isValidWord = true;
    
    if(line.length() > 7 || line.find_first_not_of("abcdefghijklmnopqrstuvwxyz")
       != string::npos) isValidWord = false;
    
    if(isValidWord)
    {
      sum = 0;
      
      for(sitr = line.begin(); sitr != line.end(); sitr++)
        sum += letterMap.find(*sitr)->second;
      
      wordMap.insert(pair<string, int> (line, sum));
    } // if valid
  } // while loop
    
  inf.close();
} // initializeWordMap()


int noSpaceScramble(string& line, set<string>& result, const
                    map<string, int>& wordMap)
{
  sort(line.begin(), line.end());
  string tempLine; int temp = 0;
  
  do
  {
    tempLine = line;
    
    for(int i = (int)tempLine.length(); i > 0; i = (int)tempLine.length())
    {
      if(wordMap.find(tempLine) != wordMap.end())
      {
        if(wordMap.find(tempLine)->second > temp)
        {
          result.clear();
          result.insert(tempLine);
          temp = wordMap.find(tempLine)->second;
        } // if it should be updated
        
        if(wordMap.find(tempLine)->second == temp && result.find(tempLine)
           == result.end()) result.insert(tempLine);
      } // if substring
      
      tempLine = tempLine.substr(0, tempLine.length() - 1);
    } // for loop
  } while (next_permutation(line.begin(), line.end())); // do while
  
  return temp;
} // noSpaceScramble()


int spaceScramble(string& line, set<string>& result, const map <string,
                  int>& wordMap, const map<char, int>& letterMap)
{
  string lineFreeze = line, tempLine; int temp = 0, occurrence;
  
  for(int i = 0 ; i < 26 ; i++)
  {
    replace(line.begin(), line.end(), ' ', (char)('a' + i));
    sort(line.begin(), line.end());
    occurrence = (int) count(line.begin(), line.end(), (char)('a' + i));
    
    do
    {
      tempLine = line;
      
      for(int j = (int)tempLine.length(); j > 0; j = (int)tempLine.length())
      {
        if(wordMap.find(tempLine) != wordMap.end())
          temp = insertSet(line, tempLine, result, wordMap, letterMap, temp,
                           occurrence, i);
        
        tempLine = tempLine.substr(0, tempLine.length() - 1);
      } // for loop
    } while (next_permutation(line.begin(), line.end())); // do while
    
    line = lineFreeze;
  } // for loop
  
  return temp;
} // spaceScramble()


int insertSet(string& line, string& tempLine, set<string>& result, const
              map<string, int>& wordMap, const map<char, int>& letterMap,
              int temp, int occurrence, int i)
{
  int sum = wordMap.find(tempLine)->second;
  
  if((int) count(line.begin(), line.end(), (char)('a' + i))
     == occurrence) sum -= letterMap.find((char)('a' + i))->second;
  
  if(sum > temp)
  {
    result.clear(); result.insert(tempLine); temp = sum;
  } // if it should be updated
  
  if(sum  == temp && result.find(tempLine) == result.end())
    result.insert(tempLine);
  
  return temp;
} // isertSet()

void printResult(string& line, const set<string>& result, int sum)
{
  set<string>::iterator itr;
  
  if(sum)
    cout << setw(2) << sum << " " << line << ":";
  else // seg fault
    cout << setw(2) << 0 << " " << line << ":";
  
  for(itr = result.begin(); itr != result.end(); itr++)
    cout << " " << *itr;
  
  if(result.empty())
    cout << " No words found.";
  
  cout << endl;
  
} // printResult()
