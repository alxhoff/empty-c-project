#ifndef COURSELIST_HPP
#define COURSELIST_HPP

#include <list>

#include "Course.hpp"

class CourseList {
    private:
        std::list<Course> courses;

    public:
        CourseList();
        void list_courses();
        void add_course(Course course);
        void add_course(std::string name, int code, float credits);
        void remove_course(std::string name);
};

#endif //COURSELIST_HPP
