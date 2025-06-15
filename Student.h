#pragma once
#include "User.h"

class Student : public User {
public:
    Student(std::string n);
    void displayRole() const override;
};
