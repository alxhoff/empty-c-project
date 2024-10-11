#ifndef MANAGEMENTSYSTEM_HPP
#define MANAGEMENTSYSTEM_HPP

#include "Course.hpp"
#include "Student.hpp"

#include <memory>
#include <string>
#include <vector>
#include <exception>

class StudentNotFound : public std::exception {
    public:
        explicit StudentNotFound(const std::string& message) : message_(message){};

        const char* what() const noexcept override {
            return message_.c_str();
        }

    private:
        std::string message_;
};

class ManagementSystem {
 private:
  std::vector<std::shared_ptr<Course>> courses;
  std::vector<std::shared_ptr<Student>> students;
  int cur_student_no;

  int get_student_no();

 public:
  ManagementSystem();
  ~ManagementSystem();

  void addGraduateStudent(std::string name);
  void addUndergraduateStudent(std::string name);
  void removeStudent(int id);

  void addCourse(std::string name, int code, float credits);
  void removeCourse(int code);

  void listStudents();
  void listCourses();

  std::shared_ptr<Student> findStudent(int id);
  std::shared_ptr<Student> findStudent(std::string name);
};

#endif  //MANAGEMENTSYSTEM_HPP
