// Toby Hammond
// lab3.cpp

#include <cstdint>
#include <cstdio>
#include <iostream>
#include <random>

using namespace std;

int main() {
  int regvar;
  int *ptrvar = nullptr;

  // Step 1
  cout << "Please enter an integer: ";
  // Error handling
  cin >> regvar;

  // Step 2
  ptrvar = &regvar;
  // Step 3
  cout << "Value (according to the normal variable): " << regvar << endl;
  cout << "Address (according to the normal variable): " << &regvar << endl;
  cout << "Value (according to the pointer): " << *ptrvar << endl;
  cout << "Address (according to the pointer): " << ptrvar << endl;

  // Step 4
  ptrvar = new int;
  // Step 5
  *ptrvar = 2;
  // Step 6
  cout << "Value (according to the normal variable): " << regvar << endl;
  cout << "Address (according to the normal variable): " << &regvar << endl;
  cout << "Value (according to the pointer): " << *ptrvar << endl;
  cout << "Address (according to the pointer): " << ptrvar << endl;

  // Step 7
  delete ptrvar;

  int size = 0;
  // Step 8
  cout << "Please enter an integer between 1 and 50: ";
  cin >> size;
  ptrvar = new int[size];
  // Step 9 (I know it's overkill but I want to get practice with what seems to
  // be accepted convention for rng in c++)
  random_device r;
  mt19937 g(r());
  uniform_int_distribution<uint_least32_t> distribute(1, size);
  for (int i = 0; i < size; i++)
    ptrvar[i] = distribute(g);

  // Step 10
  for (int i = 0; i < size; i++) {
    cout << ptrvar[i] << " ";
  }
  cout << endl;

  // Step 11
  delete[] ptrvar;
  return 0;
}
