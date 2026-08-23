// Single-file build (no header files) — merged from the multi-file project.
// Build & run:  g++ -std=c++17 main.cpp -o app && ./app
#include <algorithm>
#include <iomanip>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

// ----- forward declarations -----
class Book;
class Member;
class Transaction;
class LibraryManager;

// ===== Book.hpp =====
enum class BookStatus {
    AVAILABLE,
    BORROWED,
    RESERVED,
    LOST
};

class Book {
private:
    string bookId;
    string title;
    string author;
    string publisher;
    string isbn;
    BookStatus status;
    int publicationYear;

public:
    Book(string bookId, string title, string author,
         string publisher, string isbn, int publicationYear);
    
    string getBookId() const;
    string getTitle() const;
    string getAuthor() const;
    string getPublisher() const;
    string getIsbn() const;
    BookStatus getStatus() const;
    int getPublicationYear() const;
    
    void setStatus(BookStatus status);
    void displayInfo() const;
};

// ===== Member.hpp =====
class Member {
private:
    string memberId;
    string name;
    string email;
    string phone;
    vector<Book*> borrowedBooks;
    bool active;

public:
    Member(string memberId, string name, string email, string phone);
    
    string getMemberId() const;
    string getName() const;
    string getEmail() const;
    string getPhone() const;
    bool isActive() const;
    const vector<Book*>& getBorrowedBooks() const;
    
    void addBorrowedBook(Book* book);
    void removeBorrowedBook(Book* book);
    void setActive(bool status);
    void displayInfo() const;
};

// ===== Transaction.hpp =====
enum class TransactionType {
    BORROW,
    RETURN,
    RESERVE,
    RENEW
};

class Transaction {
private:
    string transactionId;
    Book* book;
    Member* member;
    TransactionType type;
    string issueDate;
    string dueDate;
    string returnDate;
    double fine;

public:
    Transaction(string transactionId, Book* book, Member* member,
               TransactionType type, string issueDate, string dueDate);
    
    string getTransactionId() const;
    Book* getBook() const;
    Member* getMember() const;
    TransactionType getType() const;
    string getIssueDate() const;
    string getDueDate() const;
    string getReturnDate() const;
    double getFine() const;
    
    void setReturnDate(string date);
    void setFine(double amount);
    void displayInfo() const;
};

// ===== LibraryManager.hpp =====
class LibraryManager {
private:
    vector<Book*> books;
    vector<Member*> members;
    vector<Transaction*> transactions;
    int transactionIdCounter;

public:
    LibraryManager();
    ~LibraryManager();
    
    void addBook(Book* book);
    void addMember(Member* member);
    
    bool borrowBook(string memberId, string bookId,
                   string issueDate, string dueDate);
    bool returnBook(string memberId, string bookId,
                   string returnDate);
    bool reserveBook(string memberId, string bookId);
    bool renewBook(string memberId, string bookId,
                  string newDueDate);
    
    void displayAvailableBooks() const;
    void displayMemberBooks(string memberId) const;
    void displayAllMembers() const;
    void displayTransactionHistory() const;
    
private:
    Book* findBook(const string& bookId) const;
    Member* findMember(const string& memberId) const;
    Transaction* findTransaction(const string& bookId,
                               const string& memberId) const;
    string generateTransactionId();
};

// ===== Book.cpp =====
Book::Book(string bookId, string title, string author,
           string publisher, string isbn, int publicationYear)
    : bookId(bookId), title(title), author(author), publisher(publisher),
      isbn(isbn), status(BookStatus::AVAILABLE), publicationYear(publicationYear) {}

string Book::getBookId() const { return bookId; }
string Book::getTitle() const { return title; }
string Book::getAuthor() const { return author; }
string Book::getPublisher() const { return publisher; }
string Book::getIsbn() const { return isbn; }
BookStatus Book::getStatus() const { return status; }
int Book::getPublicationYear() const { return publicationYear; }

void Book::setStatus(BookStatus status) {
    this->status = status;
}

void Book::displayInfo() const {
    cout << "Book: " << title << " (ID: " << bookId << ")" << endl;
    cout << "Author: " << author << endl;
    cout << "Publisher: " << publisher << endl;
    cout << "ISBN: " << isbn << endl;
    cout << "Publication Year: " << publicationYear << endl;
    cout << "Status: ";
    switch (status) {
        case BookStatus::AVAILABLE: cout << "Available"; break;
        case BookStatus::BORROWED: cout << "Borrowed"; break;
        case BookStatus::RESERVED: cout << "Reserved"; break;
        case BookStatus::LOST: cout << "Lost"; break;
    }
    cout << endl;
} 

// ===== LibraryManager.cpp =====
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

