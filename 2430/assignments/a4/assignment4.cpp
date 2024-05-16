#include <format>
#include <iostream>
#include <random>
#include <sstream>
#include <string>

#include "covidDB.h"

using namespace std;

int main()
{
  CovidDB myDB;

  string countries[] = {
      "United States", "Japan", "Tunisia", "England", "Peru", "Senegal",
      "United States", "Japan", "Tunisia", "England", "Peru", "Senegal",
      "United States", "Japan", "Tunisia", "England", "Peru", "Senegal",
      "United States", "Japan", "Tunisia", "England", "Peru", "Senegal",
      "United States", "Japan", "Tunisia", "England", "Peru", "Senegal",
      "United States", "Japan", "Tunisia", "England", "Peru", "Senegal",
  };
  random_device r;
  mt19937 g(r());

  uniform_int_distribution<> dist_m(1, 12);
  uniform_int_distribution<> dist_d(1, 31);
  uniform_int_distribution<> dist_y(1960, 2005);
  uniform_int_distribution<> dist_cases(20, 3000);
  uniform_int_distribution<> dist_deaths(20, 3000);

  for (int i = 0; i < 36; i++) {
    ostringstream oss;
    oss << dist_m(g) << "/" << dist_d(g) << "/" << dist_y(g);
    myDB.add(new CovidDB::DataEntry(oss.str(), countries[i], dist_cases(g),
                                    dist_deaths(g)));
  }

  myDB.displayTable();
}
