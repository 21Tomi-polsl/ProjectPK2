#include "Librarian.h"
#include <iostream>

Librarian::Librarian(std::string n) : User(n) {}
void Librarian::displayRole() const {
    std::cout << name << " (Librarian)\n";
}
