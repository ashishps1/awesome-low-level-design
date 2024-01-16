# Designing a Digital Wallet System

In this article, we will explore the object-oriented design and implementation of a Digital Wallet System using Java. 

This system facilitates online transactions, enabling users to store money digitally and make secure payments.

## System Requirements

The Digital Wallet System should:

1. **User Account Management**: Manage user account creation and maintenance.
2. **Wallet Management**: Allow users to add, withdraw, and check balances.
3. **Transaction Processing**: Handle transactions and maintain a history.
4. **Security and Authentication**: Ensure secure access and transaction integrity.

## Core Use Cases

1. **Creating and Managing User Accounts**
2. **Adding and Withdrawing Funds**
3. **Making and Receiving Payments**
4. **Viewing Transaction History**

## Key Classes:
- `DigitalWalletSystem`: Manages the system.
- `User`: Represents a user.
- `Wallet`: Manages a user's wallet.
- `Transaction`: Represents a transaction.

## Java Implementation

### User Class

Manages user account information.

```java
public class User {
    private String userId;
    private String name;
    private Wallet wallet;

    public User(String userId, String name) {
        this.userId = userId;
        this.name = name;
        this.wallet = new Wallet(this);
    }

    // Getters and setters...
}
```
### Wallet Class
Represents a user's digital wallet.
```java
import java.util.ArrayList;
import java.util.List;

public class Wallet {
    private User user;
    private double balance;
    private List<Transaction> transactionHistory;

    public Wallet(User user) {
        this.user = user;
        this.balance = 0.0;
        this.transactionHistory = new ArrayList<>();
    }

    public boolean addFunds(double amount) {
        if (amount <= 0) {
            return false;
        }
        balance += amount;
        transactionHistory.add(new Transaction("Deposit", amount, balance));
        return true;
    }

    public boolean withdrawFunds(double amount) {
        if (amount > balance) {
            return false;
        }
        balance -= amount;
        transactionHistory.add(new Transaction("Withdrawal", amount, balance));
        return true;
    }

    // Getters and setters...
}
```
### Transaction Class
Represents a financial transaction.
```java
import java.util.Date;

public class Transaction {
    private String type;
    private double amount;
    private Date date;
    private double postTransactionBalance;

    public Transaction(String type, double amount, double postTransactionBalance) {
        this.type = type;
        this.amount = amount;
        this.date = new Date();
        this.postTransactionBalance = postTransactionBalance;
    }

    // Getters and setters...
}
```
### DigitalWalletSystem Class
Manages the digital wallet system operations.
```java
import java.util.ArrayList;
import java.util.List;

public class DigitalWalletSystem {
    private List<User> users;

    public DigitalWalletSystem() {
        this.users = new ArrayList<>();
    }

    public void addUser(User user) {
        users.add(user);
    }

    public boolean transferFunds(String senderUserId, String receiverUserId, double amount) {
        User sender = users.get(senderUserId);
        User receiver = users.get(receiverUserId);

        if (sender != null && receiver != null) {
            Wallet senderWallet = sender.getWallet();
            Wallet receiverWallet = receiver.getWallet();

            if (senderWallet.deductFunds(amount)) {
                receiverWallet.addFunds(amount);
                return true;
            }
        }
        return false;
    }
    
    // Other necessary methods...
}
```