bool LibraryManager::borrowBook(string memberId, string bookId,
                              string issueDate, string dueDate) {
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

bool LibraryManager::returnBook(string memberId, string bookId,
                              string returnDate) {
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

bool LibraryManager::reserveBook(string memberId, string bookId) {
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

bool LibraryManager::renewBook(string memberId, string bookId,
                             string newDueDate) {
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
    cout << "\nAvailable Books:" << endl;
    for (const auto& book : books) {
        if (book->getStatus() == BookStatus::AVAILABLE) {
            book->displayInfo();
            cout << "------------------------" << endl;
        }
    }
}

void LibraryManager::displayMemberBooks(string memberId) const {
    Member* member = findMember(memberId);
    if (!member) return;
    
    cout << "\nBooks borrowed by " << member->getName() << ":" << endl;
    for (const auto& book : member->getBorrowedBooks()) {
        book->displayInfo();
        cout << "------------------------" << endl;
    }
}

void LibraryManager::displayAllMembers() const {
    cout << "\nAll Members:" << endl;
    for (const auto& member : members) {
        member->displayInfo();
        cout << "------------------------" << endl;
    }
}

void LibraryManager::displayTransactionHistory() const {
    cout << "\nTransaction History:" << endl;
    for (const auto& transaction : transactions) {
        transaction->displayInfo();
        cout << "------------------------" << endl;
    }
}

Book* LibraryManager::findBook(const string& bookId) const {
    for (auto book : books) {
        if (book->getBookId() == bookId) return book;
    }
    return nullptr;
}

Member* LibraryManager::findMember(const string& memberId) const {
    for (auto member : members) {
        if (member->getMemberId() == memberId) return member;
    }
    return nullptr;
}

Transaction* LibraryManager::findTransaction(const string& bookId,
                                          const string& memberId) const {
    for (auto transaction : transactions) {
        if (transaction->getBook()->getBookId() == bookId &&
            transaction->getMember()->getMemberId() == memberId &&
            transaction->getType() == TransactionType::BORROW) {
            return transaction;
        }
    }
    return nullptr;
}

string LibraryManager::generateTransactionId() {
    return "T" + to_string(transactionIdCounter++);
} 

// ===== Member.cpp =====
Member::Member(string memberId, string name, string email, string phone)
    : memberId(memberId), name(name), email(email), phone(phone), active(true) {}

string Member::getMemberId() const { return memberId; }
string Member::getName() const { return name; }
string Member::getEmail() const { return email; }
string Member::getPhone() const { return phone; }
bool Member::isActive() const { return active; }
const vector<Book*>& Member::getBorrowedBooks() const { return borrowedBooks; }

void Member::addBorrowedBook(Book* book) {
    borrowedBooks.push_back(book);
}

void Member::removeBorrowedBook(Book* book) {
    auto it = find(borrowedBooks.begin(), borrowedBooks.end(), book);
    if (it != borrowedBooks.end()) {
        borrowedBooks.erase(it);
    }
}

void Member::setActive(bool status) {
    active = status;
}

void Member::displayInfo() const {
    cout << "Member: " << name << " (ID: " << memberId << ")" << endl;
    cout << "Email: " << email << endl;
    cout << "Phone: " << phone << endl;
    cout << "Status: " << (active ? "Active" : "Inactive") << endl;
    cout << "Borrowed Books: " << borrowedBooks.size() << endl;
} 

// ===== Transaction.cpp =====
Transaction::Transaction(string transactionId, Book* book, Member* member,
                       TransactionType type, string issueDate, string dueDate)
    : transactionId(transactionId), book(book), member(member), type(type),
      issueDate(issueDate), dueDate(dueDate), fine(0.0) {}

string Transaction::getTransactionId() const { return transactionId; }
Book* Transaction::getBook() const { return book; }
Member* Transaction::getMember() const { return member; }
TransactionType Transaction::getType() const { return type; }
string Transaction::getIssueDate() const { return issueDate; }
string Transaction::getDueDate() const { return dueDate; }
string Transaction::getReturnDate() const { return returnDate; }
double Transaction::getFine() const { return fine; }

void Transaction::setReturnDate(string date) {
    returnDate = date;
}

void Transaction::setFine(double amount) {
    fine = amount;
}

void Transaction::displayInfo() const {
    cout << "\nTransaction Details:" << endl;
    cout << "Transaction ID: " << transactionId << endl;
    cout << "Book: " << book->getTitle() << endl;
    cout << "Member: " << member->getName() << endl;
    cout << "Type: ";
    switch (type) {
        case TransactionType::BORROW: cout << "Borrow"; break;
        case TransactionType::RETURN: cout << "Return"; break;
        case TransactionType::RESERVE: cout << "Reserve"; break;
        case TransactionType::RENEW: cout << "Renew"; break;
    }
    cout << endl;
    cout << "Issue Date: " << issueDate << endl;
    cout << "Due Date: " << dueDate << endl;
    if (!returnDate.empty()) {
        cout << "Return Date: " << returnDate << endl;
    }
    if (fine > 0) {
        cout << "Fine: $" << fixed << setprecision(2) << fine << endl;
    }
} 

// ===== LibraryDemo.cpp =====
int main() {
    LibraryManager library;
    
    // Add books
    Book* book1 = new Book("B001", "The Great Gatsby", "F. Scott Fitzgerald",
                          "Scribner", "978-0743273565", 1925);
    Book* book2 = new Book("B002", "To Kill a Mockingbird", "Harper Lee",
                          "HarperCollins", "978-0446310789", 1960);
    
    library.addBook(book1);
    library.addBook(book2);
    
    // Add members
    Member* member1 = new Member("M001", "John Doe", "john@example.com",
                               "+1-555-0123");
    library.addMember(member1);
    
    // Display available books
    library.displayAvailableBooks();
    
    // Borrow a book
    if (library.borrowBook("M001", "B001", "2024-01-01", "2024-01-15")) {
        cout << "\nBook borrowed successfully!" << endl;
    }
    
    // Display member's books
    library.displayMemberBooks("M001");
    
    // Return the book
    if (library.returnBook("M001", "B001", "2024-01-10")) {
        cout << "\nBook returned successfully!" << endl;
    }
    
    // Display transaction history
    library.displayTransactionHistory();
    
    return 0;
} 

