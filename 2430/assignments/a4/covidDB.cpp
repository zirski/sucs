#include "covidDB.h"

#include <cstddef>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

int CovidDB::hash(string name)
{
  int sum = 0;

  for (int i = 0; i < name.size(); i++)
    sum += (i + 1) * name[i];
  return sum % TABLE_SIZE;
}

CovidDB::~CovidDB()
{
  for (int i = 0; i < TABLE_SIZE; i++)
    for (DataEntry* d : table[i])
      delete d;
}

bool CovidDB::add(DataEntry* entry)
{
  int h_index = hash(entry->getCountry());
  vector<DataEntry*> chain = table[h_index];
  for (int i = 0; i < chain.size(); i++) {
    if (chain[i]->getCountry() == entry->getCountry()) {
      // Date format: mm/dd/yyyy
      // 0 1 2 3 4 5 6 7 8 9 l
      // m m / d d / y y y y
      string c_date = chain[i]->getDate();
      int c_y = stoi(c_date.substr(c_date.length() - 4));
      int e_y = stoi(entry->getDate().substr(entry->getDate().length() - 4));

      if (e_y < c_y)
        return false;
      else if (e_y > c_y) {
        chain[i]->inc_c_cases(entry->get_c_cases());
        chain[i]->inc_c_deaths(entry->get_c_deaths());
        cout << "1" << endl;
        return true;
      } else {
        int c_m = stoi(c_date.substr(c_date.length() - 7, 2));
        int e_m =
            stoi(entry->getDate().substr(entry->getDate().length() - 7, 2));
        if (e_m < c_m)
          return false;
        else if (e_m > c_m) {
          chain[i]->inc_c_cases(entry->get_c_cases());
          chain[i]->inc_c_deaths(entry->get_c_deaths());
          cout << "2" << endl;
          return true;
        } else {
          int c_d = stoi(c_date.substr(0, 2));
          int e_d = stoi(entry->getDate().substr(0, 2));

          if (e_d < c_d)
            return false;
          else if (e_d >= c_d) {
            chain[i]->inc_c_cases(entry->get_c_cases());
            chain[i]->inc_c_deaths(entry->get_c_deaths());
            cout << "3" << endl;
            return true;
          }
        }
      }
    }
  }
  chain.push_back(entry);
  cout << "4" << endl;
  return true;
}

CovidDB::DataEntry* CovidDB::get(string country)
{
  int key = hash(country);
  auto it = table[key].begin();
  while (it != table[key].end()) {
    if ((*it)->getCountry() == country)
      return *it;
    it++;
  }
  return nullptr;
}

void CovidDB::remove(string country)
{
  int key = hash(country);
  for (auto it = table[key].begin(); it != table[key].end(); it++) {
    if ((*it)->getCountry() == country) {
      table[key].erase(it);
      return;
    }
  }
}

void CovidDB::displayTable()
{
  for (int i = 0; i < TABLE_SIZE; i++)
    cout << table[i].size() << " " << endl;
  // for (int j = 0; j < table[i].size(); j++)
  //   cout << hash(table[i][j]->getCountry()) << ", " << table[i][j]->getDate()
  //        << ", " << table[i][j]->getCountry() << ", "
  //        << table[i][j]->get_c_cases() << ", " << table[i][j]->get_c_deaths()
  //        << endl;
}
