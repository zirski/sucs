#include <fstream>
#include <iostream>

using namespace std;

// const string FILENAME = "/home/fac/sreeder/class/cs1430/lab6.dat";
const string FILENAME = "lab6.dat";

struct Node {
  int data;
  Node *next;
};

void initList(Node *&h);
void insertInOrder(Node *&h, int d);
void removeDups(Node *h);
void printList(Node *h);
void deleteList(Node *&h);

int main() {
  Node *h = nullptr;
  initList(h);
  cout << "file read OK" << endl << endl;
  printList(h);
  removeDups(h);
  printList(h);
  deleteList(h);
}

void initList(Node *&h) {
  ifstream in(FILENAME);

  int num;
  while (in >> num) {
    insertInOrder(h, num);
  }
}

void insertInOrder(Node *&h, int d) {
  Node *insert = new Node;
  insert->data = d;
  insert->next = nullptr;

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

void removeDups(Node *h) {
  if (h == nullptr)
    return;
  else {
    Node *temp = h;
    while (temp != nullptr) {
      while (temp->next != nullptr && temp->next->data == temp->data) {
        Node *scout = temp->next;
        temp->next = scout->next;
        delete scout;
      }
      temp = temp->next;
    }
  }
}

void printList(Node *h) {
  Node *temp = h;
  while (temp != nullptr) {
    cout << temp->data << endl;
    temp = temp->next;
  }
  cout << endl;
}

void deleteList(Node *&h) {
  Node *del;
  while (h != nullptr) {
    del = h;
    h = h->next;
    delete del;
  }
}
