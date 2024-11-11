#include <iostream>

using namespace std;

struct Node {
  int data;
  Node* next;
};

Node* addFront(Node* head, int val);
Node* addEnd(Node* head, int val);
int search(Node* head, int val);

int main()
{
  Node* root = nullptr;

  root = addFront(root, 3);
  root = addFront(root, 5);

  cout << search(root, 3);
  // Node* root = nullptr;
  // int menuInput, value;
  // cout << "Integer Linked List" << endl;
  // cout << "Please enter an option:" << endl;
  // do {
  //   cout << "1. Add Integer to Front" << endl;
  //   cout << "2. Add Integer to Back" << endl;
  //   cout << "3. Search For a Value" << endl;
  //   cout << "4. Quit" << endl << ":";
  //   cin >> menuInput;

  //   switch (menuInput) {
  //     case 1:
  //       cout << "Enter value: ";
  //       cin >> value;
  //       root = addFront(root, value);
  //       cout << "Done!" << endl;
  //       break;
  //     case 2:
  //       cout << "Enter value: ";
  //       cin >> value;
  //       root = addEnd(root, value);
  //       cout << "Done!" << endl;
  //       break;
  //     case 3:
  //       cout << "Enter search value: ";
  //       cin >> value;
  //       int index = search(root, value);
  //       if (index == 0)
  //         cout << "value not found" << endl;
  //       else
  //         cout << "value is at node " << index << endl;
  //   }
  // } while (menuInput != 4);

  // while (root != nullptr) {
  //   cout << root->data << " ";
  //   root = root->next;
  // }
  // cout << endl;
  // return 0;
}

Node* addFront(Node* head, int val)
{
  Node* ins = new Node;
  ins->data = val;
  ins->next = nullptr;

  if (head != nullptr)
    ins->next = head;
  return ins;
}

Node* addEnd(Node* head, int val)
{
  Node* ins = new Node;
  ins->data = val;
  ins->next = nullptr;

  if (head == nullptr)
    head = ins;
  else {
    Node* tmp = head;
    while (tmp->next != nullptr)
      tmp = tmp->next;
    tmp->next = ins;
  }
  return head;
}

int search(Node* head, int val)
{
  int ct = 1;
  while (head != nullptr && head->data != val) {
    head = head->next;
    ct++;
  }
  if (head != nullptr)
    return ct;
  else
    return 0;
}
