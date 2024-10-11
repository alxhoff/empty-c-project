#ifndef GRADUATE_HPP
#define GRADUATE_HPP

#include "Student.hpp"

class Graduate : public Student {

public:
    Graduate(const std::string& name, int id);
    virtual ~Graduate();
    void display() const override;

};

#endif // GRADUATE_HPP
