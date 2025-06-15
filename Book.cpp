#include "Book.h"
#include <tuple>

Book::Book(std::string t, std::string a, int y)
    : title(std::move(t)), author(std::move(a)), year(y) {
}

std::ostream& operator<<(std::ostream& os, const Book& b) {
    os << b.title << "," << b.author << "," << b.year;
    return os;
}

std::istream& operator>>(std::istream& is, Book& b) {
    std::getline(is, b.title, ',');
    std::getline(is, b.author, ',');
    is >> b.year;
    is.ignore();
    return is;
}

bool Book::operator==(const Book& other) const {
    return title == other.title
        && author == other.author
        && year == other.year;
}

bool Book::operator<(const Book& other) const {
    return std::tie(title, author, year)
        < std::tie(other.title, other.author, other.year);
}

std::string Book::getTitle() const {
    return title;
}

std::string Book::getAuthor() const {
    return author;
}

int Book::getYear() const {
    return year;
}
