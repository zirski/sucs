#include <iostream>

using namespace std;

const int CLASSES = 5;

int main()
{
  int input;
  int digits[CLASSES] = {};
  int limits[CLASSES] = {9, 99, 999, 9999, 32767};

  cout << ":";
  cin >> input;

  while (input >= 0) {
    int i = 0;
    while (input > limits[i])
      i++;
    digits[i]++;
    cout << ":";
    cin >> input;
  }
  for (int i = 0; i < CLASSES; i++)
    cout << digits[i] << " ";
  cout << endl;
}
