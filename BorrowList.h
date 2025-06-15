#pragma once
#include <stack>
#include <queue>
#include <list>
#include <set>
#include <map>
#include <forward_list>
#include "Book.h"

class BorrowList {
private:
    std::list<std::forward_list<Book>> userBookList;
    std::stack<Book> history;
    std::queue<std::pair<int, Book>> reservations;
    std::set<Book> availableBooks;
    std::map<Book, int> borrowedBooks;

public:
    void addUser();
    void borrowBook(int userIndex, const Book& b);
    void returnBook(int userIndex, const Book& b);
    void reserveBook(int userIndex, const Book& b);

    void saveToFile(const std::string& filename);
    void loadFromFile(const std::string& filename);

    int userCount() const;

    void loadAvailableBooks(const std::string& filename);
    bool isBookAvailable(const Book& b) const;
    void showCatalog() const;
    void addAvailableBook(const Book& b, const std::string& filename);
};
