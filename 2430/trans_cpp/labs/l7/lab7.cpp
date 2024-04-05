#include <iostream>

using namespace std;

struct Node {
  int d;
  Node* next;
};

void insertInOrder(Node*& h, int num);
void printList(Node* h);
void deleteList(Node*& h);

int main()
{
  Node* list = nullptr;
  int input;
  char again;
  do {
    cout << "Please enter a number to be entered into the list: ";
    cin >> input;
    insertInOrder(list, input);
    cout << "Enter another number? (y/n): ";
    cin >> again;
  } while (again == 'y' || again == 'Y');

  cout << "Here is your list: " << endl;
  printList(list);
  deleteList(list);
  return 0;
}

void insertInOrder(Node*& h, int num)
{
  Node* ins = new Node;
  ins->d = num;

  if (h == nullptr || h->d > ins->d) {
    ins->next = h;
    h = ins;
  } else {
    Node* tmp = h;
    while (tmp->next != nullptr && tmp->next->d < ins->d)
      tmp = tmp->next;
    ins->next = tmp->next;
    tmp->next = ins;
  }
}

void printList(Node* h)
{
  Node* tmp = h;
  while (tmp != nullptr) {
    cout << tmp->d << " ";
    tmp = tmp->next;
  }
  cout << endl;
}

void deleteList(Node*& h)
{
  Node* delptr = nullptr;
  while (h != nullptr) {
    delptr = h;
    h = h->next;
    delete delptr;
  }
}
