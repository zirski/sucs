// Toby Hammond
// lab10.cpp
// Purpose: Recursive number-finder. From a randomly-generated linked list of
// integers, finds the last occurence of a negative number and prints the value.

#include <iostream>
#include <random>

using namespace std;

struct Node {
  int data;
  Node* next;
};

const int LIST_SIZE = 10;

// Generates a linked list of 10 randomly-generated integers.
Node* generateList();
// Prints the last occurence of a negative integer in list h.
// PRE: h cannot be nullptr.
void printLastNegative(Node* h, bool& found);
// Prints entire list with elements separated by spaces.
void printList(Node* h);
void deleteList(Node* h);

int main()
{
  Node* list = generateList();
  bool found = false;
  cout << "List: ";
  printList(list);
  cout << "Last negative element: ";
  printLastNegative(list, found);
  cout << endl;
  deleteList(list);
  return 0;
}

Node* generateList()
{
  random_device r;
  mt19937 g(r());
  uniform_int_distribution<int> distribute(-20, 20);

  Node* h = new Node;
  h->data = distribute(g);
  Node* tmp = h;

  for (int i = 0; i < LIST_SIZE; i++) {
    Node* n = new Node;
    n->data = distribute(g);
    n->next = nullptr;
    tmp->next = n;
    tmp = tmp->next;
  }
  return h;
}

void printLastNegative(Node* h, bool& found)
{
  if (h != nullptr) {
    printLastNegative(h->next, found);
    if (h->data < 0 && !found) {
      cout << h->data;
      found = true;
    }
  } else
    return;
}

void printList(Node* h)
{
  Node* tmp = h;
  while (tmp != nullptr) {
    cout << tmp->data << " ";
    tmp = tmp->next;
  }
  cout << endl;
}

void deleteList(Node* h)
{
  Node* delptr = nullptr;
  while (h != nullptr) {
    delptr = h;
    h = h->next;
    delete delptr;
  }
}
