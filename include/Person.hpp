#ifndef PERSON_HPP
#define PERSON_HPP

#include <string>

class Person {
 protected:
  std::string name;
  int id;

  Person(const std::string& name, int id);
  virtual ~Person();

 public:
  virtual void display() const;
  int getId();
  std::string getName();
};

#endif  //PERSON_HPP
