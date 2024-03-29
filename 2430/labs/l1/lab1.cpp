// Toby Hammond
// lab1.cpp
// Purpose: prints a Pascal's triangle, and allows the user to ask for a value
// in the last row of the triangle. Does not store the whole triangle.

#include <iomanip>
#include <iostream>

using namespace std;

// Uses two arrays to create a pascal's triangle (one of the arrays 1 larger
// than the other). Does not store the whole triangle, just the requested tier.
void bico(int n, int i);
void printList(int arr[], int size);

int main()
{
  int degree, cint;

  cout << "Please input the degree of the binomial: ";
  cin >> degree;
  cout << "Plase input the index of the coefficient: ";
  cin >> cint;

  bico(degree, cint);
  return 0;
}

void bico(int n, int i)
{
  int size = 1;
  // Array for storing the base (and later reference) line.
  int* line = new int[size];
  // Array which adds up value pairs from line[], adhering to pascal's triangle
  // rules.
  int* next = new int[++size];
  line[0] = 1;
  printList(line, size);
  for (int i = 0; i < n; i++) {
    // For each element in next[], add the equivalent value from line[] and the
    // equivalent value - 1. If calculating for the first or last element,
    // simply add a single value.
    for (int j = 0; j < size; j++) {
      if (j == 0)
        next[j] = line[j];
      else if (j == size)
        next[j] = line[j - 1];
      else
        next[j] = line[j - 1] + line[j];
    }
    printList(next, size);
    // Refresh the two arrays: copy all values from next[] onto line[], then
    // delete next[] for the next iteration.
    delete[] line;
    line = new int[++size];
    for (int j = 0; j < size; j++)
      line[j] = next[j];
    delete[] next;
    next = new int[size];
  }
  cout << "The result is: " << line[i] << endl;
}

void printList(int arr[], int size)
{
  for (int i = 0; i < size; i++)
    cout << setw(2) << arr[i] << " ";
  cout << endl;
}
