# Designing an Online Stock Brokerage System

In this article, we'll examine the object-oriented design and implementation of an Online Stock Brokerage System using Java. 

This system simulates key functionalities of stock trading platforms, enabling users to engage in buying and selling stocks, manage their portfolios, and stay updated with stock prices.

## System Requirements

The Stock Brokerage System needs to:

1. **User Account Management:** Manage user registrations and profiles.
2. **Stock Trading:** Enable stock buying and selling.
3. **Portfolio Management:** Allow users to manage their stock holdings.
4. **Stock Price Feed:** Provide real-time stock price updates.

## Core Use Cases

1. **Registering and Managing User Accounts**
2. **Buying and Selling Stocks**
3. **Managing Portfolio**
4. **Viewing Stock Prices**

## Key Classes:
- `StockBrokerageSystem`: Manages the entire system.
- `User`: Represents a system user.
- `Stock`: Represents a stock in the market.
- `Portfolio`: Manages a user's stock holdings.
- `Trade`: Handles stock trade transactions.

## Java Implementation

### User Class
Manages user account information.

```java
import java.util.UUID;

public class User {
    private String userId;
    private String name;
    private Portfolio portfolio;

    public User(String name) {
        this.userId = UUID.randomUUID().toString();
        this.name = name;
        this.portfolio = new Portfolio();
    }

    public void executeTrade(Stock stock, int quantity, TradeType tradeType, StockBrokerageSystem system) {
        system.executeTrade(new Trade(this, stock, quantity, tradeType));
    }

    // Getters and setters...
}
```
### Stock Class
Represents a stock in the market.
```java
public class Stock {
    private String symbol;
    private double price;

    public Stock(String symbol, double price) {
        this.symbol = symbol;
        this.price = price;
    }

    public void updatePrice(double newPrice) {
        this.price = newPrice;
    }

    // Getters and setters...
}
```
### Portfolio Class
Manages a user's stock holdings.
```java
import java.util.HashMap;
import java.util.Map;

public class Portfolio {
    private Map<Stock, Integer> holdings;

    public Portfolio() {
        this.holdings = new HashMap<>();
    }

    public void addStock(Stock stock, int quantity) {
        holdings.put(stock, holdings.getOrDefault(stock, 0) + quantity);
    }

    public void removeStock(Stock stock, int quantity) {
        int currentQuantity = holdings.getOrDefault(stock, 0);
        if (currentQuantity >= quantity) {
            holdings.put(stock, currentQuantity - quantity);
        }
    }

    // Getters and setters...
}
```
### Trade Class
Represents a stock trade transaction.
```java
public class Trade {
    private User user;
    private Stock stock;
    private int quantity;
    private TradeType tradeType;

    public Trade(User user, Stock stock, int quantity, TradeType tradeType) {
        this.user = user;
        this.stock = stock;
        this.quantity = quantity;
        this.tradeType = tradeType;
    }

    // Getters and setters...
}

enum TradeType {
    BUY, SELL
}
```
### StockBrokerageSystem Class
Main class managing the brokerage system.
```java
import java.util.ArrayList;
import java.util.List;

public class StockBrokerageSystem {
    private List<User> users;
    private List<Stock> stocks;

    public StockBrokerageSystem() {
        this.users = new ArrayList<>();
        this.stocks = new ArrayList<>();
    }

    public void executeTrade(Trade trade) {
        if (trade.getTradeType() == TradeType.BUY) {
            processBuyTrade(trade);
        } else if (trade.getTradeType() == TradeType.SELL) {
            processSellTrade(trade);
        }
    }

    private void processBuyTrade(Trade trade) {
        // Logic to process a buy trade
        trade.getUser().getPortfolio().addStock(trade.getStock(), trade.getQuantity());
    }

    private void processSellTrade(Trade trade) {
        // Logic to process a sell trade
        trade.getUser().getPortfolio().removeStock(trade.getStock(), trade.getQuantity());
    }

    // Other necessary methods...
}
```