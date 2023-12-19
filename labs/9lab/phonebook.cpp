// A simple "caller ID" program

#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <string>

using namespace std;

// add a number, name pair to the phonebook
void add(map<int, string> &phonebook, int number, string const& name) {
    phonebook.insert(make_pair(number, name));
}

// given a phone number, determine who is calling
void identify(const map<int, string> & phonebook, int number) {
  if (phonebook.find(number) == phonebook.end()) {
    cout << "unknown caller!" << endl;
  } else {
    cout << phonebook.find(number)->second << " is calling!" << endl;
  }
}

int main() {
  map<int, string> phonebook;

  // add several names to the phonebook
  add(phonebook, 1111, "fred");
  add(phonebook, 2222, "sally");
  add(phonebook, 3333, "george");

  add(phonebook, 1111111, "lily");
  add(phonebook, 1234567, "ellie");
  add(phonebook, 1111111, "ally");

  // test the phonebook
  identify(phonebook, 2222);
  identify(phonebook, 4444); //4444 does not exist

  //testing the 7 digit phone numbers
  identify(phonebook, 1111111);
  identify(phonebook, 1234567);
  identify(phonebook, 1111111);
  identify(phonebook, 11394854);
  
}