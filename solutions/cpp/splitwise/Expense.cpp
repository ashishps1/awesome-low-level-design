#include "Expense.hpp"
#include <iostream>
#include <iomanip>

Expense::Expense(std::string expenseId, std::string description, double totalAmount,
                std::string paidBy, const std::vector<std::string>& participants,
                ExpenseType type)
    : expenseId(expenseId), description(description), totalAmount(totalAmount),
      paidBy(paidBy), participants(participants), type(type) {
    timestamp = std::time(nullptr);
    if (type == ExpenseType::EQUAL) {
        calculateEqualShares();
    }
}

std::string Expense::getExpenseId() const { return expenseId; }
std::string Expense::getDescription() const { return description; }
double Expense::getTotalAmount() const { return totalAmount; }
std::string Expense::getPaidBy() const { return paidBy; }
const std::vector<std::string>& Expense::getParticipants() const { return participants; }
const std::map<std::string, double>& Expense::getShares() const { return shares; }
ExpenseType Expense::getType() const { return type; }
std::time_t Expense::getTimestamp() const { return timestamp; }

void Expense::setShares(const std::map<std::string, double>& shares) {
    this->shares = shares;
}

void Expense::calculateEqualShares() {
    double equalShare = totalAmount / participants.size();
    for (const auto& participant : participants) {
        shares[participant] = equalShare;
    }
}

void Expense::displayInfo() const {
    std::cout << "\nExpense Details:" << std::endl;
    std::cout << "ID: " << expenseId << std::endl;
    std::cout << "Description: " << description << std::endl;
    std::cout << "Amount: $" << std::fixed << std::setprecision(2) << totalAmount << std::endl;
    std::cout << "Paid by: " << paidBy << std::endl;
    std::cout << "Type: ";
    switch (type) {
        case ExpenseType::EQUAL: std::cout << "Equal"; break;
        case ExpenseType::EXACT: std::cout << "Exact"; break;
        case ExpenseType::PERCENT: std::cout << "Percent"; break;
    }
    std::cout << std::endl;
    
    std::cout << "Shares:" << std::endl;
    for (const auto& share : shares) {
        std::cout << share.first << ": $" << std::fixed << std::setprecision(2)
                  << share.second << std::endl;
    }
    
    std::cout << "Time: " << std::ctime(&timestamp);
} 