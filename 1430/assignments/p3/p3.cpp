// Toby Hammond
// p3.cpp
// Purpose: Message descrambler. Takes a user-inputted file of integer-char
// pairs (the scrambled message), and sorts them according to their positions
// (as indicated by the integer in the pair). Then displays the message and asks
// the user for another file.

#include <fstream>
#include <iostream>

using namespace std;

const int SCREEN_WIDTH = 80;

struct Node {
  int pos;
  char c;
  Node* next;
};

// Inserts nodes in ascending order according to pos
// Pre: pos must be nonnegative
void insertInOrder(Node*& h, char c, int pos);
// Reads file of chars and their respective positions in the sentence (pos, c)
// into a singly-linked list. Returns false if file is not found, cannot be
// read, or is empty
bool initList(Node*& h, string filename);
// prints the character of each node in the list
void printMessage(Node* h);
// Frees up all memory allocated by the list
void deleteList(Node*& h);

int main()
{
  string filename;
  Node* list = nullptr;

  for (int i = 0; i < SCREEN_WIDTH; i++)
    cout << "-";

  cout << endl
       << "Professor Potter has given you a scrambled message, contained "
          "within a"
       << endl
       << "file. This program will take that file, descramble it and "
          "read the message back"
       << endl
       << "to you." << endl;
  for (int i = 0; i < SCREEN_WIDTH; i++)
    cout << "-";

  // Main gameplay loop
  char playAgain;
  do {
    cout << endl << "Please enter the name of your file: ";
    cin >> filename;
    cout << endl;

    while (!initList(list, filename)) {
      cout << "Please enter a valid file with a message to descramble: ";
      cin >> filename;
    }
    printMessage(list);
    deleteList(list);

    cout << endl << "Message descrambled! enter another one? (y/n): ";
    cin >> playAgain;
  } while (playAgain == 'y' || playAgain == 'Y');

  cout << endl << "*** Thank you for using me! ***" << endl;
  return 0;
}

void insertInOrder(Node*& h, char c, int pos)
{
  Node* ins = new Node;
  ins->c = c;
  ins->pos = pos;
  ins->next = nullptr;

  if (h == nullptr)
    h = ins;
  else if (h->pos > ins->pos) {
    ins->next = h;
    h = ins;
  } else {
    Node* temp = h;
    while (temp->next != nullptr && temp->next->pos < ins->pos)
      temp = temp->next;
    ins->next = temp->next;
    temp->next = ins;
  }
}

bool initList(Node*& h, string filename)
{
  ifstream in(filename);
  if (in && in.peek() != EOF) {
    string line;
    while (getline(in, line)) {
      insertInOrder(h, line.at(0), atoi(line.substr(2).c_str()));
    }
    return true;
  } else {
    return false;
  }
}

void printMessage(Node* h)
{
  Node* tmp = h;
  cout << "MESSAGE: [";
  while (tmp != nullptr) {
    cout << tmp->c;
    tmp = tmp->next;
  }
  cout << "]" << endl;
}

void deleteList(Node*& h)
{
  Node* del;
  while (h != nullptr) {
    del = h;
    h = h->next;
    delete del;
  }
}
