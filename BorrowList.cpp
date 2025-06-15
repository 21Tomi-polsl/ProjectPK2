#include "BorrowList.h"
#include <fstream>
#include <sstream>
#include <algorithm>
#include <iostream>

void BorrowList::addUser() {
    userBookList.push_back(std::forward_list<Book>());
}

void BorrowList::borrowBook(int userIndex, const Book& b) {
    if (!isBookAvailable(b)) {
        std::cout << "Error: Book not in catalog.\n";
        return;
    }
    if (borrowedBooks.count(b) != 0) {
        std::cout << "Error: Already borrowed by user ID " << borrowedBooks.at(b) << ".\n";
        return;
    }
    auto it = userBookList.begin();
    std::advance(it, userIndex);
    it->push_front(b);
    history.push(b);
    borrowedBooks[b] = userIndex;
    std::cout << "Book borrowed.\n";
}

void BorrowList::returnBook(int userIndex, const Book& b) {
    auto it = userBookList.begin();
    std::advance(it, userIndex);
    std::forward_list<Book>& userBooks = *it;

    auto before = userBooks.before_begin();
    auto current = userBooks.begin();
    bool found = false;

    while (current != userBooks.end()) {
        if (*current == b) {
            userBooks.erase_after(before);
            found = true;
            break;
        }
        ++before;
        ++current;
    }

    if (!found) {
        std::cout << "Error: User " << userIndex << " does not have this book.\n";
        return;
    }

    if (borrowedBooks.count(b)) borrowedBooks.erase(b);
    std::cout << "Book returned.\n";

    std::queue<std::pair<int, Book>> tmp;
    bool notified = false;
    while (!reservations.empty()) {
        auto entry = reservations.front();
        reservations.pop();
        if (!notified && entry.second == b) {
            std::cout << "User " << entry.first
                << ": Your reserved book \"" << b.getTitle()
                << "\" is now available.\n";
            notified = true;
        }
        else {
            tmp.push(entry);
        }
    }
    reservations = std::move(tmp);
}

void BorrowList::reserveBook(int userIndex, const Book& b) {
    if (!isBookAvailable(b)) {
        std::cout << "Error: Book not in catalog.\n";
        return;
    }
    if (borrowedBooks.count(b) == 0) {
        std::cout << "Book is available – borrow instead of reserve.\n";
        return;
    }
    reservations.push({ userIndex, b });
    std::cout << "Book reserved.\n";
}

void BorrowList::saveToFile(const std::string& filename) {
    std::ofstream ofs(filename);
    ofs << "USERS\n";
    int uid = 0;
    for (const auto& user : userBookList) {
        ofs << "USER " << uid++ << "\n";
        for (const auto& b : user) {
            ofs << b << "\n";
        }
    }
    ofs << "RESERVATIONS\n";
    std::queue<std::pair<int, Book>> tmp = reservations;
    while (!tmp.empty()) {
        auto e = tmp.front(); tmp.pop();
        ofs << e.first << "," << e.second.getTitle() << ","
            << e.second.getAuthor() << "," << e.second.getYear() << "\n";
    }
}

void BorrowList::loadFromFile(const std::string& filename) {
    userBookList.clear();
    borrowedBooks.clear();
    while (!reservations.empty()) reservations.pop();

    std::ifstream ifs(filename);
    std::string line;
    enum Mode { NONE, USERS, RES };
    Mode mode = NONE;
    while (std::getline(ifs, line)) {
        if (line == "USERS") { mode = USERS; continue; }
        if (line == "RESERVATIONS") { mode = RES; continue; }

        if (mode == USERS) {
            if (line.rfind("USER ", 0) == 0) {
                userBookList.push_back({});
            }
            else if (!line.empty()) {
                std::istringstream iss(line);
                Book b; iss >> b;
                userBookList.back().push_front(b);
                borrowedBooks[b] = static_cast<int>(userBookList.size()) - 1;
            }
        }
        else if (mode == RES && !line.empty()) {
            std::istringstream iss(line);
            int uid; char comma;
            std::string title, author; int year;
            iss >> uid >> comma;
            std::getline(iss, title, ',');
            std::getline(iss, author, ',');
            iss >> year;
            reservations.push({ uid, Book(title, author, year) });
        }
    }
}

int BorrowList::userCount() const {
    return static_cast<int>(userBookList.size());
}

void BorrowList::loadAvailableBooks(const std::string& filename) {
    std::ifstream file(filename);
    Book b;
    while (file >> b) {
        availableBooks.insert(b);
    }
}

bool BorrowList::isBookAvailable(const Book& b) const {
    return availableBooks.find(b) != availableBooks.end();
}

void BorrowList::showCatalog() const {
    std::cout << "\n=== Catalog ===\n";
    for (std::set<Book>::const_iterator it = availableBooks.begin();
        it != availableBooks.end(); ++it) {
        std::cout << *it << "\n";
    }
}

void BorrowList::addAvailableBook(const Book& b, const std::string& filename) {
    if (availableBooks.insert(b).second) {
        std::ofstream ofs(filename, std::ios::app);
        ofs << b << "\n";
        std::cout << "Book added to catalog.\n";
    }
    else {
        std::cout << "Book already in catalog.\n";
    }
}
