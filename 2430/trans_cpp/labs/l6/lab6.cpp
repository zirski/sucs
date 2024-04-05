#include <iostream>
#include <random>

using namespace std;

int main()
{
  random_device r;
  mt19937 g(r());
  uniform_int_distribution<> distribute(1, 99);

  int num;
  int* ptr;

  cout << "Please enter an integer: ";
  cin >> num;

  ptr = &num;

  cout << "Value at num: " << num << endl;
  cout << "Address of num: " << &num << endl;
  cout << "Value at ptr: " << *ptr << endl;
  cout << "Address of ptr: " << ptr << endl;

  ptr = new int;
  *ptr = distribute(g);

  cout << "Value at num: " << num << endl;
  cout << "Address of num: " << &num << endl;
  cout << "Value at ptr: " << *ptr << endl;
  cout << "Address of ptr: " << ptr << endl;

  delete ptr;

  cout << "Please enter a number between 1 and 9. This will be the size of a new array: ";
  cin >> num;
  ptr = new int[num];

  for (int i = 0; i < num; i++)
    ptr[i] = distribute(g);
 
  for (int i = 0; i < num; i++)
    cout << ptr[i] << " ";
  cout << endl;

  delete[] ptr;
  return 0;
}
