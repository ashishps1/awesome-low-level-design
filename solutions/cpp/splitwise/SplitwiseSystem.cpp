#include "SplitwiseSystem.hpp"
#include <iostream>
#include <algorithm>
#include <numeric>

SplitwiseSystem::SplitwiseSystem() : userIdCounter(1), expenseIdCounter(1) {}

SplitwiseSystem::~SplitwiseSystem() {
    for (auto user : users) delete user;
    for (auto expense : expenses) delete expense;
}

User* SplitwiseSystem::registerUser(const std::string& name, const std::string& email) {
    std::string userId = generateUserId();
    User* user = new User(userId, name, email);
    users.push_back(user);
    return user;
}

void SplitwiseSystem::removeUser(const std::string& userId) {
    auto it = std::find_if(users.begin(), users.end(),
        [userId](User* user) { return user->getUserId() == userId; });
    
    if (it != users.end()) {
        delete *it;
        users.erase(it);
    }
}

Expense* SplitwiseSystem::addExpense(const std::string& description, double amount,
                                   const std::string& paidBy,
                                   const std::vector<std::string>& participants,
                                   ExpenseType type) {
    if (!findUser(paidBy)) return nullptr;
    
    std::string expenseId = generateExpenseId();
    Expense* expense = new Expense(expenseId, description, amount, paidBy, participants, type);
    expenses.push_back(expense);
    
    if (type == ExpenseType::EQUAL) {
        settleExpense(expenseId);
    }
    
    return expense;
}

bool SplitwiseSystem::setExpenseShares(const std::string& expenseId,
                                     const std::map<std::string, double>& shares) {
    Expense* expense = findExpense(expenseId);
    if (!expense) return false;
    
    // Validate total shares equals expense amount
    double totalShares = std::accumulate(shares.begin(), shares.end(), 0.0,
        [](double sum, const auto& pair) { return sum + pair.second; });
    
    if (std::abs(totalShares - expense->getTotalAmount()) > 0.01) return false;
    
    expense->setShares(shares);
    settleExpense(expenseId);
    return true;
}

void SplitwiseSystem::settleExpense(const std::string& expenseId) {
    Expense* expense = findExpense(expenseId);
    if (!expense) return;
    
    const std::string& paidBy = expense->getPaidBy();
    const auto& shares = expense->getShares();
    
    for (const auto& share : shares) {
        if (share.first != paidBy) {
            // Update balances for both users
            User* payer = findUser(paidBy);
            User* participant = findUser(share.first);
            
            if (payer && participant) {
                payer->updateBalance(share.first, share.second);
                participant->updateBalance(paidBy, -share.second);
            }
        }
    }
}

void SplitwiseSystem::showBalance(const std::string& userId) const {
    User* user = findUser(userId);
    if (!user) return;
    
    user->displayBalances();
}

void SplitwiseSystem::showAllBalances() const {
    std::cout << "\nAll Balances:" << std::endl;
    for (const auto& user : users) {
        user->displayBalances();
    }
}

void SplitwiseSystem::displayUsers() const {
    std::cout << "\nRegistered Users:" << std::endl;
    for (const auto& user : users) {
        user->displayInfo();
        std::cout << "------------------------" << std::endl;
    }
}

void SplitwiseSystem::displayExpenses() const {
    std::cout << "\nAll Expenses:" << std::endl;
    for (const auto& expense : expenses) {
        expense->displayInfo();
        std::cout << "------------------------" << std::endl;
    }
}

void SplitwiseSystem::displayUserExpenses(const std::string& userId) const {
    User* user = findUser(userId);
    if (!user) return;
    
    std::cout << "\nExpenses for " << user->getName() << ":" << std::endl;
    for (const auto& expense : expenses) {
        if (expense->getPaidBy() == userId ||
            std::find(expense->getParticipants().begin(),
                     expense->getParticipants().end(),
                     userId) != expense->getParticipants().end()) {
            expense->displayInfo();
            std::cout << "------------------------" << std::endl;
        }
    }
}

User* SplitwiseSystem::findUser(const std::string& userId) const {
    auto it = std::find_if(users.begin(), users.end(),
        [userId](User* user) { return user->getUserId() == userId; });
    return it != users.end() ? *it : nullptr;
}

Expense* SplitwiseSystem::findExpense(const std::string& expenseId) const {
    auto it = std::find_if(expenses.begin(), expenses.end(),
        [expenseId](Expense* expense) { return expense->getExpenseId() == expenseId; });
    return it != expenses.end() ? *it : nullptr;
}

std::string SplitwiseSystem::generateUserId() {
    return "U" + std::to_string(userIdCounter++);
}

std::string SplitwiseSystem::generateExpenseId() {
    return "E" + std::to_string(expenseIdCounter++);
} 