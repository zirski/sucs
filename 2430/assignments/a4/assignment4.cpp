#include <chrono>
#include <format>
#include <fstream>
#include <iostream>
#include <random>
#include <sstream>
#include <string>
#include <thread>

#include "covidDB.h"

using namespace std;

int main()
{
  CovidDB myDB;
  bool isBuilt = false;
  int input;

  while (true) {
    cout << "----------------------------------------" << endl;
    cout << "Covid Tracker" << endl;
    cout << "Please choose the operation you want:" << endl;
    cout << "1. Create the initial hash table" << endl;
    cout << "2. Add a new data entry" << endl;
    cout << "3. Get a data entry" << endl;
    cout << "4. Remove a data entry" << endl;
    cout << "5. Display hash table" << endl;
    cout << "0. Quit the system" << endl;
    cout << ":";
    cin >> input;
    switch (input) {
      case 1: {
        if (!isBuilt) {
          ifstream in("WHO-COVID-DATA.csv");
          string dummy;
          getline(in, dummy);

          string line, word;
          vector<string> words;
          while (getline(in, line)) {
            words.clear();
            stringstream ss(line);

            while (getline(ss, word, ',')) {
              words.push_back(word);
            }

            CovidDB::DataEntry* entry = new CovidDB::DataEntry(
                words[0], words[1], stoi(words[2]), stoi(words[3]));
            myDB.add(entry);
          }
          isBuilt = true;
          cout << "Hash table built." << endl;
        } else
          cout << "Hash table already built!" << endl;
        break;
      }
      case 2: {
        string date, name;
        int cases, deaths;
        cout << "----------------------------------------" << endl;
        cout << "Enter date of entry:";
        cin >> date;
        while (!(date[2] == '/' && date[5] == '/' && date.size() == 8)) {
          cout << "Error: format date as follows: mm/dd/yy" << endl;
          cin >> date;
        }
        cout << "Enter country name: ";
        cin >> name;
        cout << "Enter cases: ";
        cin >> cases;
        cout << "Enter deaths: ";
        cin >> deaths;
        CovidDB::DataEntry* entry =
            new CovidDB::DataEntry(date, name, cases, deaths);
        myDB.add(entry);
        cout << "Entry [" << date << " " << name << " " << cases << " "
             << deaths << "] added." << endl;
        break;
      }
      case 3: {
        string name;
        cout << "----------------------------------------" << endl;
        cout << "Please enter the country name of the entry you'd like: ";
        cin >> name;
        CovidDB::DataEntry* result = myDB.get(name);

        if (result == nullptr)
          cout << "Error: entry not found." << endl;
        else {
          cout << "--------------Requested Entry--------------" << endl;
          cout << "Country: " << result->getCountry() << endl;
          cout << "Date of latest entry: " << result->getDate() << endl;
          cout << "Cases: " << result->get_c_cases() << endl;
          cout << "Deaths: " << result->get_c_deaths() << endl;
        }
        break;
      }
      case 4: {
        string name;
        cout << "----------------------------------------" << endl;
        cout << "Please enter the country name of the entry you'd like to "
                "remove: ";
        cin >> name;
        if (myDB.get(name) == nullptr)
          cout << "Error: entry not found." << endl;
        else {
          myDB.remove(name);
          cout << "Entry [" << name << "] removed." << endl;
        }
        break;
      }
      case 5:
        cout << "----------------------------------------" << endl;
        myDB.displayTable();
        break;
      case 0:
        return 0;
    }
    cout << "Press <enter> to display the main menu:";
    cin.get();
    cin.get();
  }
}
