#include "CourseList.hpp"

#include <algorithm>

CourseList::CourseList() {}
void CourseList::list_courses() {
  for (Course course : courses) {
    course.display();
  }
}

void CourseList::add_course(Course course) {
  courses.push_back(course);
}

void CourseList::add_course(std::string name, int code, float credits) {
  courses.push_back(Course(name, code, credits));
}

void CourseList::remove_course(std::string name) {
  auto it = std::find_if(
      courses.begin(), courses.end(),
      [name](const Course& course) { return course.name == name; });
  it != courses.end() ? static_cast<void>(courses.erase(it)) : void();
}
