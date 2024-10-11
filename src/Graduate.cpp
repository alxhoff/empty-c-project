
#include "Graduate.hpp"

#include <iostream>

Graduate::Graduate(const std::string& name, int id) : Student(name, id) {}
Graduate::~Graduate(){}

void Graduate::display() const {
  Student::display();
  std::cout << "Is a graduate" << std::endl;
}
