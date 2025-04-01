#ifndef TRANSACTION_HPP
#define TRANSACTION_HPP

#include <string>
#include "Book.hpp"
#include "Member.hpp"

enum class TransactionType {
    BORROW,
    RETURN,
    RESERVE,
    RENEW
};

class Transaction {
private:
    std::string transactionId;
    Book* book;
    Member* member;
    TransactionType type;
    std::string issueDate;
    std::string dueDate;
    std::string returnDate;
    double fine;

public:
    Transaction(std::string transactionId, Book* book, Member* member,
               TransactionType type, std::string issueDate, std::string dueDate);
    
    std::string getTransactionId() const;
    Book* getBook() const;
    Member* getMember() const;
    TransactionType getType() const;
    std::string getIssueDate() const;
    std::string getDueDate() const;
    std::string getReturnDate() const;
    double getFine() const;
    
    void setReturnDate(std::string date);
    void setFine(double amount);
    void displayInfo() const;
};

#endif 