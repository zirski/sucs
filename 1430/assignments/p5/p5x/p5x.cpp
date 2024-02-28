// Useful libraries to include
#include <cctype>
#include <fstream>
#include <iostream>
#include <string>

#include "queue.h"
#include "stack.h"

using namespace std;

bool isPal(string word);

int main()
{
  // TODO: change filepath
  // ifstream in("/home/fac/sreeder/class/cs1430/p5.dat");
  ifstream in("p5.dat");
  if (!in) {
    cerr << "Error opening file" << endl;
    return 1;
  }

  string word;
  int numWords = 0, numPals = 0;
  while (in >> word) {
    if (isPal(word)) {
      cout << word << " is a palindrome." << endl;
      numPals++;
    } else {
      cout << word << " is not a palindrome." << endl;
    }
    numWords++;
  }

  cout << endl << "Number of words read: " << numWords << endl;
  cout << "Number of palindromes found: " << numPals << endl;
  return 0;
}

bool isPal(string word)
{
  Queue forward;
  Stack reverse;

  for (int i = 0; i < word.length(); i++) {
    char c = tolower(word[i]);
    forward.enqueue(c);
    reverse.push(c);
  }

  bool match = true;
  while (!forward.isEmpty())
    if (forward.dequeue() != reverse.pop())
      match = false;
  return match;
}
