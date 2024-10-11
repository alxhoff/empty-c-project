#ifndef UNDERGRADUATE_HPP
#define UNDERGRADUATE_HPP

#include "Student.hpp"

class Undergraduate : public Student {
    public:
        Undergraduate(const std::string& name, int id);
        virtual ~Undergraduate();
        void display() const override;
};

#endif //UNDERGRADUATE_HPP
