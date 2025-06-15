#pragma once
#include <iostream>
#include <string>

class Book {
private:
    std::string title;
    std::string author;
    int year;
public:
    Book(std::string t = "", std::string a = "", int y = 0);
    friend std::ostream& operator<<(std::ostream& os, const Book& b);
    friend std::istream& operator>>(std::istream& is, Book& b);
    bool operator==(const Book& other) const;
    bool operator<(const Book& other) const;
    std::string getTitle() const;
    std::string getAuthor() const;
    int getYear() const;
};
