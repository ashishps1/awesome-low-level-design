# Digital Wallet Service (LLD)

## Problem Statement

Design and implement a Digital Wallet Service that allows users to manage their digital money, make transactions, and link multiple payment methods. The system should handle currency conversions, track transactions, and manage different types of accounts.

---

## Requirements

1. **Account Management:**
   - Create and manage user accounts
   - Support multiple payment methods (Bank Account, Credit Card)
   - Handle account balances and transactions

2. **Transaction Management:**
   - Process money transfers
   - Track transaction history
   - Handle transaction status and types

3. **Payment Methods:**
   - Support bank account integration
   - Support credit card integration
   - Allow adding/removing payment methods

4. **Currency Support:**
   - Handle multiple currencies
   - Provide currency conversion
   - Maintain exchange rates

5. **Security and Validation:**
   - Validate transactions
   - Handle insufficient funds
   - Ensure data consistency

---

## Core Entities

### 1. DigitalWallet
- **Fields:** String id, User user, double balance, List<PaymentMethod> paymentMethods, List<Transaction> transactions
- **Methods:** addMoney(), sendMoney(), getBalance(), addPaymentMethod(), removePaymentMethod()

### 2. User
- **Fields:** String id, String name, String email, String phoneNumber
- **Methods:** updateProfile(), getWallet()

### 3. Account
- **Fields:** String id, User user, double balance, Currency currency
- **Methods:** deposit(), withdraw(), getBalance()

### 4. PaymentMethod
- **Fields:** String id, User user, PaymentMethodType type
- **Methods:** validate(), processPayment()

### 5. BankAccount
- **Fields:** String accountNumber, String bankName, String ifscCode
- **Methods:** transfer(), validate()

### 6. CreditCard
- **Fields:** String cardNumber, String expiryDate, String cvv
- **Methods:** charge(), validate()

### 7. Transaction
- **Fields:** String id, Account from, Account to, double amount, Currency currency, TransactionStatus status
- **Methods:** process(), cancel(), getStatus()

### 8. Currency
- **Fields:** String code, String symbol
- **Methods:** getExchangeRate()

### 9. CurrencyConverter
- **Methods:** convert(double amount, Currency from, Currency to)

---

## Example Usage

```java
// Create a new user
User user = new User("John Doe", "john@example.com", "1234567890");

// Create a digital wallet
DigitalWallet wallet = new DigitalWallet(user);

// Add a bank account
BankAccount bankAccount = new BankAccount("1234567890", "HDFC Bank", "HDFC0001234");
wallet.addPaymentMethod(bankAccount);

// Add money to wallet
wallet.addMoney(1000.0, Currency.USD);

// Send money to another user
User recipient = new User("Jane Doe", "jane@example.com", "9876543210");
wallet.sendMoney(recipient.getWallet(), 500.0, Currency.USD);
```

---

## Demo

See `DigitalWalletDemo.java` for a sample usage and simulation of the digital wallet system.

---

## Extending the Framework

- **Add authentication:** Implement user authentication and authorization
- **Add transaction limits:** Set and enforce transaction limits
- **Add rewards system:** Implement cashback and rewards
- **Add bill payments:** Support utility bill payments
- **Add investment options:** Support investment in various instruments
- **Add notification system:** Send transaction alerts and updates

---

## Design Patterns Used

- **Factory Pattern:** For creating different types of payment methods
- **Strategy Pattern:** For different payment processing strategies
- **Observer Pattern:** For transaction notifications
- **Singleton Pattern:** For currency converter service

---

## Exception Handling

- **InsufficientFundsException:** Thrown when there are insufficient funds for a transaction
- **InvalidPaymentMethodException:** Thrown when payment method validation fails
- **TransactionFailedException:** Thrown when transaction processing fails

---