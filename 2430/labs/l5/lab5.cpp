#include <algorithm>
#include <chrono>
#include <exception>
#include <iomanip>
#include <iostream>
#include <random>
#include <vector>

using namespace std;

void heapSort(int* A, int n);
void mergeSort(int* A, int i, int n);
void merge(int* A, int p, int q, int r);
void quickSort(int* A, int n);
void printArray(int* A, int n);
void measureSort(void (*sortingFunction)(int*, int));

class MinHeap {
public:
  vector<int> arr;
  void insert(int n)
  {
    arr.push_back(n);
    percolate_up(arr.size() - 1);
  }
  int peekMin()
  {
    return arr.at(0);
  }
  void deleteMin()
  {
    if (arr.size() > 0) {
      swap(arr[0], arr[arr.size() - 1]);
      arr.pop_back();
      percolate_down(0);
    }
  }

private:
  void percolate_up(int i)
  {
    if (i != 0) {
      int parent = (i - 1) / 2;
      if (arr[parent] > arr[i]) {
        swap(arr[parent], arr[i]);
        percolate_up(parent);
      }
    }
  }
  void percolate_down(int i)
  {
    if (i * 2 + 2 < arr.size()) {
      int lesserChildIndex =
          (arr[i * 2 + 1] < arr[i * 2 + 2]) ? i * 2 + 1 : i * 2 + 2;
      if (arr[lesserChildIndex] < arr[i]) {
        swap(arr[lesserChildIndex], arr[i]);
        percolate_down(lesserChildIndex);
      }
    } else if (i * 2 + 1 < arr.size() && arr[i * 2 + 1] < arr[i]) {
      swap(arr[i * 2 + 1], arr[i]);
      percolate_down(i * 2 + 1);
    }
  }
  void swap(int& a, int& b)
  {
    int tmp = a;
    a = b;
    b = tmp;
  }
};

// different sorting algorithms defined here
// add other functions as needed
void heapSort(int* A, int n)
{
  MinHeap h;
  for (int i = 0; i < n; i++)
    h.insert(A[i]);
  int i = 0;
  while (true) {
    try {
      A[i++] = h.peekMin();
      h.deleteMin();
    } catch (exception& e) {
      break;
    }
  }
}

void mergeSort(int* A, int i, int n)
{
  if (i < n) {
    int mid = (i + n) / 2;
    mergeSort(A, i, mid);
    mergeSort(A, mid + 1, n);
    merge(A, i, mid, n);
  }
}

// p: start index
// q: middle index (end of first unsorted array)
// q: end index
void merge(int* A, int p, int q, int r)
{
  int* tmp = new int[r - p + 1];
  int i = p;
  int j = q + 1;

  int index = 0;
  while (i <= q && j <= r) {
    if (A[i] < A[j])
      tmp[index++] = A[i++];
    else
      tmp[index++] = A[j++];
  }

  while (i <= q)
    tmp[index++] = A[i++];
  while (j <= r)
    tmp[index++] = A[j++];

  index = 0;
  for (int k = p; k <= r; k++)
    A[k] = tmp[index++];
}

void quickSort(int* A, int n)
{
  // quick sort
}

void printArray(int* A, int n)
{
  for (int i = 0; i < n; i++)
    cout << A[i] << " ";
  cout << endl;
}

void measureSort(void (*sortingFunction)(int*, int))
{
  int size[] = {10, 100, 1000, 10000, 100000};
  for (int i = 0; i < 5; i++) {
    // allocate memory for the array
    int* array = new int[size[i]];
    // fill in array with random numbers
    for (int j = 0; j < size[i]; j++) {
      array[j] = rand() % 100000;
    }
    // display size 10 random array
    if (size[i] == 10) {
      cout << "Random array: " << endl;
      printArray(array, size[i]);
    }
    // Call the sorting function (make sure to
    // start with a new unsorted array each time)
    // and measure the execution time here
    chrono::time_point<chrono::high_resolution_clock> start =
        chrono::high_resolution_clock::now();
    sortingFunction(array, size[i]);
    chrono::time_point<chrono::high_resolution_clock> stop =
        chrono::high_resolution_clock::now();
    int duration =
        chrono::duration_cast<chrono::nanoseconds>(stop - start).count();
    // display size 10 sorted array
    if (size[i] == 10) {
      cout << "Sorted array: " << endl;
      printArray(array, size[i]);
    }
    // display the time measurement with units
    cout << "Array size " << size[i] << " duration: ";
    cout << duration << " ns.";
    delete[] array;
  }
}

int main()
{
  int size = 30;
  int* arr = new int[size];
  random_device r;
  mt19937 g(r());
  uniform_int_distribution<> distribute(1, 20);

  for (int i = 0; i < size; i++) {
    arr[i] = distribute(g);
    cout << setw(2) << arr[i] << " ";
  }
  cout << endl;
  mergeSort(arr, 0, size);
  for (int i = 0; i < size; i++)
    cout << setw(2) << arr[i] << " ";
  cout << endl;

  // // function pointer
  // void (*sortingFunction)(int*, int);
  // cout << endl << "HEAP SORT" << endl;
  // sortingFunction = &heapSort;
  // measureSort(sortingFunction);
  // cout << endl << "MERGE SORT" << endl;
  // sortingFunction = &mergeSort;
  // measureSort(sortingFunction);
  // cout << endl << "QUICK SORT" << endl;
  // sortingFunction = &quickSort;
  // measureSort(sortingFunction);
}
