#pragma once
#include "User.h"

class Librarian : public User {
public:
    Librarian(std::string n);
    void displayRole() const override;
};
