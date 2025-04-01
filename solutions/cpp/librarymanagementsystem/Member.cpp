#include "Member.hpp"
#include <iostream>
#include <algorithm>

Member::Member(std::string memberId, std::string name, std::string email, std::string phone)
    : memberId(memberId), name(name), email(email), phone(phone), active(true) {}

std::string Member::getMemberId() const { return memberId; }
std::string Member::getName() const { return name; }
std::string Member::getEmail() const { return email; }
std::string Member::getPhone() const { return phone; }
bool Member::isActive() const { return active; }
const std::vector<Book*>& Member::getBorrowedBooks() const { return borrowedBooks; }

void Member::addBorrowedBook(Book* book) {
    borrowedBooks.push_back(book);
}

void Member::removeBorrowedBook(Book* book) {
    auto it = std::find(borrowedBooks.begin(), borrowedBooks.end(), book);
    if (it != borrowedBooks.end()) {
        borrowedBooks.erase(it);
    }
}

void Member::setActive(bool status) {
    active = status;
}

void Member::displayInfo() const {
    std::cout << "Member: " << name << " (ID: " << memberId << ")" << std::endl;
    std::cout << "Email: " << email << std::endl;
    std::cout << "Phone: " << phone << std::endl;
    std::cout << "Status: " << (active ? "Active" : "Inactive") << std::endl;
    std::cout << "Borrowed Books: " << borrowedBooks.size() << std::endl;
} 