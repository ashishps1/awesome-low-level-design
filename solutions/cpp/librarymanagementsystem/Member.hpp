#ifndef MEMBER_HPP
#define MEMBER_HPP

#include <string>
#include <vector>
#include "Book.hpp"

class Member {
private:
    std::string memberId;
    std::string name;
    std::string email;
    std::string phone;
    std::vector<Book*> borrowedBooks;
    bool active;

public:
    Member(std::string memberId, std::string name, std::string email, std::string phone);
    
    std::string getMemberId() const;
    std::string getName() const;
    std::string getEmail() const;
    std::string getPhone() const;
    bool isActive() const;
    const std::vector<Book*>& getBorrowedBooks() const;
    
    void addBorrowedBook(Book* book);
    void removeBorrowedBook(Book* book);
    void setActive(bool status);
    void displayInfo() const;
};

#endif 