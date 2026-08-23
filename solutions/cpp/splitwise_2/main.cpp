// Single-file build (no header files) — merged from the multi-file project.
// Build & run:  g++ -std=c++17 main.cpp -o app && ./app
#include <algorithm>
#include <ctime>
#include <iomanip>
#include <iostream>
#include <map>
#include <numeric>
#include <string>
#include <vector>

using namespace std;

// ----- forward declarations -----
class Expense;
class User;
class SplitwiseSystem;

// ===== Expense.hpp =====
enum class ExpenseType {
    EQUAL,
    EXACT,
    PERCENT
};

class Expense {
private:
    string expenseId;
    string description;
    double totalAmount;
    string paidBy;
    vector<string> participants;
    map<string, double> shares;  // userId -> share amount
    ExpenseType type;
    time_t timestamp;

public:
    Expense(string expenseId, string description, double totalAmount,
           string paidBy, const vector<string>& participants,
           ExpenseType type);
    
    string getExpenseId() const;
    string getDescription() const;
    double getTotalAmount() const;
    string getPaidBy() const;
    const vector<string>& getParticipants() const;
    const map<string, double>& getShares() const;
    ExpenseType getType() const;
    time_t getTimestamp() const;
    
    void setShares(const map<string, double>& shares);
    void calculateEqualShares();
    void displayInfo() const;
};

// ===== User.hpp =====
class User {
private:
    string userId;
    string name;
    string email;
    map<string, double> balances;  // userId -> amount
    bool active;

public:
    User(string userId, string name, string email);
    
    string getUserId() const;
    string getName() const;
    string getEmail() const;
    bool isActive() const;
    double getBalanceWith(const string& userId) const;
    const map<string, double>& getBalances() const;
    
    void updateBalance(const string& userId, double amount);
    void setActive(bool status);
    void displayInfo() const;
    void displayBalances() const;
};

// ===== SplitwiseSystem.hpp =====
class SplitwiseSystem {
private:
    vector<User*> users;
    vector<Expense*> expenses;
    int userIdCounter;
    int expenseIdCounter;

public:
    SplitwiseSystem();
    ~SplitwiseSystem();
    
    // User management
    User* registerUser(const string& name, const string& email);
    void removeUser(const string& userId);
    
    // Expense management
    Expense* addExpense(const string& description, double amount,
                       const string& paidBy,
                       const vector<string>& participants,
                       ExpenseType type = ExpenseType::EQUAL);
    bool setExpenseShares(const string& expenseId,
                         const map<string, double>& shares);
    
    // Balance management
    void settleExpense(const string& expenseId);
    void showBalance(const string& userId) const;
    void showAllBalances() const;
    
    // Display functions
    void displayUsers() const;
    void displayExpenses() const;
    void displayUserExpenses(const string& userId) const;

private:
    User* findUser(const string& userId) const;
    Expense* findExpense(const string& expenseId) const;
    void updateBalances(Expense* expense);
    string generateUserId();
    string generateExpenseId();
};

// ===== Expense.cpp =====
Expense::Expense(string expenseId, string description, double totalAmount,
                string paidBy, const vector<string>& participants,
                ExpenseType type)
    : expenseId(expenseId), description(description), totalAmount(totalAmount),
      paidBy(paidBy), participants(participants), type(type) {
    timestamp = time(nullptr);
    if (type == ExpenseType::EQUAL) {
        calculateEqualShares();
    }
}

string Expense::getExpenseId() const { return expenseId; }
string Expense::getDescription() const { return description; }
double Expense::getTotalAmount() const { return totalAmount; }
string Expense::getPaidBy() const { return paidBy; }
const vector<string>& Expense::getParticipants() const { return participants; }
const map<string, double>& Expense::getShares() const { return shares; }
ExpenseType Expense::getType() const { return type; }
time_t Expense::getTimestamp() const { return timestamp; }

void Expense::setShares(const map<string, double>& shares) {
    this->shares = shares;
}

void Expense::calculateEqualShares() {
    double equalShare = totalAmount / participants.size();
    for (const auto& participant : participants) {
        shares[participant] = equalShare;
    }
}

void Expense::displayInfo() const {
    cout << "\nExpense Details:" << endl;
    cout << "ID: " << expenseId << endl;
    cout << "Description: " << description << endl;
    cout << "Amount: $" << fixed << setprecision(2) << totalAmount << endl;
    cout << "Paid by: " << paidBy << endl;
    cout << "Type: ";
    switch (type) {
        case ExpenseType::EQUAL: cout << "Equal"; break;
        case ExpenseType::EXACT: cout << "Exact"; break;
        case ExpenseType::PERCENT: cout << "Percent"; break;
    }
    cout << endl;
    
    cout << "Shares:" << endl;
    for (const auto& share : shares) {
        cout << share.first << ": $" << fixed << setprecision(2)
                  << share.second << endl;
    }
    
    cout << "Time: " << ctime(&timestamp);
} 

// ===== SplitwiseSystem.cpp =====
SplitwiseSystem::SplitwiseSystem() : userIdCounter(1), expenseIdCounter(1) {}

SplitwiseSystem::~SplitwiseSystem() {
    for (auto user : users) delete user;
    for (auto expense : expenses) delete expense;
}

User* SplitwiseSystem::registerUser(const string& name, const string& email) {
    string userId = generateUserId();
    User* user = new User(userId, name, email);
    users.push_back(user);
    return user;
}

void SplitwiseSystem::removeUser(const string& userId) {
    auto it = find_if(users.begin(), users.end(),
        [userId](User* user) { return user->getUserId() == userId; });
    
    if (it != users.end()) {
        delete *it;
        users.erase(it);
    }
}

