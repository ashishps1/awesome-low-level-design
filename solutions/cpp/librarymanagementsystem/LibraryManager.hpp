#ifndef LIBRARY_MANAGER_HPP
#define LIBRARY_MANAGER_HPP

#include <vector>
#include <string>
#include "Book.hpp"
#include "Member.hpp"
#include "Transaction.hpp"

class LibraryManager {
private:
    std::vector<Book*> books;
    std::vector<Member*> members;
    std::vector<Transaction*> transactions;
    int transactionIdCounter;

public:
    LibraryManager();
    ~LibraryManager();
    
    void addBook(Book* book);
    void addMember(Member* member);
    
    bool borrowBook(std::string memberId, std::string bookId,
                   std::string issueDate, std::string dueDate);
    bool returnBook(std::string memberId, std::string bookId,
                   std::string returnDate);
    bool reserveBook(std::string memberId, std::string bookId);
    bool renewBook(std::string memberId, std::string bookId,
                  std::string newDueDate);
    
    void displayAvailableBooks() const;
    void displayMemberBooks(std::string memberId) const;
    void displayAllMembers() const;
    void displayTransactionHistory() const;
    
private:
    Book* findBook(const std::string& bookId) const;
    Member* findMember(const std::string& memberId) const;
    Transaction* findTransaction(const std::string& bookId,
                               const std::string& memberId) const;
    std::string generateTransactionId();
};

#endif 