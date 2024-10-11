#include "ManagementSystem.hpp"

extern "C" {
#include "main.h"
}

int main() {

  ManagementSystem ms;

  ms.addCourse("IT", 1001, 3.5);
  ms.addCourse("English", 1002, 4);
  ms.addCourse("German", 1003, 4.25);

  ms.addGraduateStudent("Alex");
  ms.addUndergraduateStudent("Franzi");
  ms.addGraduateStudent("David");
  ms.addGraduateStudent("Alex");
  ms.addUndergraduateStudent("Matze");

  ms.listStudents();

  ms.removeStudent(1);

  ms.listStudents();

  ms.listCourses();

  ms.removeCourse(1002);

  ms.listCourses();

  std::shared_ptr<Student> student_alex = ms.findStudent(0);

  student_alex->display();

  student_alex->addCourse("IT", 4.0);
  student_alex->addCourse("English", 6.0);

  student_alex->display();

  std::shared_ptr<Student> student_david = ms.findStudent("David");

  student_david->addCourse("IT", 3.0);

  student_david->display();

  std::shared_ptr<Student> student_unknown = ms.findStudent("Unknown Student");

  return 0;
}
