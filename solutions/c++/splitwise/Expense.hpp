#ifndef EXPENSE_HPP
#define EXPENSE_HPP

#include <string>
#include <vector>
#include <map>
#include <ctime>

enum class ExpenseType {
    EQUAL,
    EXACT,
    PERCENT
};

class Expense {
private:
    std::string expenseId;
    std::string description;
    double totalAmount;
    std::string paidBy;
    std::vector<std::string> participants;
    std::map<std::string, double> shares;  // userId -> share amount
    ExpenseType type;
    std::time_t timestamp;

public:
    Expense(std::string expenseId, std::string description, double totalAmount,
           std::string paidBy, const std::vector<std::string>& participants,
           ExpenseType type);
    
    std::string getExpenseId() const;
    std::string getDescription() const;
    double getTotalAmount() const;
    std::string getPaidBy() const;
    const std::vector<std::string>& getParticipants() const;
    const std::map<std::string, double>& getShares() const;
    ExpenseType getType() const;
    std::time_t getTimestamp() const;
    
    void setShares(const std::map<std::string, double>& shares);
    void calculateEqualShares();
    void displayInfo() const;
};

#endif 