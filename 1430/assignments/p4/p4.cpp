#include <chrono>
#include <exception>
#include <iostream>
#include <random>
#include <string>
#include <thread>

#include "queue.h"
#include "stack.h"

#define SLEEP(X) (this_thread::sleep_for(chrono::milliseconds(X)))

using namespace std;

const int INITIAL_NUM_CHARS = 20;
const int NEW_NUM_CHARS = 30;
const int SHORT_SLEEP = 100;
const int LONG_SLEEP = 1000;

void removeChars(Queue& q, int reps);
void removeChars(Stack& s, int reps);
void print(Stack& s);
void print(Queue& q);

int main()
{
  random_device r;
  mt19937 g(r());
  uniform_int_distribution<int> distribute('A', 'Z');

  char* initialValues = new char[INITIAL_NUM_CHARS];
  char* moreValues = new char[NEW_NUM_CHARS];

  for (int i = 0; i < INITIAL_NUM_CHARS; i++)
    initialValues[i] = distribute(g);
  for (int i = 0; i < NEW_NUM_CHARS; i++)
    moreValues[i] = distribute(g);

  // Tests
  // cout << endl
  //      << "----------------------------------"
  //      << "STACK TESTS"
  //      << "----------------------------------" << endl;

  // cout << "Creating Stack s1" << endl;
  // Stack s1;
  // SLEEP(400);
  // cout << "Populating s1 with 25 random chars: ";
  // for (int i = 0; i < INITIAL_NUM_CHARS; i++) {
  //   cout << initialValues[i] << " ";
  //   s1.push(initialValues[i]);
  // }
  // SLEEP(LONG_SLEEP);
  // cout << endl << "Making new stack s2 from s1" << endl;
  // Stack s2(s1);
  // SLEEP(LONG_SLEEP);
  // cout << "Popping all values from s2:" << endl;
  // removeChars(s2, INITIAL_NUM_CHARS);
  // SLEEP(LONG_SLEEP);
  // cout << "Attempting to pop one more value from s2:" << endl;
  // SLEEP(LONG_SLEEP);
  // try {
  //   cout << s2.pop();
  // } catch (Stack::emptyStackException) {
  //   cout << "Error: Tried to pop off am empty stack" << endl;
  // }
  // SLEEP(LONG_SLEEP);
  // cout << "Populating s2 with 30 new random chars: " << endl;
  // for (int i = 0; i < NEW_NUM_CHARS; i++) {
  //   cout << moreValues[i] << " ";
  //   s2.push(moreValues[i]);
  // }
  // SLEEP(LONG_SLEEP);
  // cout << endl << "Copying s2 to s1" << endl;
  // s1 = s2;
  // SLEEP(LONG_SLEEP);
  // cout << "Popping values from both stacks until empty" << endl;
  // cout << "s2:" << endl;
  string chars;
  char c;
  // while (!s2.isEmpty()) {
  //   c = s2.pop();
  //   chars += c;
  //   chars += ' ';
  //   cout << "\r" << chars << flush << endl << "\33[1A";
  //   SLEEP(SHORT_SLEEP);
  // }
  // cout << chars << endl;
  // chars.clear();
  // cout << "s1:" << endl;
  // while (!s1.isEmpty()) {
  //   c = s1.pop();
  //   chars += c;
  //   chars += ' ';
  //   cout << "\r" << chars << flush << endl << "\33[1A";
  //   SLEEP(SHORT_SLEEP);
  // }
  // cout << chars << endl;
  // chars.clear();
  // SLEEP(LONG_SLEEP);

  // // Refreshing pools of chars
  // for (int i = 0; i < INITIAL_NUM_CHARS; i++)
  //   initialValues[i] = distribute(g);
  // for (int i = 0; i < NEW_NUM_CHARS; i++)
  //   moreValues[i] = distribute(g);

  cout << endl
       << "----------------------------------"
       << "QUEUE TESTS"
       << "----------------------------------" << endl;

  cout << "Creating Queue q1" << endl;
  Queue q1;
  SLEEP(400);
  cout << "Populating q1 with 25 random chars: ";
  for (int i = 0; i < INITIAL_NUM_CHARS; i++) {
    cout << initialValues[i] << " ";
    q1.enqueue(initialValues[i]);
  }
  SLEEP(LONG_SLEEP);
  cout << endl << "Making new Queue q2 from q1" << endl;
  Queue q2(q1);
  SLEEP(LONG_SLEEP);
  cout << "Dequeueing all values from q2:" << endl;
  print(q2);
  // removeChars(q2, INITIAL_NUM_CHARS);
  SLEEP(LONG_SLEEP);
  cout << "Attempting to dequeue one more value from q2:" << endl;
  SLEEP(LONG_SLEEP);
  try {
    cout << q2.dequeue();
  } catch (Queue::emptyQueueException) {
    cout << "Error: Tried to dequeue from am empty queue" << endl;
  }
  SLEEP(LONG_SLEEP);
  cout << "Populating q2 with 30 new random chars: " << endl;
  for (int i = 0; i < NEW_NUM_CHARS; i++) {
    cout << moreValues[i] << " ";
    q2.enqueue(moreValues[i]);
  }
  SLEEP(LONG_SLEEP);
  cout << endl << "Copying q2 to q1" << endl;
  q1 = q2;
  SLEEP(LONG_SLEEP);
  cout << "Dequeueing values from both queues until empty" << endl;
  cout << "q2:" << endl;

  while (!q2.isEmpty()) {
    c = q2.dequeue();
    chars += c;
    chars += ' ';
    cout << "\r" << chars << flush << endl << "\33[1A";
    SLEEP(SHORT_SLEEP);
  }

  cout << chars << endl;
  chars.clear();
  cout << "q1:" << endl;
  while (!q1.isEmpty()) {
    c = q1.dequeue();
    chars += c;
    chars += ' ';
    cout << "\r" << chars << flush << endl << "\33[1A";
    SLEEP(SHORT_SLEEP);
  }
  cout << chars << endl;
}

void removeChars(Queue& q, int reps)
{
  string chars;
  char c;
  try {
    for (int i = 0; i < reps; i++) {
      c = q.dequeue();
      chars += c;
      chars += ' ';
      cout << "\r" << chars << flush << endl << "\33[1A";
      SLEEP(SHORT_SLEEP);
    }
    cout << chars << endl;
  } catch (Queue::emptyQueueException) {
    cout << endl << "Error: tried to dequeue from an empty queue" << endl;
  }
}

void removeChars(Stack& s, int reps)
{
  string chars;
  char c;
  try {
    for (int i = 0; i < reps; i++) {
      c = s.pop();
      chars += c;
      chars += ' ';
      cout << "\r" << chars << flush << endl << "\33[1A";
      SLEEP(SHORT_SLEEP);
    }
    cout << chars << endl;
  } catch (Stack::emptyStackException) {
    cout << endl << "Error: Tried to pop from an empty stack" << endl;
  }
}

void print(Stack& s)
{
  while (!s.isEmpty())
    cout << s.pop() << " ";
  cout << endl;
}

void print(Queue& q)
{
  while (!q.isEmpty())
    cout << q.dequeue() << " ";
  cout << endl;
}
