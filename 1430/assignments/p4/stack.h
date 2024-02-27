// Toby Hammond
// stack.h
// Purpose: Dynamic array-implemented stack. Can be resized in the event of
// stack overflow. isEmpty is available to the user, but methods within this
// class throw emptyStackException when needed anyway.

#ifndef STACK_H
#define STACK_H

class Stack {
public:
  Stack();
  Stack(const Stack& src);
  Stack& operator=(const Stack& rhs);
  ~Stack();
  void push(char c);
  // Throws emptyStackException if user attempts to pop off an empty stack.
  char pop();
  bool isEmpty();
  class emptyStackException {};

private:
  void resize();
  static const int DEFAULT_SIZE = 50;
  int size;
  char* arr;
  int top;
};

#endif
