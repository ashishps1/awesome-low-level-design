#ifndef SPLITWISE_SYSTEM_HPP
#define SPLITWISE_SYSTEM_HPP

#include <vector>
#include <string>
#include "User.hpp"
#include "Expense.hpp"

class SplitwiseSystem {
private:
    std::vector<User*> users;
    std::vector<Expense*> expenses;
    int userIdCounter;
    int expenseIdCounter;

public:
    SplitwiseSystem();
    ~SplitwiseSystem();
    
    // User management
    User* registerUser(const std::string& name, const std::string& email);
    void removeUser(const std::string& userId);
    
    // Expense management
    Expense* addExpense(const std::string& description, double amount,
                       const std::string& paidBy,
                       const std::vector<std::string>& participants,
                       ExpenseType type = ExpenseType::EQUAL);
    bool setExpenseShares(const std::string& expenseId,
                         const std::map<std::string, double>& shares);
    
    // Balance management
    void settleExpense(const std::string& expenseId);
    void showBalance(const std::string& userId) const;
    void showAllBalances() const;
    
    // Display functions
    void displayUsers() const;
    void displayExpenses() const;
    void displayUserExpenses(const std::string& userId) const;

private:
    User* findUser(const std::string& userId) const;
    Expense* findExpense(const std::string& expenseId) const;
    void updateBalances(Expense* expense);
    std::string generateUserId();
    std::string generateExpenseId();
};

#endif 