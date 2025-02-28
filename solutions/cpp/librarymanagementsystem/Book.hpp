#ifndef BOOK_HPP
#define BOOK_HPP

#include <string>

enum class BookStatus {
    AVAILABLE,
    BORROWED,
    RESERVED,
    LOST
};

class Book {
private:
    std::string bookId;
    std::string title;
    std::string author;
    std::string publisher;
    std::string isbn;
    BookStatus status;
    int publicationYear;

public:
    Book(std::string bookId, std::string title, std::string author,
         std::string publisher, std::string isbn, int publicationYear);
    
    std::string getBookId() const;
    std::string getTitle() const;
    std::string getAuthor() const;
    std::string getPublisher() const;
    std::string getIsbn() const;
    BookStatus getStatus() const;
    int getPublicationYear() const;
    
    void setStatus(BookStatus status);
    void displayInfo() const;
};

#endif 