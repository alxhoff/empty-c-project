#include "Course.hpp"

#include <format>
#include <iostream>

Course::Course(std::string name, int code, float credits)
    : name(name), code(code), credits(credits) {}

void Course::display() {
  std::cout << std::format("Course: {} ({}) gives {} credits", name, code,
                           credits)
            << std::endl;
}
