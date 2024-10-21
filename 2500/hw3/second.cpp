#include <iostream>
using namespace std;

int main()
{
  int in = 0;
  int pen = 0;
  int ult = 0;

  while (in >= 0) {
    cout << "Enter number: ";
    cin >> in;

    if (in > ult) {
      pen = ult;
      ult = in;
    } else if (in > pen || in == ult)
      pen = in;
  }
  if (in == pen)
    cout << 0 << endl;
  else
    cout << pen << endl;
}
