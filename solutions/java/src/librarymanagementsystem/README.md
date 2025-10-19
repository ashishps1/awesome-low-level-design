# 📚 Library Management System

A comprehensive library management system demonstrating **Object-Oriented Programming (OOP)**, **SOLID principles**, and **Design Patterns** in Java.

---

## 🎯 Features

### Core Features
- ✅ **Book Management** - Add, update, remove, and search books
- ✅ **Patron Management** - Register patrons with different membership types
- ✅ **Lending System** - Checkout and return books with due date tracking
- ✅ **Late Fee Calculation** - Automatic calculation of overdue fees
- ✅ **Search Functionality** - Search books by title, author, or ISBN

### Advanced Features
- ✅ **Reservation System** - Reserve unavailable books with queue management
- ✅ **Multi-Branch Support** - Manage multiple library branches
- ✅ **Book Transfer** - Transfer books between branches
- ✅ **Recommendation System** - Personalized book recommendations
- ✅ **Notification System** - Notify patrons about due dates and availability

---

## 🏗️ Architecture

### Project Structure
librarymanagementsystem/ 
    ├── models/ # Domain entities │
    ├── Book.java │ 
    ├── Patron.java │ 
    ├── LoanRecord.java │ 
    ├── Branch.java 
 
│ └── Reservation.java │ ├── patterns/ # Design pattern implementations │ ├── observer/ # Observer Pattern (Notifications) │ │ ├── Observer.java │ │ ├── Subject.java │ │ ├── PatronObserver.java │ │ └── BookSubject.java │ │ │ ├── factory/ # Factory Pattern (Item Creation) │ │ ├── LibraryItem.java │ │ ├── BookItem.java │ │ ├── MagazineItem.java │ │ └── LibraryItemFactory.java │ │ │ └── strategy/ # Strategy Pattern (Late Fees) │ ├── LateFeeStrategy.java │ ├── BookLateFeeStrategy.java │ ├── MagazineLateFeeStrategy.java │ └── PremiumLateFeeStrategy.java │ ├── services/ # Business logic layer │ ├── BookService.java │ ├── PatronService.java │ ├── LoanService.java │ ├── ReservationService.java │ ├── BranchService.java │ ├── NotificationService.java │ └── RecommendationService.java │ ├── repositories/ # Data access layer │ ├── Repository.java │ ├── BookRepository.java │ ├── PatronRepository.java │ └── LoanRepository.java │ ├── exceptions/ # Custom exceptions │ ├── BookNotFoundException.java │ ├── PatronNotFoundException.java │ └── BookNotAvailableException.java │ ├── utils/ # Utility classes │ ├── IdGenerator.java │ └── Logger.java │ ├── LibraryManagementSystem.java # Main system (Facade) └── LibraryDemo.java # Demo application
---

## 🎨 Design Patterns Implemented

### 1. **Observer Pattern** 👁️
**Purpose:** Notify patrons when reserved books become available

**Implementation:**
- `Subject` interface - Book availability notifications
- `Observer` interface - Patron notification receiver
- `PatronObserver` - Concrete observer for patrons
- `NotificationService` - Manages observers

**Usage:**
```java
// Patron automatically notified when book is returned
reservationService.reserveBook(isbn, patronId);
// When book is returned, observer is notified
library.returnBook(isbn, anotherPatronId);