Expense* SplitwiseSystem::addExpense(const string& description, double amount,
                                   const string& paidBy,
                                   const vector<string>& participants,
                                   ExpenseType type) {
    if (!findUser(paidBy)) return nullptr;
    
    string expenseId = generateExpenseId();
    Expense* expense = new Expense(expenseId, description, amount, paidBy, participants, type);
    expenses.push_back(expense);
    
    if (type == ExpenseType::EQUAL) {
        settleExpense(expenseId);
    }
    
    return expense;
}

bool SplitwiseSystem::setExpenseShares(const string& expenseId,
                                     const map<string, double>& shares) {
    Expense* expense = findExpense(expenseId);
    if (!expense) return false;
    
    // Validate total shares equals expense amount
    double totalShares = accumulate(shares.begin(), shares.end(), 0.0,
        [](double sum, const auto& pair) { return sum + pair.second; });
    
    if (abs(totalShares - expense->getTotalAmount()) > 0.01) return false;
    
    expense->setShares(shares);
    settleExpense(expenseId);
    return true;
}

void SplitwiseSystem::settleExpense(const string& expenseId) {
    Expense* expense = findExpense(expenseId);
    if (!expense) return;
    
    const string& paidBy = expense->getPaidBy();
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

void SplitwiseSystem::showBalance(const string& userId) const {
    User* user = findUser(userId);
    if (!user) return;
    
    user->displayBalances();
}

void SplitwiseSystem::showAllBalances() const {
    cout << "\nAll Balances:" << endl;
    for (const auto& user : users) {
        user->displayBalances();
    }
}

void SplitwiseSystem::displayUsers() const {
    cout << "\nRegistered Users:" << endl;
    for (const auto& user : users) {
        user->displayInfo();
        cout << "------------------------" << endl;
    }
}

void SplitwiseSystem::displayExpenses() const {
    cout << "\nAll Expenses:" << endl;
    for (const auto& expense : expenses) {
        expense->displayInfo();
        cout << "------------------------" << endl;
    }
}

void SplitwiseSystem::displayUserExpenses(const string& userId) const {
    User* user = findUser(userId);
    if (!user) return;
    
    cout << "\nExpenses for " << user->getName() << ":" << endl;
    for (const auto& expense : expenses) {
        if (expense->getPaidBy() == userId ||
            find(expense->getParticipants().begin(),
                     expense->getParticipants().end(),
                     userId) != expense->getParticipants().end()) {
            expense->displayInfo();
            cout << "------------------------" << endl;
        }
    }
}

User* SplitwiseSystem::findUser(const string& userId) const {
    auto it = find_if(users.begin(), users.end(),
        [userId](User* user) { return user->getUserId() == userId; });
    return it != users.end() ? *it : nullptr;
}

Expense* SplitwiseSystem::findExpense(const string& expenseId) const {
    auto it = find_if(expenses.begin(), expenses.end(),
        [expenseId](Expense* expense) { return expense->getExpenseId() == expenseId; });
    return it != expenses.end() ? *it : nullptr;
}

string SplitwiseSystem::generateUserId() {
    return "U" + to_string(userIdCounter++);
}

string SplitwiseSystem::generateExpenseId() {
    return "E" + to_string(expenseIdCounter++);
} 

// ===== User.cpp =====
User::User(string userId, string name, string email)
    : userId(userId), name(name), email(email), active(true) {}

string User::getUserId() const { return userId; }
string User::getName() const { return name; }
string User::getEmail() const { return email; }
bool User::isActive() const { return active; }
double User::getBalanceWith(const string& userId) const {
    auto it = balances.find(userId);
    return it != balances.end() ? it->second : 0.0;
}
const map<string, double>& User::getBalances() const { return balances; }

void User::updateBalance(const string& userId, double amount) {
    balances[userId] += amount;
}

void User::setActive(bool status) {
    active = status;
}

void User::displayInfo() const {
    cout << "User: " << name << " (ID: " << userId << ")" << endl;
    cout << "Email: " << email << endl;
    cout << "Status: " << (active ? "Active" : "Inactive") << endl;
}

void User::displayBalances() const {
    cout << "\nBalances for " << name << ":" << endl;
    for (const auto& balance : balances) {
        cout << "With " << balance.first << ": $"
                  << fixed << setprecision(2) << balance.second << endl;
    }
} 

// ===== SplitwiseDemo.cpp =====
int main() {
    SplitwiseSystem splitwise;
    
    // Register users
    User* user1 = splitwise.registerUser("John", "john@email.com");
    User* user2 = splitwise.registerUser("Alice", "alice@email.com");
    User* user3 = splitwise.registerUser("Bob", "bob@email.com");
    
    cout << "Initial users:" << endl;
    splitwise.displayUsers();
    
    // Add expenses
    vector<string> participants = {
        user1->getUserId(), user2->getUserId(), user3->getUserId()
    };
    
    // Equal split expense
    Expense* dinner = splitwise.addExpense("Dinner", 300.0, user1->getUserId(), participants);
    
    // Custom split expense
    vector<string> movieParticipants = {
        user1->getUserId(), user2->getUserId()
    };
    Expense* movie = splitwise.addExpense("Movie", 100.0, user2->getUserId(),
                                        movieParticipants, ExpenseType::EXACT);
    
    map<string, double> movieShares = {
        {user1->getUserId(), 60.0},
        {user2->getUserId(), 40.0}
    };
    splitwise.setExpenseShares(movie->getExpenseId(), movieShares);
    
    // Display expenses
    cout << "\nAll expenses:" << endl;
    splitwise.displayExpenses();
    
    // Show balances
    cout << "\nBalances after expenses:" << endl;
    splitwise.showAllBalances();
    
    // Show individual expenses
    cout << "\nJohn's expenses:" << endl;
    splitwise.displayUserExpenses(user1->getUserId());
    
    return 0;
} 

