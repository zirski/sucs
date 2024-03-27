#include <cstdio>
#include <fstream>
#include <iostream>
#include <string>

using namespace std;

struct Person {
  string name;
  int age;
  int coffee;
};

const string FILENAME = "/home/fac/sreeder/class/online/lab5input.dat";
const int LIST_SIZE = 150;

Person findOldest(Person arr[], int size);
Person findSmallestCoffeeIntake(Person arr[], int size);
void sortList(Person arr[], int size);
void printList(Person arr[], int size);
void printRecord(Person p);

int main()
{
  ifstream in(FILENAME);
  Person list[LIST_SIZE];
  int ct = 0;

  if (!in) {
    perror("Error: ");
    return 1;
  }

  while (!in.eof()) {
    in >> list[ct].name >> list[ct].age >> list[ct].coffee;
    ct++;
  }

  cout << "Oldest Person: " << endl;
  printRecord(findOldest(list, ct));
  cout << "Person who drinks the least coffee:" << endl;
  printRecord(findSmallestCoffeeIntake(list, ct));
  cout << endl;
  printList(list, ct);
  cout << "Sorting list..." << endl;
  sortList(list, ct);
  cout << endl;
  printList(list, ct);
  return 0;
}

Person findOldest(Person arr[], int size)
{
  int o = 0;

  for (int i = 0; i < size; i++)
    if (arr[i].age > arr[o].age)
      o = i;
  return arr[o];
}

Person findSmallestCoffeeIntake(Person arr[], int size)
{
  int c = 0;

  for (int i = 0; i < size; i++)
    if (arr[i].coffee < arr[c].coffee)
      c = i;
  return arr[c];
}

void sortList(Person arr[], int size)
{
  for (int i = 1; i < size; i++) {
    int index = i;
    while (index > 0 && arr[index].name > arr[index - 1].name) {
      Person tmp = arr[index];
      arr[index] = arr[index - 1];
      arr[index - 1] = tmp;
    }
  }
}

void printList(Person arr[], int size)
{
  for (int i = 0; i < size; i++) {
    cout << i + 1 << endl;
    printRecord(arr[i]);
    cout << endl;
  }
}

void printRecord(Person p)
{
  cout << "Name: " << p.name << endl;
  cout << "Age: " << p.age << endl;
  cout << "Cofee Intake Per Day: " << p.coffee << endl;
}
