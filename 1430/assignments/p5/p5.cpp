// Useful libraries to include
#include <cctype>
#include <fstream>
#include <iostream>
#include <string>

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
  int numWords = 0;
  int numPals = 0;
  while (in >> word) {
    if (isPal(word)) {
      cout << word << " is a palindrome." << endl;
      numPals++;
    }
    numWords++;
  }

  cout << endl << "Number of words read: " << numWords << endl;
  cout << "Number of palindromes found: " << numPals << endl;
  return 0;
}
