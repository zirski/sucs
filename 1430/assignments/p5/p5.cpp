#include <cctype>
#include <fstream>
#include <iostream>
#include <string>

#include "queue.h"
#include "stack.h"

using namespace std;

// isPal will return true if word is an empty string. Technically this makes
// sense...
bool isPal(string word);
// in needs to be a valid basic_istream
void processWords(ifstream& in);

int main()
{
  string finput;
  char playAgain;

  cout << "Welcome! this program takes a file of words and determines whether "
          "they are "
       << endl
       << "palindromes." << endl;

  do {
    cout << "Please enter a filepath: ";
    cin >> finput;
    // ifstream in("/home/fac/sreeder/class/cs1430/p5x.dat");
    ifstream in(finput);
    if (!in) {
      perror("Error"); 
      return 1;
    }
    processWords(in);
    in.close();
    cout << endl << "Evaluate another file? (y/n): ";
    cin >> playAgain;
  } while (playAgain != 'n' && playAgain != 'N');

  cout << "Goodbye!" << endl;
  return 0;
}

bool isPal(string word)
{
  Queue forward;
  Stack reverse;
  bool match = true;

  for (size_t i = 0; i < word.length(); i++) {
    char c = tolower(word[i]);
    forward.enqueue(c);
    reverse.push(c);
  }

  while (!forward.isEmpty())
    if (forward.dequeue() != reverse.pop())
      match = false;
  return match;
}

void processWords(ifstream& in)
{
  string word;
  int numWords = 0, numPals = 0;

  cout << endl;
  while (in >> word) {
    if (isPal(word)) {
      cout << "\033[32m" << word << "\033[37m is a palindrome." << endl;
      numPals++;
    } else {
      cout << word << " is not a palindrome." << endl;
    }
    numWords++;
  }
  cout << endl << "Number of words read: " << numWords << endl;
  cout << "Number of palindromes found: " << numPals << endl;
}
