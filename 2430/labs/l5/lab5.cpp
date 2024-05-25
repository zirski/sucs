#include <chrono>
#include <iostream>

using namespace std;

// different sorting algorithms defined here
// add other functions as needed
void heapSort(int* A, int n)
{
  // heap sort
}
void mergeSort(int* A, int n)
{
  // merge sort
}
void quickSort(int* A, int n)
{
  // quick sort
}
void printArray(int* A, int n)
{
  // to be called to print unsorted and sorted
  // size 10 arrays
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
    // display size 10 random array if (size[i] == 10){
    cout << "Random array: " << endl;
    printArray(array, size[i]);
  }

  // Call the sorting function (make sure to
  // start with a new unsorted array each time)
  // and measure the execution time here
  auto start = ... sortingFunction(array, size[i]);
  auto stop = ... auto duration =
      ...
      // display size 10 sorted array if (size[i] == 10){
      cout
      << "Sorted array: " << endl;
  printArray(array, size[i]);
  // display the time measurement with units
  cout << "Array size " << size[i] << " duration: ";
  cout << duration << " ns.";
}
int main()
{
  // function pointer
  void (*sortingFunction)(int*, int);
  cout << endl << "HEAP SORT" << endl;
  sortingFunction = &heapSort;
  measureSort(sortingFunction);
  cout << endl << "MERGE SORT" << endl;
  sortingFunction = &mergeSort;
  measureSort(sortingFunction);
  cout << endl << "QUICK SORT" << endl;
  sortingFunction = &quickSort;
  measureSort(sortingFunction);
}
