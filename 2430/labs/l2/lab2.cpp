// Toby Hammond
// lab2.cpp
// Purpose: prints a Pascal's triangle using iterative and recursive techniques,
// and allows the user to ask for a value in the last row of the triangle.
// Measures time complexity of program.

#include <chrono>
#include <fstream>
#include <iomanip>
#include <iostream>

using namespace std::chrono;
using namespace std;

const int NUM_TESTS = 100;
const int AVG_SAMPLE_SIZE = 1000;

// Iteratively populates a 2d array containing a
// pascal's triangle, the width and height of the array being d elements wide
// and deep. The function returns the
// array.
int** iterativePascal(int degree);
// Achieves same result as iterativePascal, except populates each element using
// recursiveBico.
int** recursivePascal(int degree);
// Recursively generates the coefficient for the requested index of a specific
// degree-raised binomial.
int recursiveBico(int d, int i);
// prints value-initialized elements of 2d array arr.
void printList(int** arr, int size);

int main()
{
  // int index, degree;
  int** triangle = nullptr;

  ofstream out("tests.csv");

  out << "degree,iterative(ns),recursive(ns)" << endl;
  for (int i = 0; i < NUM_TESTS; i++) {
    int avgSum = 0;

    for (int j = 0; j < AVG_SAMPLE_SIZE; j++) {
      auto start = high_resolution_clock::now();
      triangle = iterativePascal(i);
      auto stop = high_resolution_clock::now();

      avgSum += duration_cast<nanoseconds>(stop - start).count();
    }

    out << i << "," << avgSum / AVG_SAMPLE_SIZE << endl;
    avgSum = 0;

    for (int j = 0; j < i; j++)
      delete[] triangle[j];
    delete[] triangle;

    // for (int j = 0; j < AVG_SAMPLE_SIZE; j++) {
    //   auto start = high_resolution_clock::now();
    //   triangle = recursivePascal(i);
    //   auto stop = high_resolution_clock::now();

    //   avgSum += duration_cast<nanoseconds>(stop - start).count();
    // }

    // out << avgSum / AVG_SAMPLE_SIZE << endl;

    // for (int j = 0; j < i; j++)
    //   delete[] triangle[j];
    // delete[] triangle;
  }

  // cout << "Iterative Test: Please input the degree of the binomial: ";
  // cin >> degree;
  // cout << "Please input the desired index: ";
  // cin >> index;
  // while (index >= degree) {
  //   cout << "Error: not a valid index. Try again: ";
  //   cin >> index;
  // }

  // cout << "Lab 1, iterative pascal triangle:" << endl;
  // triangle = iterativePascal(degree);
  // printList(triangle, degree);

  // cout << "The result is: " << triangle[degree - 1][index] << endl << endl;

  // for (int i = 0; i < degree; i++)
  //   delete[] triangle[i];
  // delete[] triangle;
  // triangle = nullptr;

  // cout << "Lab 2, recursive pascal triangle:" << endl;
  // triangle = recursivePascal(degree);
  // printList(triangle, degree);
  // cout << "The result is: " << triangle[degree - 1][index] << endl;

  // for (int i = 0; i < degree; i++)
  //   delete[] triangle[i];
  // delete[] triangle;
  // triangle = nullptr;

  return 0;
}

int** iterativePascal(int degree)
{
  int** t = new int*[degree];
  for (int i = 0; i < degree; i++)
    t[i] = new int[degree];

  for (int i = 0; i < degree; i++) {
    for (int j = 0; j < i + 1; j++) {
      if (i == 0)
        t[i][j] = 1;
      else if (j == 0)
        t[i][j] = t[i - 1][j];
      else
        t[i][j] = t[i - 1][j] + t[i - 1][j - 1];
    }
  }
  return t;
}

int** recursivePascal(int degree)
{
  int** t = new int*[degree];
  for (int i = 0; i < degree; i++)
    t[i] = new int[degree];

  for (int i = 0; i < degree; i++)
    for (int j = 0; j < i + 1; j++)
      t[i][j] = recursiveBico(i, j);
  return t;
}

int recursiveBico(int d, int i)
{
  // If if the binomial has 1 degree, it's coefficient is always 1. Simliarly
  // resulting is when the index of the binomial is at index 0 or the end.
  if (d == 1 || i == 0 || i == d)
    return 1;
  else
    return recursiveBico(d - 1, i - 1) + recursiveBico(d - 1, i);
}

void printList(int** arr, int size)
{
  for (int i = 0; i < size; i++) {
    for (int j = 0; j < i + 1; j++) {
      cout << left << setw(2) << arr[i][j] << " ";
    }
    cout << endl;
  }
}
