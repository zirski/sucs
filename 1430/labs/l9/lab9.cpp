// Toby Hammond
// lab9.cpp
// Purpose: Takes a file of words and sorts them alphabetically. Then, provides
// a user with an interface with which they can search for a word.

#include <fstream>
#include <iomanip>
#include <iostream>
#include <string>

using namespace std;

const int LIST_SIZE = 50;
// const string FILENAME = "/home/fac/sreeder/class/cs1430/lab9.dat";
const string FILENAME = "lab9.dat";

void printArray(string arr[], int numElements);
// Insertion sort
void sortArray(string arr[], int numElements);
// Binary search
int searchArray(string arr[], string query, int numElements);

int main()
{
  ifstream in(FILENAME);
  string word;
  string words[LIST_SIZE];
  char playAgain;
  int numElements = 0;

  if (!in) {
    perror("Error");
    return 1;
  }

  // I'm using numElements first as an index-accessing variable, and the
  // immediately afterwards a counter for the number of elements.
  while (in >> word) {
    words[numElements++] = word;
  }
  cout << "Unsorted List: " << endl << endl;
  printArray(words, numElements);

  sortArray(words, numElements);

  cout << endl << "Sorted List: " << endl << endl;
  printArray(words, numElements);

  do {
    cout << endl << "Enter a word to search for; you will receive its index: ";
    cin >> word;
    int index = searchArray(words, word, numElements);
    if (index == -1) {
      cout << "Sorry, that word doesn't exist in the list." << endl;
      fflush(stdin);
    } else {
      cout << endl
           << "\"" << word << "\""
           << " is at index " << searchArray(words, word, numElements) << endl;
    }
    cout << "Search for another word? (y/n): ";
    cin >> playAgain;
  } while (playAgain != 'n' && playAgain != 'N');
  cout << "Thanks! Goodbye" << endl;
  return 0;
}

void printArray(string arr[], int numElements)
{
  cout << "Index  Value" << endl;
  for (size_t i = 0; i < numElements; i++)
    cout << left << setw(2) << i << "     " << arr[i] << endl;
}

void sortArray(string arr[], int numElements)
{
  int index;
  for (int i = 1; i < numElements; i++) {
    index = i;
    while (index > 0 && arr[index] < arr[index - 1]) {
      string temp = arr[index];
      arr[index] = arr[index - 1];
      arr[index - 1] = temp;
      index--;
    }
  }
}

int searchArray(string arr[], string query, int numElements)
{
  int high = numElements - 1;
  int low = 0;
  int mid = (high + low) / 2;

  while (arr[mid] != query && low <= high) {
    if (arr[mid] < query)
      low = mid + 1;
    else
      high = mid - 1;
    mid = (high + low) / 2;
  }
  if (arr[mid] != query)
    return -1;
  else {
    while (arr[mid] == arr[mid - 1])
      mid--;
    return mid;
  }
}
