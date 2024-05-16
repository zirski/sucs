#ifndef COVIDDB_H
#define COVIDDB_H

#include <string>
#include <vector>

using namespace std;

static const int TABLE_SIZE = 17;

class CovidDB {
public:
  ~CovidDB();
  class DataEntry {
  private:
    string date;
    string country;
    int c_cases;
    int c_deaths;

  public:
    DataEntry(string date, string country, int c_cases, int c_deaths)
        : date(date), country(country), c_cases(c_cases), c_deaths(c_deaths){};
    string getDate()
    {
      return date;
    }
    string getCountry()
    {
      return country;
    }
    int get_c_cases()
    {
      return c_cases;
    }
    int get_c_deaths()
    {
      return c_deaths;
    }

    void inc_c_cases(int cases)
    {
      c_cases += cases;
    }
    void inc_c_deaths(int deaths)
    {
      c_deaths += deaths;
    }
  };
  // inserts one entry into the hash table. Returns true if record is added,
  // false if rejected.
  bool add(DataEntry* entry);
  // Returns entry with specified name. Returns nullptr if no such entry exists.
  DataEntry* get(string country);
  // Removes entry with specified name.
  void remove(string country);
  // Displays contents of table.
  void displayTable();
  int hash(string name);

private:
  vector<DataEntry*> table[TABLE_SIZE];
};

#endif
