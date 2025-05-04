# ATM System (LLD)

## Problem Statement

Design and implement an ATM (Automated Teller Machine) system that allows users to perform basic banking operations such as balance inquiry, cash withdrawal, and cash deposit, with secure authentication and proper cash management.

---

## Requirements

- **User Authentication:** Users must authenticate using a card and PIN.
- **Balance Inquiry:** Users can check their account balance.
- **Cash Withdrawal:** Users can withdraw cash if sufficient balance and cash are available.
- **Cash Deposit:** Users can deposit cash into their account.
- **Transaction Management:** The system records and processes transactions (withdrawal, deposit).
- **Banking Service Integration:** The ATM interacts with a backend banking service to validate accounts and perform transactions.
- **Cash Dispenser:** The ATM manages its own cash inventory and dispenses cash securely.
- **Concurrency & Consistency:** The system handles concurrent access and ensures data consistency.
- **User Interface:** The ATM provides a user-friendly interface for operations.
- **Extensibility:** Easy to add new features such as mini-statements, fund transfers, or multi-currency support.

---

## Core Entities

- **ATM:** Main class for ATM operations; interacts with `BankingService` and `CashDispenser`.
- **Card:** Represents an ATM card with card number and PIN.
- **Account:** Represents a bank account with account number and balance; supports debit and credit operations.
- **Transaction (abstract):** Base class for transactions; extended by `WithdrawalTransaction` and `DepositTransaction`.
- **WithdrawalTransaction / DepositTransaction:** Concrete transaction types for withdrawal and deposit.
- **BankingService:** Manages bank accounts and processes transactions; uses thread-safe data structures.
- **CashDispenser:** Manages the ATM's cash inventory and handles dispensing; ensures thread safety.
- **ATMDemo:** Demonstrates the usage of the ATM system with sample accounts and operations.

---

## Class Design

### 1. ATM
- **Fields:** BankingService bankingService, CashDispenser cashDispenser
- **Methods:** authenticateUser(Card), checkBalance(String accountNumber), withdrawCash(String accountNumber, double amount), depositCash(String accountNumber, double amount)

### 2. Card
- **Fields:** String cardNumber, String pin

### 3. Account
- **Fields:** String accountNumber, double balance
- **Methods:** debit(double), credit(double), getBalance()

### 4. Transaction (abstract)
- **Fields:** String accountNumber, double amount, Date date
- **Methods:** process()

### 5. WithdrawalTransaction / DepositTransaction
- **Inherits:** Transaction
- **Methods:** process()

### 6. BankingService
- **Fields:** Map<String, Account> accounts
- **Methods:** createAccount(String, double), getAccount(String), processTransaction(Transaction)

### 7. CashDispenser
- **Fields:** double cashAvailable
- **Methods:** dispenseCash(double), addCash(double), getCashAvailable()

### 8. ATMDemo
- **Methods:** run() — demonstrates sample ATM operations

---

## Example Usage

```java
BankingService bankingService = new BankingService();
CashDispenser cashDispenser = new CashDispenser(10000);
ATM atm = new ATM(bankingService, cashDispenser);

bankingService.createAccount("1234567890", 1000.0);
Card card = new Card("1234567890", "1234");
atm.authenticateUser(card);

double balance = atm.checkBalance("1234567890");
atm.withdrawCash("1234567890", 500.0);
atm.depositCash("1234567890", 200.0);
```

---

## Demo

See `ATMDemo.java` for a sample usage and simulation of the ATM system.

---

## Extending the Framework

- **Add mini-statements:** Show recent transactions.
- **Add fund transfers:** Allow transfers between accounts.
- **Add multi-currency support:** Handle different currencies and conversions.

---