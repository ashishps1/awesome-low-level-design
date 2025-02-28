#include "Book.hpp"
#include <iostream>

Book::Book(std::string bookId, std::string title, std::string author,
           std::string publisher, std::string isbn, int publicationYear)
    : bookId(bookId), title(title), author(author), publisher(publisher),
      isbn(isbn), status(BookStatus::AVAILABLE), publicationYear(publicationYear) {}

std::string Book::getBookId() const { return bookId; }
std::string Book::getTitle() const { return title; }
std::string Book::getAuthor() const { return author; }
std::string Book::getPublisher() const { return publisher; }
std::string Book::getIsbn() const { return isbn; }
BookStatus Book::getStatus() const { return status; }
int Book::getPublicationYear() const { return publicationYear; }

void Book::setStatus(BookStatus status) {
    this->status = status;
}

void Book::displayInfo() const {
    std::cout << "Book: " << title << " (ID: " << bookId << ")" << std::endl;
    std::cout << "Author: " << author << std::endl;
    std::cout << "Publisher: " << publisher << std::endl;
    std::cout << "ISBN: " << isbn << std::endl;
    std::cout << "Publication Year: " << publicationYear << std::endl;
    std::cout << "Status: ";
    switch (status) {
        case BookStatus::AVAILABLE: std::cout << "Available"; break;
        case BookStatus::BORROWED: std::cout << "Borrowed"; break;
        case BookStatus::RESERVED: std::cout << "Reserved"; break;
        case BookStatus::LOST: std::cout << "Lost"; break;
    }
    std::cout << std::endl;
} 