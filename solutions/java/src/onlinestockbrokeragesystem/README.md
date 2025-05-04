# Online Stock Brokerage System (LLD)

## Problem Statement

Design and implement an Online Stock Brokerage System that allows users to manage accounts, place buy and sell orders for stocks, maintain portfolios, and handle order execution and exceptions.

---

## Requirements

- **User Management:** Users can register and manage their accounts.
- **Account Management:** Each user has an account with a balance for trading.
- **Stock Management:** The system manages a list of stocks with their details and prices.
- **Portfolio Management:** Users can view and manage their stock holdings (portfolio).
- **Order Placement:** Users can place buy and sell orders for stocks.
- **Order Execution:** The system executes orders, updates portfolios and account balances.
- **Order Status Tracking:** Orders have statuses (e.g., PENDING, COMPLETED, FAILED).
- **Exception Handling:** The system handles insufficient funds and insufficient stock scenarios.
- **Extensibility:** Easy to add new order types, features, or support for multiple exchanges.

---

## Core Entities

- **StockBroker:** Main class that manages users, accounts, stocks, and order processing.
- **User:** Represents a user with a unique ID and name.
- **Account:** Represents a user's trading account with a balance.
- **Portfolio:** Represents a user's stock holdings.
- **Stock:** Represents a stock with a symbol, name, and price.
- **Order:** Abstract class representing a buy or sell order.
- **BuyOrder / SellOrder:** Concrete classes for buy and sell orders.
- **OrderStatus:** Enum for order status (PENDING, COMPLETED, FAILED).
- **InsufficientFundsException / InsufficientStockException:** Custom exceptions for error handling.

---

## Class Design

### 1. StockBroker
- **Fields:** Map<Integer, User> users, Map<Integer, Account> accounts, Map<Integer, Portfolio> portfolios, Map<String, Stock> stocks
- **Methods:** registerUser(User), createAccount(User, double initialBalance), addStock(Stock), placeOrder(Order), getPortfolio(User), getAccount(User), etc.

### 2. User
- **Fields:** int id, String name

### 3. Account
- **Fields:** int userId, double balance
- **Methods:** deposit(double), withdraw(double), getBalance()

### 4. Portfolio
- **Fields:** int userId, Map<String, Integer> stockHoldings
- **Methods:** addStock(Stock, int quantity), removeStock(Stock, int quantity), getHoldings()

### 5. Stock
- **Fields:** String symbol, String name, double price

### 6. Order (abstract)
- **Fields:** int userId, String stockSymbol, int quantity, double price, OrderStatus status
- **Methods:** execute(StockBroker)

### 7. BuyOrder / SellOrder
- **Inherits:** Order
- **Methods:** execute(StockBroker)

### 8. OrderStatus (enum)
- Values: PENDING, COMPLETED, FAILED

### 9. InsufficientFundsException / InsufficientStockException
- Custom exceptions for error handling

---

## Example Usage

```java
StockBroker broker = new StockBroker();
User alice = new User(1, "Alice");
broker.registerUser(alice);
broker.createAccount(alice, 10000.0);

Stock apple = new Stock("AAPL", "Apple Inc.", 150.0);
broker.addStock(apple);

Order buyOrder = new BuyOrder(alice.getId(), "AAPL", 10, 150.0);
broker.placeOrder(buyOrder);

Portfolio alicePortfolio = broker.getPortfolio(alice);
System.out.println(alicePortfolio.getHoldings());
```

---

## Demo

See `StockBrokerageSystemDemo.java` for a sample usage and simulation of the stock brokerage system.

---

## Extending the Framework

- **Add new order types:** Such as limit orders, stop-loss orders, etc.
- **Support multiple exchanges:** Manage stocks and orders across different exchanges.
- **Add features:** Such as transaction history, reporting, or margin trading.

---