#include "covidDB.h"

#include <cstddef>
#include <iomanip>
#include <iostream>
#include <sstream>
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
    for (int j = 0; j < table[i].size(); j++)
      delete table[i][j];
}

bool CovidDB::add(DataEntry*& entry)
{
  int h_index = hash(entry->getCountry());
  for (int i = 0; i < table[h_index].size(); i++) {
    DataEntry* ref = table[h_index][i];
    if (ref->getCountry() == entry->getCountry()) {
      string c_date = ref->getDate();
      string e_date = entry->getDate();
      if (valiDATE(c_date, e_date)) {
        ref->inc_c_cases(entry->get_c_cases());
        ref->inc_c_deaths(entry->get_c_deaths());
        ref->setDate(entry->getDate());
        return true;
      } else
        return false;
    }
  }
  table[h_index].push_back(entry);
  return true;
}

CovidDB::DataEntry* CovidDB::get(string country)
{
  int key = hash(country);
  for (int i = 0; i < table[key].size(); i++)
    if (table[key][i]->getCountry() == country)
      return table[key][i];
  return nullptr;
}

void CovidDB::remove(string country)
{
  int key = hash(country);
  for (int i = 0; i < table[key].size(); i++)
    if (table[key][i]->getCountry() == country) {
      table[key].erase(table[key].begin() + i);
      return;
    }
}

void CovidDB::displayTable()
{
  cout << left << setw(47) << "|Country" << setw(23) << "|Date of Latest Entry"
       << setw(10) << "|Cases" << setw(10) << "|Deaths" << endl;
  for (int i = 0; i < TABLE_SIZE; i++)
    for (int j = 0; j < table[i].size(); j++)
      cout << left << setw(47) << table[i][j]->getCountry() << setw(23)
           << table[i][j]->getDate() << setw(10) << table[i][j]->get_c_cases()
           << setw(10) << table[i][j]->get_c_deaths() << endl;
}

bool CovidDB::valiDATE(string ref, string test)
{
  // Date format: mm/dd/yy
  // 0 1 2 3 4 5 6 7 l
  // m m / d d / y y
  ref = sanitize_date(ref);
  test = sanitize_date(test);

  int ry, ty, rm, tm, rd, td;
  ry = stoi(ref.substr(6));
  ty = stoi(test.substr(6));
  rd = stoi(ref.substr(3, 2));
  td = stoi(test.substr(3, 2));
  rm = stoi(ref.substr(0, 2));
  tm = stoi(test.substr(0, 2));

  if (ty < ry)
    return false;
  else if (ty > ry)
    return true;
  // if years are equal
  else {
    if (tm < rm)
      return false;
    else if (tm > rm)
      return true;
    // if months are equal
    else {
      if (td < rd)
        return false;
      else
        return true;
    }
  }
}

string CovidDB::sanitize_date(string date)
{
  stringstream ss(date);
  vector<string> tkns;
  string tkn;
  while (getline(ss, tkn, '/'))
    tkns.push_back(tkn);
  if (tkns[0].size() == 1)
    tkns[0] = "0" + tkns[0];
  if (tkns[1].size() == 1)
    tkns[1] = "0" + tkns[1];
  return tkns[0] + "/" + tkns[1] + "/" + tkns[2];
}
