#include <cstdint>
#include <iomanip>
#include <iostream>
#include <random>

using namespace std;

int main() {
  random_device r;
  mt19937 g(r());
  uniform_int_distribution<> distribute(1, 99);
  int size;
  char playOrNot = 'y';

  while (playOrNot != 'n' || playOrNot != 'N') {
    cout << "Please enter a number between 3 and 10: ";
    cin >> size;
    cout << endl;
    int **arr = new int *[size];
    int *colSums = new int[size];
    int *diagSums = new int[2];
    for (int i = 0; i < size; i++) {
      arr[i] = new int[size];
      for (int j = 0; j < size; j++) {
        arr[i][j] = distribute(g);
        cout << setw(3) << arr[i][j] << " ";
      }
      cout << endl;
    }
    cout << endl;

    for (int i = 0; i < size; i++) {
      int rowSum = 0;
      diagSums[0] += arr[i][i];
      diagSums[1] += arr[i][(size - 1) - i];
      for (int j = 0; j < size; j++) {
        rowSum += arr[i][j];
        colSums[i] += arr[j][i];
      }
      cout << "Sum of row " << i << ": " << rowSum << endl;
    }
    cout << endl;

    for (int i = 0; i < size; i++)
      cout << "Sum of column " << i << ": " << colSums[i] << endl;
    cout << endl << "Sum of left-leaning diagonal: " << diagSums[0];
    cout << endl
         << "Sum of right-leaning diagonal: " << diagSums[1] << endl
         << endl;

    for (int i = 0; i < size; i++) {
      delete arr[i];
    }
    delete[] arr;
    cout << "Keep playing? (y/n): ";
    cin >> playOrNot;
    if (playOrNot == 'n' || playOrNot == 'N') {
      return 0;
    }
  }
}
