package onlinestockbrokeragesystem.entities;

import onlinestockbrokeragesystem.exceptions.InsufficientFundsException;
import onlinestockbrokeragesystem.exceptions.InsufficientStockException;

import java.util.Map;
import java.util.concurrent.ConcurrentHashMap;

public class Account {
    private double balance;
    private final Map<String, Integer> portfolio; // Stock symbol -> quantity

    public Account(double initialCash) {
        this.balance = initialCash;
        this.portfolio = new ConcurrentHashMap<>();
    }

    public synchronized void debit(double amount) {
        if (balance < amount) {
            throw new InsufficientFundsException("Insufficient funds to debit " + amount);
        }
        balance -= amount;
    }

    public synchronized void credit(double amount) {
        balance += amount;
    }

    public synchronized void addStock(String symbol, int quantity) {
        portfolio.put(symbol, portfolio.getOrDefault(symbol, 0) + quantity);
    }

    public synchronized void removeStock(String symbol, int quantity) {
        int currentQuantity = portfolio.getOrDefault(symbol, 0);
        if (currentQuantity < quantity) {
            throw new InsufficientStockException("Not enough " + symbol + " stock to sell.");
        }
        portfolio.put(symbol, currentQuantity - quantity);
    }

    public double getBalance() { return balance; }
    public Map<String, Integer> getPortfolio() { return Map.copyOf(portfolio); }
    public int getStockQuantity(String symbol) { return portfolio.getOrDefault(symbol, 0); }
}
