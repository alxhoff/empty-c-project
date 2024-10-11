#include "Student.hpp"

#include <iostream>

Student::Student(const std::string& name, int id) : Person(name, id) {}
Student::~Student(){}

void Student::addCourse(std::string&& course_name, float grade) {
  grades.insert(std::pair(course_name, grade));
}

float Student::calculateGPA() const{
  float GPA = 0.0;
  for (auto it = grades.begin();
       it != grades.end(); ++it) {
    GPA += it->second;
  }
  return grades.size() == 0 ? GPA : GPA / grades.size();
}

void Student::display() const{
  Person::display();
  std::cout << "GPA: " << Student::calculateGPA() << std::endl;
}
