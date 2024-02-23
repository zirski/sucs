#include "queue.h"

#include <cstddef>

Queue::Queue() : h(nullptr), t(nullptr)
{
}

Queue::Queue(const Queue& src)
{
  h = nullptr;
  t = nullptr;
  if (src.h != nullptr) {
    Node* tmp = src.h;
    h = new Node;
    t = h;
    while (tmp != nullptr) {
      t->c = tmp->c;
      tmp = tmp->next;
      t->next = new Node;
      t = t->next;
    }
  }
}

Queue& Queue::operator=(const Queue& rhs)
{
  if (this != &rhs) {
    // old list deletion
    t = nullptr;
    Node* delptr = nullptr;
    while (h != nullptr) {
      delptr = h;
      h = h->next;
      delete delptr;
    }
    h = nullptr;

    // List copying
    Node* tmp = rhs.h;
    h = new Node;
    t = h;
    while (tmp != nullptr) {
      t->c = tmp->c;
      tmp = tmp->next;
      t->next = new Node;
      t = t->next;
    }
  }
  return *this;
}

Queue::~Queue()
{
  t = nullptr;
  Node* delptr = nullptr;
  while (h != nullptr) {
    delptr = h;
    h = h->next;
    delete delptr;
  }
  h = nullptr;
}

void Queue::enqueue(char c)
{
  Node* insert = new Node;
  insert->c = c;
  insert->next = nullptr;

  if (h == t) {
    h = insert;
    t = insert;
  } else {
    t->next = insert;
    t = insert;
  }
}

char Queue::dequeue()
{
  if (h == nullptr)
    throw emptyQueueException();
  Node* d = h;
  char c = h->c;
  h = h->next;
  delete d;
  return c;
}

bool Queue::isEmpty()
{
  return h == nullptr;
}
