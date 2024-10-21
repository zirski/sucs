#include <iostream>
#include <sstream>

using namespace std;

int main()
{
  int in1, in2, low, high;
  int out = 0;

  cout << "Enter first input: ";
  cin >> in1;
  cout << "Enter second input:";
  cin >> in2;

  if (in1 < in2) {
    low = in1;
    high = in2;
  } else {
    low = in2;
    high = in1;
  }

  for (int i = low; i <= high; i++)
    out += i;
  cout << "Output: " << out << endl;
}
