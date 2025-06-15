#include "Student.h"
#include <iostream>

Student::Student(std::string n) : User(n) {}
void Student::displayRole() const {
    std::cout << name << " (Student)\n";
}
