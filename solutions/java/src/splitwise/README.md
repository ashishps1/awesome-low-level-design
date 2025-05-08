# Splitwise System (LLD)

## Problem Statement

Design and implement a Splitwise System that allows users to split expenses among groups and individuals. The system should handle expense tracking, balance calculations, and settlement of debts between users.

---

## Requirements

1. **User Management:**
   - Create and manage user profiles
   - Track user balances
   - Handle user relationships

2. **Group Management:**
   - Create and manage groups
   - Add/remove members
   - Track group expenses

3. **Expense Management:**
   - Add expenses to groups or individuals
   - Support different split types (EQUAL, EXACT, PERCENTAGE)
   - Track expense history

4. **Balance Management:**
   - Calculate balances between users
   - Track who owes whom
   - Handle settlements

5. **Transaction Management:**
   - Record transactions
   - Track payment status
   - Generate balance reports

---

## Core Entities

### 1. SplitwiseService
- **Fields:** List<User> users, List<Group> groups, List<Expense> expenses
- **Methods:** 
  - addUser()
  - createGroup()
  - addExpense()
  - getBalance()
  - settleExpense()

### 2. User
- **Fields:** String id, String name, String email, Map<User, Double> balances
- **Methods:** 
  - updateProfile()
  - getBalance()
  - addBalance()
  - subtractBalance()

### 3. Group
- **Fields:** String id, String name, List<User> members, List<Expense> expenses
- **Methods:** 
  - addMember()
  - removeMember()
  - addExpense()
  - getBalances()

### 4. Expense
- **Fields:** String id, String description, double amount, User paidBy, List<User> paidFor, SplitType splitType
- **Methods:** 
  - calculateSplits()
  - getAmount()
  - getPaidBy()

### 5. Transaction
- **Fields:** String id, User from, User to, double amount
- **Methods:** 
  - execute()
  - getStatus()

### 6. SplitType (Enum)
- **Values:** EQUAL, EXACT, PERCENTAGE

---

## Example Usage

```java
SplitwiseService service = new SplitwiseService();

// Create users
User user1 = service.addUser("John", "john@example.com");
User user2 = service.addUser("Jane", "jane@example.com");

// Create a group
Group group = service.createGroup("Trip to Paris");
group.addMember(user1);
group.addMember(user2);

// Add an expense
Expense expense = service.addExpense(
    "Dinner", 
    100.0, 
    user1, 
    Arrays.asList(user1, user2), 
    SplitType.EQUAL
);

// Get balances
double balance = service.getBalance(user1, user2);

// Settle expense
service.settleExpense(user2, user1, 50.0);
```

---

## Demo

See `SplitwiseDemo.java` for a sample usage and simulation of the Splitwise system.

---

## Extending the Framework

- **Add expense categories:** Categorize expenses (food, travel, etc.)
- **Add recurring expenses:** Support for regular payments
- **Add expense comments:** Allow users to add notes to expenses
- **Add expense attachments:** Support for receipts and documents
- **Add payment integration:** Integrate with payment gateways
- **Add notification system:** Send reminders for pending payments

---

## Design Patterns Used

- **Singleton Pattern:** For the Splitwise service instance
- **Factory Pattern:** For creating different types of splits
- **Strategy Pattern:** For different expense splitting strategies
- **Observer Pattern:** For balance updates and notifications

---

## Exception Handling

- **InvalidAmountException:** Thrown when expense amount is invalid
- **InvalidSplitException:** Thrown when split details are invalid
- **UserNotFoundException:** Thrown when user is not found
- **GroupNotFoundException:** Thrown when group is not found
- **InsufficientBalanceException:** Thrown when user has insufficient balance

---