#ifndef QUEUE_H
#define QUEUE_H

class Queue {
public:
  Queue();
  Queue(const Queue& src);
  Queue& operator=(const Queue& rhs);
  ~Queue();
  void enqueue(char c);
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
