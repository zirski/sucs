// Useful libraries to include
#include <cctype>
#include <fstream>
#include <iostream>
#include <string>

#include "queue.h"
#include "stack.h"

using namespace std;

bool isPal(string text);
string sanitizeLine(string line);

int main()
{
  ifstream in("/home/fac/sreeder/class/cs1430/p5x.dat");
  if (!in) {
    cerr << "Error opening file" << endl;
    return 1;
  }

  string line;
  int numPhrases = 0, numPals = 0;
  while (getline(in, line) && !line.empty()) {
    if (isPal(sanitizeLine(line))) {
      cout << "\"\033[32m" << line << "\033[37m\" is a palindrome." << endl;
      numPals++;
    } else {
      cout << "\"" << line << "\" is not a palindrome." << endl;
    }
    numPhrases++;
  }

  cout << endl << "Number of words read: " << numPhrases << endl;
  cout << "Number of palindromes found: " << numPals << endl;
  return 0;
}

bool isPal(string text)
{
  Queue forward;
  Stack reverse;

  for (size_t i = 0; i < text.length(); i++) {
    char c = tolower(text[i]);
    forward.enqueue(c);
    reverse.push(c);
  }

  bool match = true;
  while (!forward.isEmpty())
    if (forward.dequeue() != reverse.pop())
      match = false;
  return match;
}

string sanitizeLine(string line)
{
  for (size_t i = 0; i < line.length(); i++)
    if (isspace(line.at(i)) || ispunct(line.at(i)))
      line.erase(i, 1);
  return line;
}
