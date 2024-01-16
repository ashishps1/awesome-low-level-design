# Designing an ATM System

This article covers the design and implementation of an Automated Teller Machine (ATM) system using object-oriented programming in Java.

## System Requirements
Our ATM system is designed to handle:
1. **Authentication:** Verifying user identity using a card number and PIN.
2. **Account Management:** Managing different account types.
3. **Balance Inquiry:** Checking the account balance.
4. **Cash Withdrawal and Deposit:** Handling money transactions.
5. **Transaction History:** Providing a record of past transactions.

## Core Use Cases
- **User Authentication**
- **Performing Transactions:** Withdrawals, deposits, balance inquiries.
- **Printing Transaction Receipts** (optional for this implementation)

## Key Classes:
- `ATM`: The main class to interact with users.
- `Account`: To manage account details.
- `Bank`: Represents the bank system that verifies transactions.
- `CardReader`: To read user's card data.
- `CashDispenser`: To manage cash dispensing.

## Java Implementation
### Account Class
```java
public class Account {
    private String accountNumber;
    private double balance;

    public Account(String accountNumber, double initialBalance) {
        this.accountNumber = accountNumber;
        this.balance = initialBalance;
    }

    public boolean withdraw(double amount) {
        if (amount > balance) {
            return false; // Insufficient balance
        }
        balance -= amount;
        return true;
    }

    public void deposit(double amount) {
        balance += amount;
    }

    public double getBalance() {
        return balance;
    }

    // Other necessary methods...
}
```
### 
ATM Class
```java
public class ATM {
    private Account currentAccount;
    private Bank bank;

    public ATM(Bank bank) {
        this.bank = bank;
    }

    public boolean authenticateUser(String accountNumber, String pin) {
        this.currentAccount = bank.verifyAccount(accountNumber, pin);
        return currentAccount != null;
    }

    public double checkBalance() {
        return currentAccount.getBalance();
    }

    public boolean withdraw(double amount) {
        return currentAccount.withdraw(amount);
    }

    public void deposit(double amount) {
        currentAccount.deposit(amount);
    }

    // Other necessary methods...
}
```
### Bank Class
```java
public class Bank {
    private Map<String, Account> accounts;

    public Bank() {
        accounts = new HashMap<>();
        // Initialize with some accounts
    }

    public Account verifyAccount(String accountNumber, String pin) {
        // Verify account based on accountNumber and PIN
        // Return account if verified, else return null
    }

    // Other necessary methods...
}
```