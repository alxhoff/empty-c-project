#ifndef COURSE_HPP
#define COURSE_HPP

#include <string>

class Course {
 public:
  std::string name;
  int code;
  float credits;

  Course(std::string name, int code, float credits);

  void display();
};

#endif  //COURSE_HPP
