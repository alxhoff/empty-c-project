
#include "ManagementSystem.hpp"
#include "Graduate.hpp"
#include "Undergraduate.hpp"

#include <algorithm>
#include <format>
#include <iostream>
#include <typeinfo>

ManagementSystem::ManagementSystem() : cur_student_no(0) {}
ManagementSystem::~ManagementSystem() {}

int ManagementSystem::get_student_no() {
  return cur_student_no++;
}

void ManagementSystem::addGraduateStudent(std::string name) {
  students.push_back(
      std::make_shared<Graduate>(name, ManagementSystem::get_student_no()));
}

void ManagementSystem::addUndergraduateStudent(std::string name) {
  students.push_back(std::make_shared<Undergraduate>(
      name, ManagementSystem::get_student_no()));
}

void ManagementSystem::removeStudent(int id) {
  students.erase(std::remove_if(students.begin(), students.end(),
                                [id](const std::shared_ptr<Student>& student) {
                                  return student->getId() == id;
                                }),
                 students.end());
}

void ManagementSystem::addCourse(std::string name, int code, float credits) {
  courses.push_back(std::make_shared<Course>(name, code, credits));
}

void ManagementSystem::removeCourse(int code) {
  courses.erase(std::remove_if(courses.begin(), courses.end(),
                               [code](const std::shared_ptr<Course>& course) {
                                 return course->code == code;
                               }),
                courses.end());
}

void ManagementSystem::listStudents() {
  for (const auto& studentPtr : students) {
    studentPtr->display();
  }
}

void ManagementSystem::listCourses() {
  for (const auto& coursePtr : courses) {
    coursePtr->display();
  }
}

// T: vector to search, U: value to compare
// comp: member extraction lambda
template <typename T, typename U>
typename std::shared_ptr<Student> findInVector(std::vector<T>& vec,
                                               const U& value,
                                               auto get_member) {
  auto it = std::find_if(vec.begin(), vec.end(), [&value, &get_member](T& obj) {
    return get_member(obj) == value;
  });

  if (it != vec.end())
    return *it;
  else
    throw StudentNotFound(std::format("Student not found using: {}", value));
}

std::shared_ptr<Student> ManagementSystem::findStudent(int id) {
  return findInVector(students, id,
                      [](std::shared_ptr<Student>& s) { return s->getId(); });
}

std::shared_ptr<Student> ManagementSystem::findStudent(std::string name) {
  return findInVector(students, name,
                      [](std::shared_ptr<Student>& s) { return s->getName(); });
}

