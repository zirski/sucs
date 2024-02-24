#include <chrono>
#include <exception>
#include <iostream>
#include <random>
#include <string>
#include <thread>

#include "queue.h"
#include "stack.h"

#define SLEEP100 (this_thread::sleep_for(chrono::milliseconds(100)))

using namespace std;

const int NUM_ELEMENTS = 20;

void removeChars(Queue q, int reps);
void removeChars(Stack s, int reps);
void print(Stack s);
void print(Queue q);

int main()
{
  Queue myQueue;
  random_device r;
  mt19937 g(r());
  uniform_int_distribution<int> distribute('A', 'Z');

  // Tests
  cout << "Creating Stack s1" << endl;
  Stack s1;
  SLEEP100;
  cout << "Populating s1 with 20 random values" << endl;
  for (int i = 0; i < NUM_ELEMENTS; i++) {
    char c = distribute(g);
    cout << "\r" << c << " -> s1";
    SLEEP100;
  }
  cout << endl;

  cout << "s1: ";
  print(s1);
}

void removeChars(Queue q, int reps)
{
  string chars;
  char c;
  try {
    for (int i = 0; i < reps; i++) {
      c = q.dequeue();
      chars.append(to_string(c) + " ");
      cout << "\r" << chars << flush;
      SLEEP100;
    }
  } catch (exception& e) {
    cout << "tried to dequeue from an empty queue" << endl;
  }
}

void removeChars(Stack s, int reps)
{
  string chars;
  char c;
  try {
    for (int i = 0; i < reps; i++) {
      c = s.pop();
      chars.append(to_string(c) + " ");
      cout << "\r" << chars << flush;
      SLEEP100;
    }
  } catch (exception& e) {
    cout << "Tried to pop from an empty stack" << endl;
  }
}

void print(Stack s)
{
  while (!s.isEmpty())
    cout << s.pop() << " ";
  cout << endl;
}

void print(Queue q)
{
  while (!q.isEmpty())
    cout << q.dequeue() << " ";
  cout << endl;
}
