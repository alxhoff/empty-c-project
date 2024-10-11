
#include "Undergraduate.hpp"

#include <iostream>

Undergraduate::Undergraduate(const std::string& name, int id)
    : Student(name, id) {};
Undergraduate::~Undergraduate(){}

void Undergraduate::display() const{
  Student::display();
  std::cout << "Is an undergraduate" << std::endl;
}
