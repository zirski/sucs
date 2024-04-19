#include <cmath>
#include <iostream>
#include <string>

using namespace std;

int mysterySequence(int n);
int tennisBalls(int n);
string decToBase2(int n);
bool isDivisibleBy7(int n);
double ramanujan(int depth, int num, int num2);
void runTests();

const int NUM_TESTS = 10;
const int RAM_NUM1 = 6;
const int RAM_NUM2 = 2;

int main()
{
  int input;

  do {
    cout << "Welcome to the recursion assignment. What would you like to test?"
         << endl;
    cout << "1. mysterySequence" << endl;
    cout << "2. tennisBalls" << endl;
    cout << "3. decToBase2" << endl;
    cout << "4. isDivisibleBy7" << endl;
    cout << "5. ramanujan" << endl;
    cout << "6. run tests" << endl;
    cout << "7. Exit" << endl;

    cin >> input;

    switch (input) {
      case 1: {
        int input;
        cout << "Mystery Sequence. Please enter n to compute the nth number in"
                " sequence: ";
        cin >> input;
        cout << "The 4th number in mystery sequence is "
             << mysterySequence(input) << "." << endl
             << endl;
        break;
      }
      case 2: {
        int input;
        cout << "Tennis Balls. Please enter the height of the pyramid: ";
        cin >> input;
        cout << "A pyramid with " << input << " levels holds "
             << tennisBalls(input) << " tennis balls." << endl
             << endl;
        break;
      }
      case 3: {
        int input;
        cout << "Decimal to Binary Converter. Please enter the integer you "
                "wish to convert: ";
        cin >> input;
        cout << decToBase2(input) << " is " << input << " in binary." << endl
             << endl;
        break;
      }
      case 4: {
        int input;
        cout << "Divisible by 7. Please enter the integer you wish to test: ";
        cin >> input;
        if (isDivisibleBy7(input))
          cout << input << " is divisible by 7." << endl << endl;
        else
          cout << input << " is not divisible by 7." << endl << endl;
        break;
      }
      case 5: {
        int input;
        cout << "Ramanujan. Enter integer depth: ";
        cin >> input;
        cout << "Result at depth " << input << ": "
             << ramanujan(input, RAM_NUM1, RAM_NUM2) << endl;
        cout << "Result at infinite depth: "
             << ramanujan(1000, RAM_NUM1, RAM_NUM2) << endl;
        break;
      }
      case 6: {
        cout << "-*- Mystery Sequence -*-" << endl;
        cout << "mysterySequence(1): " << mysterySequence(1) << endl;
        cout << "mysterySequence(2): " << mysterySequence(2) << endl;
        cout << "mysterySequence(3): " << mysterySequence(3) << endl;
        cout << "mysterySequence(4): " << mysterySequence(4) << endl;
        cout << "mysterySequence(5): " << mysterySequence(5) << endl;

        cout << endl << "-*- Tennis Balls -*-" << endl;
        cout << "tennisBalls(1): " << tennisBalls(1) << endl;
        cout << "tennisBalls(2): " << tennisBalls(2) << endl;
        cout << "tennisBalls(3): " << tennisBalls(3) << endl;
        cout << "tennisBalls(4): " << tennisBalls(4) << endl;
        cout << "tennisBalls(5): " << tennisBalls(5) << endl;

        cout << endl << "-*- Decimal to Base 2 Converter -*-" << endl;
        cout << "decToBase2(1):" << decToBase2(1) << endl;
        cout << "decToBase2(27):" << decToBase2(27) << endl;
        cout << "decToBase2(38):" << decToBase2(38) << endl;
        cout << "decToBase2(200202):" << decToBase2(200202) << endl;
        cout << "decToBase2(6969696):" << decToBase2(6969696) << endl;

        cout << endl << "-*- Is Divisible By 7 -*-" << endl;
        cout << "isDivisibleBy7(1):" << isDivisibleBy7(1) << endl;
        cout << "isDivisibleBy7(29):" << isDivisibleBy7(29) << endl;
        cout << "isDivisibleBy7(161):" << isDivisibleBy7(161) << endl;
        cout << "isDivisibleBy7(273):" << isDivisibleBy7(273) << endl;
        cout << "isDivisibleBy7(12345):" << isDivisibleBy7(12345) << endl;

        cout << endl << "-*- Ramanujan -*-" << endl;
        cout << "ramanujan(1)" << ramanujan(1, RAM_NUM1, RAM_NUM2) << endl;
        cout << "ramanujan(10)" << ramanujan(10, RAM_NUM1, RAM_NUM2) << endl;
        cout << "ramanujan(100)" << ramanujan(100, RAM_NUM1, RAM_NUM2) << endl;
        cout << "ramanujan(1000)" << ramanujan(1000, RAM_NUM1, RAM_NUM2)
             << endl;
        cout << "ramanujan(10000)" << ramanujan(10000, RAM_NUM1, RAM_NUM2)
             << endl;
      }
    }
  } while (input != 7);
  return 0;
}

int mysterySequence(int n)
{
  if (n == 1)
    return 3;
  else if (n == 0)
    return 2;
  else
    return mysterySequence(n - 1) * mysterySequence(n - 2);
}

int tennisBalls(int n)
{
  if (n == 1)
    return 1;
  else
    return (n * n) + (tennisBalls(n - 1));
}

string decToBase2(int n)
{
  if (n == 1)
    return "1";
  else if (n == 0)
    return 0;
  else
    return to_string(n % 2) + decToBase2(n / 2);
}

bool isDivisibleBy7(int n)
{
  if (n == 0)
    return true;
  else if (n < 100)
    return n % 7 == 0;
  else {
    string s = to_string(n);
    s.pop_back();
    return isDivisibleBy7(stoi(s) - (int)(to_string(n).back() - '0') * 2);
  }
}

double ramanujan(int depth, int n, int n2)
{
  if (depth == 0)
    return sqrt(n);
  else
    return sqrt(n + n2 * ramanujan(depth - 1, n + 1, n2 + 1));
}
