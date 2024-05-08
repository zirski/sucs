/*
** Min-Heap construction and basic operations
** Lab 4, CPSC 2430
*/
#include <chrono>
#include <cstddef>
#include <ctime>
#include <iomanip>
#include <iostream>
#include <random>
#include <string>
#include <vector>

const int SECONDS_IN_DAY = 86400;

using namespace std;
using namespace std::chrono;

struct Pet {
  string name;
  chrono::time_point<system_clock> arrival;
  Pet(string name, chrono::time_point<system_clock> arrival)
      : name(name), arrival(arrival){};
};

class PetHeap {
private:
  vector<Pet*> petHeap;
  void percolateUp(int index);
  void percolateDown(int index);
  void deleteMin();
  Pet* peekMin();
  void swapNodes(int a, int b);

public:
  PetHeap()
  {
    petHeap = vector<Pet*>();
  }

  ~PetHeap()
  {
    for (size_t i = 0; i < petHeap.size(); i++)
      delete petHeap[i];
  }
  void insert(Pet* pet);
  Pet* adoptOldestPet();
  int numPets();
  void displayPets();
  void runTests();
};

void PetHeap::percolateUp(int index)
{
  if (index != 0) {
    int parent = (index - 1) / 2;
    if (petHeap[index]->arrival < petHeap[parent]->arrival) {
      swapNodes(index, parent);
      percolateUp(parent);
    }
  }
}

void PetHeap::percolateDown(int index)
{
  size_t r = index * 2 + 1;
  size_t l = index * 2 + 2;
  if (r < petHeap.size()) {
    int lesserChild = (petHeap[r]->arrival < petHeap[l]->arrival) ? r : l;
    if (petHeap[lesserChild]->arrival < petHeap[index]->arrival) {
      swapNodes(lesserChild, index);
      percolateDown(lesserChild);
    }
  } else if (l < petHeap.size() &&
             petHeap[r]->arrival < petHeap[index]->arrival) {
    swapNodes(r, index);
    percolateDown(r);
  }
}

void PetHeap::deleteMin()
{
  if (petHeap.size() > 0) {
    swapNodes(0, petHeap.size() - 1);
    petHeap.pop_back();
    percolateDown(0);
  }
}

Pet* PetHeap::peekMin()
{
  if (petHeap.size() > 0)
    return petHeap.front();
  else
    return nullptr;
}

void PetHeap::swapNodes(int a, int b)
{
  Pet* tmp = petHeap[a];
  petHeap[a] = petHeap[b];
  petHeap[b] = tmp;
}

void PetHeap::insert(Pet* pet)
{
  petHeap.push_back(pet);
  percolateUp(petHeap.size() - 1);
}

Pet* PetHeap::adoptOldestPet()
{
  Pet* a = peekMin();
  deleteMin();
  return a;
}

int PetHeap::numPets()
{
  return petHeap.size();
}

void PetHeap::displayPets()
{
  for (size_t i = 0; i < petHeap.size(); i++) {
    auto currentTime = system_clock::to_time_t(petHeap[i]->arrival);
    cout << left << setw(7) << petHeap[i]->name << " " << ctime(&currentTime)
         << endl;
  }
}

void PetHeap::runTests()
{
  int numTestPets = 10;
  string names[] = {"Smudge", "Angus", "Rio",  "Zuzu",   "Wheels",
                    "Beeb",   "Katy",  "Indy", "Violet", "Coco"};

  // Populates petHeap with 10 pets, each with randomized arrival times spanning
  // from runtime to runtime - 1 day.
  random_device r;
  mt19937 g(r());
  time_point<system_clock> t_now = system_clock::now();
  long end_range = duration_cast<seconds>(t_now.time_since_epoch()).count();
  long start_range = end_range - SECONDS_IN_DAY;
  uniform_int_distribution<> distribute(start_range, end_range);

  for (int i = 0; i < 10; i++) {
    cout << distribute(g) << endl;
  }

  for (int i = 0; i < numTestPets; i++) {
    cout << "Inserting pet " << names[i] << endl;
    insert(new Pet(names[i],
                   time_point<system_clock>(duration<long>(distribute(g)))));
  }
  cout << endl;

  displayPets();
  cout << "Adopted pet " << adoptOldestPet()->name << endl << endl;
  displayPets();
  cout << "Adopted pet " << adoptOldestPet()->name << endl << endl;
  displayPets();
  cout << "Adopted pet " << adoptOldestPet()->name << endl << endl;
  displayPets();

  int numLeft = numPets();
  cout << "There are " << numLeft << " pets left" << endl;
  for (int i = 0; i < numLeft; i++)
    cout << "Adopted pet " << adoptOldestPet()->name << endl;

  cout << endl << "Attempting to adopt one more pet..." << endl;
  Pet* p = adoptOldestPet();
  if (p == nullptr)
    cout << "Error: no more pets!" << endl;
  else
    cout << "Adopted pet " << p->name << endl;
}

int main()
{
  PetHeap heap;
  int input;

  do {
    cout << "Welcome to Lab 4 on Basic Heap Operations. What would you like to "
            "test?"
         << endl;
    cout << "1. Insert Pet" << endl;
    cout << "2. Adopt Pet" << endl;
    cout << "3. Number of Pets" << endl;
    cout << "4. Display Pets" << endl;
    cout << "5. Run Tests" << endl;
    cout << "6. Exit" << endl;
    cout << ":";

    cin >> input;

    switch (input) {
      case 1: {
        string name;
        cout << "Please enter the name of the pet you wish to insert: ";
        cin >> name;
        heap.insert(new Pet(name, system_clock::now()));
        cout << "Inserted pet " << name << endl;
        break;
      }
      case 2: {
        Pet* adoptee = heap.adoptOldestPet();
        if (adoptee != nullptr)
          cout << "Congratulations, you have adopted " << adoptee->name << "."
               << endl;
        else
          cout << "Error: No available pets to adopt";
        break;
      }
      case 3:
        cout << "The shelter heap has " << heap.numPets() << "pets." << endl;
        break;
      case 4:
        heap.displayPets();
        break;
      case 5: {
        heap.runTests();
        break;
      }
    }
    cout << endl;
  } while (input != 6);
  return 0;
}
