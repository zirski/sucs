// Toby Hammond
// stack.cpp
// Purpose: Dynamic array-implemented stack.

#include "stack.h"

Stack::Stack() : size(DEFAULT_SIZE), top(0)
{
  arr = new char[size];
}

Stack::Stack(const Stack& src) : size(src.size), top(src.top)
{
  arr = new char[size];
  for (int i = 0; i < size; i++)
    arr[i] = src.arr[i];
}

Stack& Stack::operator=(const Stack& rhs)
{
  if (this != &rhs) {
    delete[] arr;
    size = rhs.size;
    top = rhs.top;
    arr = new char[size];

    for (int i = 0; i < size; i++)
      arr[i] = rhs.arr[i];
  }
  return *this;
}

Stack::~Stack()
{
  delete[] arr;
}

void Stack::push(char c)
{
  if (top == size)
    resize();
  arr[top++] = c;
}

char Stack::pop()
{
  if (top == 0)
    throw emptyStackException();
  else {
    return arr[--top];
  }
}

bool Stack::isEmpty()
{
  return top == 0;
}

void Stack::resize()
{
  int newSize = size * 1.5;
  char* tmp = new char[newSize];
  for (int i = 0; i < size; i++)
    tmp[i] = arr[i];
  size = newSize;
  delete[] arr;
  arr = tmp;
}
