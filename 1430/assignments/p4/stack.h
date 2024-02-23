// Toby Hammond
// stack.h
// Purpose: Dynamic array stack. Can be resized in the event of stack overflow.

#ifndef STACK_H
#define STACK_H

class Stack {
public:
  Stack();
  Stack(const Stack& src);
  Stack& operator=(const Stack& rhs);
  ~Stack();
  void push(char c);
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
