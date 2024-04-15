// Toby Hammond
// lab2.cpp
// Purpose: prints a Pascal's triangle using iterative and recursive techniques,
// and allows the user to ask for a value in the last row of the triangle.
// Measures time complexity of program.

#include <chrono>
#include <iomanip>
#include <iostream>
#include <ratio>

using namespace std::chrono;
using namespace std;

const int NUM_TESTS = 21;
const int AVG_SAMPLE_SIZE = 100;

// Iteratively populates a 2d array containing a
// pascal's triangle, the width and height of the array being d elements wide
// and deep. extra elements are populated with 0s. The function returns the
// array.
int** iterativePascal(int degree);
int** recursivePascal(int degree);
// Indexes into a dynamically allocated array t (created by recursivePascal) and
// returns t[d - 1][i].
int recursiveBico(int d, int i);
// prints value-initialized elements of 2d array arr.
void printList(int** arr, int size);

int main()
{
  // int index, degree;
  int** triangle = nullptr;

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

  cout << endl << "Iterative tests:" << endl;
  for (int i = 0; i < NUM_TESTS; i++) {
    int avgSum = 0;

    for (int j = 0; j < AVG_SAMPLE_SIZE; j++) {
      auto start = high_resolution_clock::now();
      triangle = iterativePascal(i);
      auto stop = high_resolution_clock::now();

      avgSum += duration_cast<nanoseconds>(stop - start).count();
    }

    cout << "iterativePascal(" << i << "): " << avgSum / AVG_SAMPLE_SIZE << "ns"
         << endl;

    for (int j = 0; j < i; j++)
      delete[] triangle[j];
    delete[] triangle;
  }

  cout << endl << "Recursive tests:" << endl;
  for (int i = 0; i < NUM_TESTS; i++) {
    int avgSum = 0;

    for (int j = 0; j < AVG_SAMPLE_SIZE; j++) {
      auto start = high_resolution_clock::now();
      triangle = recursivePascal(i);
      auto stop = high_resolution_clock::now();

      avgSum += duration_cast<nanoseconds>(stop - start).count();
    }

    cout << "recursivePascal(" << i << "): " << avgSum / AVG_SAMPLE_SIZE << "ns"
         << endl;

    for (int j = 0; j < i; j++)
      delete[] triangle[j];
    delete[] triangle;
  }

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
