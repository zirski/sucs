#include <iostream>
#include <random>

#include "queue.h"
#include "stack.h"

using namespace std;

const int NUM_ELEMENTS = 100;

void displayStack(Stack s);

int main()
{
  Stack myStack;
  Queue myQueue;
  random_device r;
  mt19937 g(r());
  uniform_int_distribution<int> distribute('A', 'Z');

  for (int i = 0; i < NUM_ELEMENTS; i++)
    myStack.push(distribute(g));

  for (int i = 0; i < NUM_ELEMENTS + 1; i++) {
    try {
      cout << myStack.pop() << endl;
    } catch (exception& e) {
      cout << e.what() << endl;
      return 0;
    }
  }
}
