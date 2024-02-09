// your name here
// lab5.cpp

#include <cstddef>
#include <fstream>
#include <iostream>

using namespace std;

struct Node {
  int data;
  Node *next;
};

const string FILENAME = "lab5.dat";

void insertInOrder(Node *&h, int d);
// inserts d into h in numerical order
// post: h may be changed

void printList(Node *h);
// prints all data on h to the screen in a column

void deleteList(Node *&h);
// post: each node of h deleted

int main() {
  Node *head = nullptr;
  ifstream inFile;
  int num;

  inFile.open(FILENAME);
  if (inFile.fail()) {
    cout << "file problem...exiting program...press enter...";
    cin.get();
  }

  while (inFile >> num)
    insertInOrder(head, num);

  inFile.close();

  cout << endl;
  printList(head);

  cout << endl << endl;

  deleteList(head);

  return 0;
}

void insertInOrder(Node *&h, int d) {
  Node *insert = new Node;
  insert->data = d;

  if (h == nullptr)
    h = insert;
  else if (h->data > insert->data) {
    insert->next = h;
    h = insert;
  } else {
    Node *temp = h;
    while (temp->next != nullptr && temp->next->data < insert->data)
      temp = temp->next;
    insert->next = temp->next;
    temp->next = insert;
  }
}

void printList(Node *h) {
  Node *temp = h;
  while (temp != nullptr) {
    cout << temp->data << endl;
    temp = temp->next;
  }
}

void deleteList(Node *&h) {
  Node *del;
  while (h != nullptr) {
    del = h;
    h = h->next;
    delete del;
  }
}
