#include "User.h"

User::User(std::string n) : name(n) {}
std::string User::getName() const { return name; }
