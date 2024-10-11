#include "Person.hpp"

#include <iostream>
#include <string>

Person::Person(const std::string& name, int id) : name(name), id(id) {}

Person::~Person() {
  std::cout << "Person destroyed" << std::endl;
}

void Person::display() const {
  std::cout << "Name: " << name << " ID: " << id << std::endl;
}

int Person::getId(){
    return id;
}
  
std::string Person::getName(){
    return name;
};

