// WordChecker.cpp
//
// ICS 46 Spring 2016
// Project #3: Set the Controls for the Heart of the Sun
//
// Replace and/or augment the implementations below as needed to meet
// the requirements.

#include "WordChecker.hpp"
#include <algorithm>


WordChecker::WordChecker(const Set<std::string>& words)
    : words{words}
{
}


bool WordChecker::wordExists(const std::string& word) const
{
  return words.contains(word);
}


std::vector<std::string> WordChecker::findSuggestions(const std::string& word) const
{
  std::vector<std::string> suggestions;
  
  if (!wordExists(word))
    {
      // swapping each adjaent pair of characters in the word
      swapAdjacentPairs(suggestions, word);

      // insert A-Z in between each adjacent pair of characters
      inBetweenInsertAZ(suggestions, word);

      // deleting each character from the word
      deleteEachChar(suggestions, word);

      // replacing each character with a letter from A-Z
      replaceCharAZ(suggestions, word);

      // splitting the word into a pair of words
      splitIntoPairs(suggestions, word);
    }

  return suggestions;
}


void WordChecker::swapAdjacentPairs(std::vector<std::string>& suggestions,
                                    const std::string& word) const
{
  for (int i = 0; i < word.size(); ++i)
    {
      std::string temp = word;
      std::swap(temp[i], temp[i+1]);
      if (wordExists(temp)) unique_push_back(suggestions,temp);
    }
}

void WordChecker::inBetweenInsertAZ(std::vector<std::string>& suggestions,
                         const std::string& word) const
{ 
  for (int i = 0; i < alphabet.size(); ++i)
    {
      std::string temp = alphabet[i] + word;
      if (wordExists(temp)) unique_push_back(suggestions,temp);
      std::string temp2 = word + alphabet[i];
      if (wordExists(temp2)) unique_push_back(suggestions,temp);
    }

  for (int i = 0; i < word.size(); ++i)
    {
      for (int j = 0; j < alphabet.size(); ++j)
        {
          std::string temp = word;
          temp.insert(i, alphabet[j]);
          if (wordExists(temp)) unique_push_back(suggestions,temp);
        }
    }
}

void WordChecker::deleteEachChar(std::vector<std::string>& suggestions,
                      const std::string& word) const
 {
   for (int i = 0 ; i < word.size(); ++i)
     {
       std::string temp = word;
       temp.erase(i, 1);
       if (wordExists(temp)) unique_push_back(suggestions,temp);
     }
 }

void WordChecker::replaceCharAZ(std::vector<std::string>& suggestions,
                     const std::string& word) const
 {
   for (int i = 0; i < word.size(); ++i)
     {
       for (int j = 0; j < alphabet.size(); ++j)
         {
           std::string temp = word;
           temp.replace(i, 1, alphabet[j]);
           if (wordExists(temp)) unique_push_back(suggestions, temp);
         }
     }
 }

void WordChecker::splitIntoPairs(std::vector<std::string>& suggestions,
                      const std::string& word) const
{
  for (int i = 0; i < word.size(); ++i)
    {
      std::string tempSplit = word;
      tempSplit.insert (i, " ");

      std::string temp1 = word;
      std::string temp2 = word;

      temp1.replace(i, word.size(), "");
      temp2.replace(0, i, "");

      if (wordExists(temp1) && wordExists(temp2))
        unique_push_back(suggestions, tempSplit);
    }
}

void WordChecker::unique_push_back(std::vector<std::string>& suggestions,
                                   const std::string& word) const
{
  for (int i = 0; i < suggestions.size(); ++i)
    if (word == suggestions[i]) return;

  suggestions.push_back(word);
}
