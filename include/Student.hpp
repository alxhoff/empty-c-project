#ifndef STUDENT_HPP
#define STUDENT_HPP

#include <map>
#include <string>

#include "Person.hpp"

class Student : public Person {
 private:
  std::map<std::string, float> grades;

 public:
  Student(const std::string& name, int id);
  virtual ~Student();

  void addCourse(std::string&& course_name, float grade);
  float calculateGPA() const;
  virtual void display() const;
};

#endif  //STUDENT_HPP
