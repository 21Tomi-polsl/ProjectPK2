#pragma once
#include <string>

class User {
protected:
    std::string name;
public:
    User(std::string n);
    virtual void displayRole() const = 0;
    std::string getName() const;
    virtual ~User() = default;
};
