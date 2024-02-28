// Toby Hammond
// queue.h
// Purpose: Linked list-implemented queue. isEmpty is available  the user,
// but methods within this class throw emptyQueueException when needed anyway.

#ifndef QUEUE_H
#define QUEUE_H

class Queue {
public:
  Queue();
  Queue(const Queue& src);
  Queue& operator=(const Queue& rhs);
  ~Queue();
  void enqueue(char c);
  // Throws emptyQueueException if user attempts to dequeue on an empty queue.
  char dequeue();
  bool isEmpty();
  class emptyQueueException {};

private:
  struct Node {
    char c;
    Node* next;
  };

  Node* h;
  Node* t;
};

#endif
