// Toby Hammond
// p5.cpp
// Purpose: Palindrome detector. Takes a user-submitted filepath, and for each
// line of text in this file determines whether the line is a palindrome.
// Returns the list of lines, with palindromes noted and highlighted in green.

#include <cctype>
#include <fstream>
#include <iostream>
#include <string>

#include "queue.h"
#include "stack.h"

using namespace std;

// isPal will return true if text is an empty string. Technically this makes
// sense...
bool isPal(string text);
string sanitizeLine(string line);
// Pre: in needs to be a valid basic_istream
void processLines(ifstream& in);

int main()
{
  cout << "Welcome! this program takes a file of words/phrases and determines "
          "whether they"
       << endl
       << "are palindromes." << endl;

  string finput;
  char playAgain;

  do {
    cout << "Please enter a filepath: ";
    cin >> finput;
    ifstream in(finput);
    if (!in) {
      perror("Error");
      return 1;
    }

    processLines(in);
    in.close();

    cout << endl << "Evaluate another file? (y/n): ";
    cin >> playAgain;
  } while (playAgain != 'n' && playAgain != 'N');

  cout << "Goodbye!" << endl;
  return 0;
}

bool isPal(string text)
{
  Queue forward;
  Stack reverse;
  bool match = true;

  for (size_t i = 0; i < text.length(); i++) {
    char c = tolower(text[i]);
    forward.enqueue(c);
    reverse.push(c);
  }

  while (!forward.isEmpty())
    if (forward.dequeue() != reverse.pop())
      match = false;
  return match;
}

string sanitizeLine(string line)
{
  for (size_t i = 0; i < line.length(); i++)
    if (isspace(line.at(i)) || ispunct(line.at(i)))
      line.erase(i--, 1);
  return line;
}

void processLines(ifstream& in)
{
  string line;
  int numPhrases = 0, numPals = 0;

  cout << endl;
  while (getline(in, line) && !sanitizeLine(line).empty()) {
    if (isPal(sanitizeLine(line))) {
      cout << "\"\033[32m" << line << "\033[37m\" is a palindrome." << endl;
      numPals++;
    } else {
      cout << "\"" << line << "\" is not a palindrome." << endl;
    }
    numPhrases++;
  }

  cout << endl << "Number of phrases read: " << numPhrases << endl;
  cout << "Number of palindromes found: " << numPals << endl;
}
