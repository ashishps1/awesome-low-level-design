# Online Stock Brokerage System (LLD)

## Problem Statement

Design and implement an Online Stock Brokerage System that allows users to buy and sell stocks, manage their portfolio, and track their investments. The system should handle order processing, account management, and stock trading.

---

## Requirements

1. **Account Management:**
   - Create and manage user accounts
   - Track account balance
   - Handle fund deposits and withdrawals

2. **Stock Management:**
   - Track available stocks
   - Maintain stock prices
   - Handle stock information

3. **Order Management:**
   - Process buy and sell orders
   - Track order status
   - Handle order execution

4. **Portfolio Management:**
   - Track user's stock holdings
   - Calculate portfolio value
   - Monitor investment performance

5. **Trading Rules:**
   - Validate order amounts
   - Check sufficient funds
   - Verify stock availability

---

## Core Entities

### 1. StockBroker
- **Fields:** List<Account> accounts, List<Stock> stocks, List<Order> orders
- **Methods:** 
  - createAccount()
  - placeBuyOrder()
  - placeSellOrder()
  - getPortfolio()
  - getStockPrice()

### 2. Account
- **Fields:** String id, User user, double balance, Portfolio portfolio
- **Methods:** 
  - deposit()
  - withdraw()
  - getBalance()
  - getPortfolio()

### 3. User
- **Fields:** String id, String name, String email
- **Methods:** 
  - getAccount()
  - updateProfile()

### 4. Stock
- **Fields:** String symbol, String name, double currentPrice
- **Methods:** 
  - updatePrice()
  - getPrice()

### 5. Order
- **Fields:** String id, Account account, Stock stock, int quantity, OrderStatus status
- **Methods:** 
  - execute()
  - cancel()
  - getStatus()

### 6. BuyOrder
- **Fields:** double price
- **Methods:** 
  - validateFunds()
  - execute()

### 7. SellOrder
- **Fields:** double price
- **Methods:** 
  - validateStocks()
  - execute()

### 8. Portfolio
- **Fields:** Map<Stock, Integer> holdings
- **Methods:** 
  - addStock()
  - removeStock()
  - getValue()

### 9. OrderStatus (Enum)
- **Values:** PENDING, EXECUTED, CANCELLED, FAILED

---

## Example Usage

```java
StockBroker broker = new StockBroker();

// Create a user account
User user = new User("John Doe", "john@example.com");
Account account = broker.createAccount(user);

// Deposit funds
account.deposit(10000.0);

// Place a buy order
Stock stock = broker.getStock("AAPL");
BuyOrder buyOrder = broker.placeBuyOrder(account, stock, 10);

// Place a sell order
SellOrder sellOrder = broker.placeSellOrder(account, stock, 5);

// Get portfolio
Portfolio portfolio = account.getPortfolio();
```

---

## Demo

See `StockBrokerageSystemDemo.java` for a sample usage and simulation of the stock brokerage system.

---

## Extending the Framework

- **Add real-time market data:** Integrate with market data providers
- **Add order types:** Support limit orders, stop-loss orders
- **Add trading strategies:** Implement automated trading strategies
- **Add transaction history:** Track all trading activities
- **Add reporting system:** Generate investment reports
- **Add notification system:** Send price alerts and order updates

---

## Design Patterns Used

- **Singleton Pattern:** For the stock broker instance
- **Factory Pattern:** For creating different types of orders
- **Observer Pattern:** For stock price updates
- **Strategy Pattern:** For different order execution strategies

---

## Exception Handling

- **InsufficientFundsException:** Thrown when account has insufficient funds
- **InsufficientStockException:** Thrown when portfolio has insufficient stocks
- **InvalidOrderException:** Thrown when order details are invalid
- **OrderExecutionException:** Thrown when order execution fails

---