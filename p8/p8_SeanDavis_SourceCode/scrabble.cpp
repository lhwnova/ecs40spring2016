#include <map>
#include <set>
#include <string>
#include <fstream>
#include <algorithm>
#include <iostream>
#include <iomanip>
using namespace std;

typedef map <char, int>  LetterMap;
typedef map <string, int> WordMap;
const int MAX_PERMUTATIONS = 5040;
const int MAX_WORD_LENGTH = 7;

void setLetterValues(LetterMap &letterMap)
{
  short values[] = 
  {
    1, 3, 3, 2, 1, 4, 2, 4, 2, 8, 5, 1, 3, 1, 1, 3, 10, 1, 1, 1, 1, 4, 4, 8, 4,
    10
  };  // values

  for(char letter = 'a'; letter <= 'z'; letter++)
    letterMap.insert(LetterMap::value_type(letter, values[letter - 'a']));

}  // setLetterValues();


void readWords(const LetterMap &letterMap, WordMap &words)
{
  ifstream inf("words.txt");
  string word, sortedWord;
  short value;

  while( getline(inf, word))
  {
    if(word.length() <= MAX_WORD_LENGTH
       && word.find_first_not_of("abcedefghijklmnopqrstuvwxyz") == string::npos)
    {
      value = 0;

      for(string::const_iterator itr = word.begin(); itr != word.end(); itr++)
        value += (letterMap.find(*itr))->second;

      words.insert(WordMap::value_type(word, value));
    } // if word up to MAX_WORD_LENGTH characters and no captial letters.
  } // while
}  // readWords()


void writeResults(short bestCount, const set<string> &bestWords,
                  const string word)
{
  cout << setw(2) << bestCount << " " << word << ":";

  if(bestCount == 0)
  {
      cout << " No words found.\n";
      return;
  } // if no words

  for(set<string>::const_iterator itr = bestWords.begin();
      itr != bestWords.end(); itr++)
    cout << " " << *itr;

  cout <<  endl;
} // writeResults()


void processBlankWord(const WordMap &words, string &originalWord,
                      set<string> &bestWords, short &bestCount,
                      const LetterMap &letterMap,  
                      WordMap::const_iterator &itr,
                      char letter)
{
  int count = itr->second;

  if(std::count(itr->first.begin(), itr->first.end(),
     letter) > std::count(originalWord.begin(), originalWord.end(),
     letter)) // space used
     count -= letterMap.find(letter)->second;

  if(count >= bestCount)
  {
    if(count > bestCount)
    {
      bestWords.clear();
      bestCount = count;
    } // if better than those previous

    bestWords.insert(itr->first);
  } // if at least as good as previous
} // processBlankWord()


void processBlank(const WordMap &words, string &originalWord,
                  set<string> &bestWords, short &bestCount, 
                  const LetterMap &letterMap)
{
  bestCount = 0;

  string word = originalWord;
  int pos = word.find(' ');

  for(char letter = 'a'; letter <= 'z'; letter++)
  {
    string temp(1, letter);
    word.replace(pos, 1, temp);

    for(int i = 0; i <  MAX_PERMUTATIONS; i++)
    {
      for(unsigned int j = 1; j <= word.length(); j++)
      {
        string shortenedWord;
        shortenedWord.assign(word, 0, j);
        WordMap::const_iterator itr = words.find(shortenedWord);

        if(itr != words.end())
          processBlankWord(words, originalWord, bestWords, bestCount, 
                           letterMap, itr, letter);
      } // for each word size

      next_permutation(word.begin(), word.end());
    } // for i
  } // for each letter in blank
}  // processBlank()


void processNormal(const WordMap &words, string word, set<string> &bestWords,
                   short &bestCount)
{
  bestCount = 0;

  for(int i = 0; i <  MAX_PERMUTATIONS; i++)
  {
    for(unsigned int j = 1; j <= word.length(); j++)
    {
      string shortenedWord;
      shortenedWord.assign(word, 0, j);
      WordMap::const_iterator itr = words.find(shortenedWord);

      if(itr != words.end() && itr->second >= bestCount)
      {

        if(itr->second > bestCount)
        {
          bestWords.clear();
          bestCount = itr->second;
        } // if better than those previous

        bestWords.insert(itr->first);
      } // if at least as good as previous
    } // for each word size

    next_permutation(word.begin(), word.end());
  } // for i
}  // processNormal()


void processFile(const char *filename, const WordMap &words,
                 const LetterMap &letterMap)
{
  set <string> bestWords;
  string word;
  short bestCount;
  ifstream inf(filename);

  while(getline(inf, word))
  {
    if(word.find(' ') != string::npos)
      processBlank(words, word, bestWords, bestCount, letterMap);
    else // doesn't contain a space
      processNormal(words, word, bestWords, bestCount);

    writeResults(bestCount, bestWords, word);
  } // while
} // processFile()


int main(int argc, char** argv)
{
  LetterMap letterMap;
  WordMap words;
  setLetterValues(letterMap);
  readWords(letterMap, words);
  processFile(argv[1], words, letterMap);
  return 0;
} // main()

