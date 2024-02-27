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
const int SHORT_SLEEP = 50;
const int LONG_SLEEP = 1200;

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
  cout << endl
       << "----------------------------------"
       << "STACK TESTS"
       << "----------------------------------" << endl;

  cout << "Creating Stack s1" << endl;
  Stack s1;
  SLEEP(400);
  cout << "Populating s1 with 25 random chars: ";
  for (int i = 0; i < INITIAL_NUM_CHARS; i++) {
    cout << initialValues[i] << " ";
    s1.push(initialValues[i]);
  }
  SLEEP(LONG_SLEEP);
  cout << endl << "Making new stack s2 from s1" << endl;
  Stack s2(s1);
  SLEEP(LONG_SLEEP);
  cout << "Popping all values from s2:" << endl;
  print(s2);
  SLEEP(LONG_SLEEP);
  cout << "Attempting to pop one more value from s2:" << endl;
  SLEEP(LONG_SLEEP);
  try {
    cout << s2.pop();
  } catch (Stack::emptyStackException) {
    cout << "Error: Tried to pop off am empty stack" << endl;
  }
  SLEEP(LONG_SLEEP);
  cout << "Populating s2 with 30 new random chars: " << endl;
  for (int i = 0; i < NEW_NUM_CHARS; i++) {
    cout << moreValues[i] << " ";
    s2.push(moreValues[i]);
  }
  SLEEP(LONG_SLEEP);
  cout << endl << "Copying s2 to s1" << endl;
  s1 = s2;
  SLEEP(LONG_SLEEP);
  cout << "Popping values from both stacks until empty" << endl;
  cout << "s2:" << endl;
  string chars;
  char c;
  while (!s2.isEmpty()) {
    c = s2.pop();
    chars += c;
    chars += ' ';
    cout << "\r" << chars << flush << endl << "\33[1A";
    SLEEP(SHORT_SLEEP);
  }
  cout << chars << endl;
  chars.clear();
  cout << "s1:" << endl;
  while (!s1.isEmpty()) {
    c = s1.pop();
    chars += c;
    chars += ' ';
    cout << "\r" << chars << flush << endl << "\33[1A";
    SLEEP(SHORT_SLEEP);
  }
  cout << chars << endl;
  chars.clear();
  SLEEP(LONG_SLEEP);

  // Refreshing pools of chars
  for (int i = 0; i < INITIAL_NUM_CHARS; i++)
    initialValues[i] = distribute(g);
  for (int i = 0; i < NEW_NUM_CHARS; i++)
    moreValues[i] = distribute(g);

  cout << endl
       << endl
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
