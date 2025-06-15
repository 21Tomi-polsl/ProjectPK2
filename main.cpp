#include <iostream>
#include "Book.h"
#include "BorrowList.h"
#include "Student.h"
#include "Librarian.h"

void showMenu() {
    std::cout << "\n=== MENU ===\n"
        << "1. Add new user\n"
        << "2. Borrow book\n"
        << "3. Return book\n"
        << "4. Reserve book\n"
        << "5. Save data to file\n"
        << "6. Load data from file\n"
        << "7. Exit\n"
        << "8. Show catalog\n"
        << "9. Add book to catalog\n"
        << "Select option: ";
}

Book getBookInput(const BorrowList& lib) {
    std::string title, author;
    std::cin.ignore();
    std::cout << "Title: ";   std::getline(std::cin, title);
    std::cout << "Author: ";  std::getline(std::cin, author);
    // dopasuj rok z katalogu
    for (int y = 1000; y <= 2100; ++y) {
        Book b(title, author, y);
        if (lib.isBookAvailable(b)) return b;
    }
    std::cout << "Error: Not in catalog.\n";
    return Book();
}

Book getNewBook() {
    std::string title, author; int year;
    std::cin.ignore();
    std::cout << "New title: ";   std::getline(std::cin, title);
    std::cout << "New author: ";  std::getline(std::cin, author);
    std::cout << "Year: ";        std::cin >> year;
    return Book(title, author, year);
}

int main() {
    BorrowList lib;
    const std::string catalogFile = "ksiazki.txt";
    const std::string dataFile = "biblioteka.txt";

    lib.loadAvailableBooks(catalogFile);
    int choice;
    while (true) {
        showMenu();
        std::cin >> choice;
        switch (choice) {
        case 1:
            lib.addUser();
            std::cout << "User ID " << lib.userCount() - 1 << " created.\n";
            break;
        case 2: {
            int id; std::cout << "User ID: "; std::cin >> id;
            Book b = getBookInput(lib);
            if (!b.getTitle().empty()) lib.borrowBook(id, b);
            break;
        }
        case 3: {
            int id; std::cout << "User ID: "; std::cin >> id;
            Book b = getBookInput(lib);
            if (!b.getTitle().empty()) lib.returnBook(id, b);
            break;
        }
        case 4: {
            int id; std::cout << "User ID: "; std::cin >> id;
            Book b = getBookInput(lib);
            if (!b.getTitle().empty()) lib.reserveBook(id, b);
            break;
        }
        case 5:
            lib.saveToFile(dataFile);
            std::cout << "Data saved.\n";
            break;
        case 6:
            lib.loadFromFile(dataFile);
            std::cout << "Data loaded.\n";
            break;
        case 7:
            std::cout << "Exiting...\n";
            return 0;
        case 8:
            lib.showCatalog();
            break;
        case 9: {
            Book nb = getNewBook();
            lib.addAvailableBook(nb, catalogFile);
            break;
        }
        default:
            std::cout << "Invalid option.\n";
        }
    }
}
