#include "LibraryManager.hpp"
#include <iostream>

LibraryManager::LibraryManager() : transactionIdCounter(1) {}

LibraryManager::~LibraryManager() {
    for (auto book : books) delete book;
    for (auto member : members) delete member;
    for (auto transaction : transactions) delete transaction;
}

void LibraryManager::addBook(Book* book) {
    books.push_back(book);
}

void LibraryManager::addMember(Member* member) {
    members.push_back(member);
}

bool LibraryManager::borrowBook(std::string memberId, std::string bookId,
                              std::string issueDate, std::string dueDate) {
    Member* member = findMember(memberId);
    Book* book = findBook(bookId);
    
    if (!member || !member->isActive() || !book || 
        book->getStatus() != BookStatus::AVAILABLE) {
        return false;
    }
    
    Transaction* transaction = new Transaction(
        generateTransactionId(),
        book,
        member,
        TransactionType::BORROW,
        issueDate,
        dueDate
    );
    
    transactions.push_back(transaction);
    book->setStatus(BookStatus::BORROWED);
    member->addBorrowedBook(book);
    return true;
}

bool LibraryManager::returnBook(std::string memberId, std::string bookId,
                              std::string returnDate) {
    Member* member = findMember(memberId);
    Book* book = findBook(bookId);
    Transaction* transaction = findTransaction(bookId, memberId);
    
    if (!member || !book || !transaction || 
        book->getStatus() != BookStatus::BORROWED) {
        return false;
    }
    
    transaction->setReturnDate(returnDate);
    book->setStatus(BookStatus::AVAILABLE);
    member->removeBorrowedBook(book);
    
    // Create return transaction
    Transaction* returnTrans = new Transaction(
        generateTransactionId(),
        book,
        member,
        TransactionType::RETURN,
        returnDate,
        returnDate
    );
    transactions.push_back(returnTrans);
    
    return true;
}

bool LibraryManager::reserveBook(std::string memberId, std::string bookId) {
    Member* member = findMember(memberId);
    Book* book = findBook(bookId);
    
    if (!member || !member->isActive() || !book || 
        book->getStatus() != BookStatus::AVAILABLE) {
        return false;
    }
    
    book->setStatus(BookStatus::RESERVED);
    Transaction* transaction = new Transaction(
        generateTransactionId(),
        book,
        member,
        TransactionType::RESERVE,
        "NOW",  // Should use actual datetime
        "NOW"   // Should use actual datetime
    );
    transactions.push_back(transaction);
    return true;
}

bool LibraryManager::renewBook(std::string memberId, std::string bookId,
                             std::string newDueDate) {
    Member* member = findMember(memberId);
    Book* book = findBook(bookId);
    Transaction* transaction = findTransaction(bookId, memberId);
    
    if (!member || !book || !transaction || 
        book->getStatus() != BookStatus::BORROWED) {
        return false;
    }
    
    Transaction* renewTrans = new Transaction(
        generateTransactionId(),
        book,
        member,
        TransactionType::RENEW,
        transaction->getDueDate(),
        newDueDate
    );
    transactions.push_back(renewTrans);
    return true;
}

void LibraryManager::displayAvailableBooks() const {
    std::cout << "\nAvailable Books:" << std::endl;
    for (const auto& book : books) {
        if (book->getStatus() == BookStatus::AVAILABLE) {
            book->displayInfo();
            std::cout << "------------------------" << std::endl;
        }
    }
}

void LibraryManager::displayMemberBooks(std::string memberId) const {
    Member* member = findMember(memberId);
    if (!member) return;
    
    std::cout << "\nBooks borrowed by " << member->getName() << ":" << std::endl;
    for (const auto& book : member->getBorrowedBooks()) {
        book->displayInfo();
        std::cout << "------------------------" << std::endl;
    }
}

void LibraryManager::displayAllMembers() const {
    std::cout << "\nAll Members:" << std::endl;
    for (const auto& member : members) {
        member->displayInfo();
        std::cout << "------------------------" << std::endl;
    }
}

void LibraryManager::displayTransactionHistory() const {
    std::cout << "\nTransaction History:" << std::endl;
    for (const auto& transaction : transactions) {
        transaction->displayInfo();
        std::cout << "------------------------" << std::endl;
    }
}

Book* LibraryManager::findBook(const std::string& bookId) const {
    for (auto book : books) {
        if (book->getBookId() == bookId) return book;
    }
    return nullptr;
}

Member* LibraryManager::findMember(const std::string& memberId) const {
    for (auto member : members) {
        if (member->getMemberId() == memberId) return member;
    }
    return nullptr;
}

Transaction* LibraryManager::findTransaction(const std::string& bookId,
                                          const std::string& memberId) const {
    for (auto transaction : transactions) {
        if (transaction->getBook()->getBookId() == bookId &&
            transaction->getMember()->getMemberId() == memberId &&
            transaction->getType() == TransactionType::BORROW) {
            return transaction;
        }
    }
    return nullptr;
}

std::string LibraryManager::generateTransactionId() {
    return "T" + std::to_string(transactionIdCounter++);
} 