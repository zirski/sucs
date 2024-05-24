#include <iostream>

using namespace std;

int partition(int arr[], int l, int h);
void quickSort(int arr[], int l, int h);

const int SIZE = 7;

int main()
{
  int list[] = {1, 20, 29, 17, 7, 3, 8};

  for (int i = 0; i < SIZE; i++)
    cout << list[i] << " ";
  cout << endl;

  quickSort(list, 0, SIZE);
}

int partition(int arr[], int l, int h)
{
  int p = arr[h];

  return p;
}
