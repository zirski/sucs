// Toby Hammond
// assignment1.cpp
// Purpose: Adoption center management system. Maintains a database of cats and
// dogs, into which users can put up pets for adoption or choose either a cat or
// dog to adopt (or simply the first pet added to the db).

#include <cstdio>
#include <iostream>
#include <iterator>
#include <string>
#include <vector>

using namespace std;

struct Pet {
  string type;
  string name;
};

void addCat(vector<Pet>& l, string n);
void addDog(vector<Pet>& l, string n);
bool adopt(vector<Pet>& l, Pet& p);
bool adopt(vector<Pet>& l, string c, Pet& p);

int main()
{
  int choice;
  Pet adoptee;
  vector<Pet> petList;
  do {
    cout << "Welcome to the animal shelter. What would you like to do?" << endl;
    cout << "1. Add a CAT to the shelter" << endl;
    cout << "2. Add a DOG to the shelter" << endl;
    cout << "3. Adopt a CAT from the shelter" << endl;
    cout << "4. Adopt a DOG from the shelter" << endl;
    cout << "5. Adopt any animal from the shelter" << endl;
    cout << "6. Exit" << endl << ":";

    cin >> choice;
    string dummy;
    getline(cin, dummy);

    switch (choice) {
      case 1: {
        string name;
        cout << "Please enter the CAT's name: ";
        getline(cin, name);
        addCat(petList, name);
        break;
      }
      case 2: {
        string name;
        cout << "Please enter the DOG's name: ";
        getline(cin, name);
        addDog(petList, name);
        break;
      }
      case 3:
        if (!adopt(petList, "cat", adoptee))
          cout << "Sorry, no cats are available for adoption today" << endl;
        else
          cout << "Congrats on adopting a cat, their name is " << adoptee.name
               << endl;
        break;
      case 4:
        if (!adopt(petList, "dog", adoptee))
          cout << "Sorry, no dogs are available for adoption today" << endl;
        else
          cout << "Congrats on adopting a dog, their name is " << adoptee.name
               << endl;
        break;
      case 5: {
        if (!adopt(petList, adoptee))
          cout << "Sorry, no animals are available for adoption today" << endl;
        else
          cout << "Congrats on adopting a " << adoptee.type
               << ", their name is: " << adoptee.name << endl;
        break;
      }
    }
    cout << endl;
  } while (choice != 6);
  return 0;
}

void addCat(vector<Pet>& l, string n)
{
  Pet p = Pet();
  p.type = "cat";
  p.name = n;

  l.push_back(p);
}

void addDog(vector<Pet>& l, string n)
{
  Pet p = Pet();
  p.type = "dog";
  p.name = n;

  l.push_back(p);
}

bool adopt(vector<Pet>& l, Pet& p)
{
  if (!l.empty()) {
    p = l.front();
    l.erase(l.begin());
    return true;
  }
  return false;
}

bool adopt(vector<Pet>& l, string c, Pet& p)
{
  if (!l.empty()) {
    vector<Pet>::iterator it = l.begin();
    // Steps through vector until it encounters the first instance of the desired
    // pet type
    while (it->type != c) {
      // If not found
      if (it == l.end())
        return false;
      it++;
    }
    p = *it;
    l.erase(l.begin());
    return true;
  }
  return false;
}
