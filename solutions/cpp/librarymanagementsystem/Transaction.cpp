#include "Transaction.hpp"
#include <iostream>
#include <iomanip>

Transaction::Transaction(std::string transactionId, Book* book, Member* member,
                       TransactionType type, std::string issueDate, std::string dueDate)
    : transactionId(transactionId), book(book), member(member), type(type),
      issueDate(issueDate), dueDate(dueDate), fine(0.0) {}

std::string Transaction::getTransactionId() const { return transactionId; }
Book* Transaction::getBook() const { return book; }
Member* Transaction::getMember() const { return member; }
TransactionType Transaction::getType() const { return type; }
std::string Transaction::getIssueDate() const { return issueDate; }
std::string Transaction::getDueDate() const { return dueDate; }
std::string Transaction::getReturnDate() const { return returnDate; }
double Transaction::getFine() const { return fine; }

void Transaction::setReturnDate(std::string date) {
    returnDate = date;
}

void Transaction::setFine(double amount) {
    fine = amount;
}

void Transaction::displayInfo() const {
    std::cout << "\nTransaction Details:" << std::endl;
    std::cout << "Transaction ID: " << transactionId << std::endl;
    std::cout << "Book: " << book->getTitle() << std::endl;
    std::cout << "Member: " << member->getName() << std::endl;
    std::cout << "Type: ";
    switch (type) {
        case TransactionType::BORROW: std::cout << "Borrow"; break;
        case TransactionType::RETURN: std::cout << "Return"; break;
        case TransactionType::RESERVE: std::cout << "Reserve"; break;
        case TransactionType::RENEW: std::cout << "Renew"; break;
    }
    std::cout << std::endl;
    std::cout << "Issue Date: " << issueDate << std::endl;
    std::cout << "Due Date: " << dueDate << std::endl;
    if (!returnDate.empty()) {
        std::cout << "Return Date: " << returnDate << std::endl;
    }
    if (fine > 0) {
        std::cout << "Fine: $" << std::fixed << std::setprecision(2) << fine << std::endl;
    }
} 