#ifndef HOMEWORK_PRIME7_PERSON_H_
#define HOMEWORK_PRIME7_PERSON_H_

#include <iostream>
#include <string>
using std::string;
using std::cout;
using std::cin;
using std::endl;

class Person {
public:
  Person() = default;
  Person(const string& address, const string& name)
    : address_(address)
    , name_(name)
  {}
  // TODO
  //Person(std::istream &is) { is >> *this; }
public:
  string get_address() const {
    return this->address_;
  }
  string get_name() const {
    return this->name_;
  }
private:
  string address_;
  string name_;
};
#endif