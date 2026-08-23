// Single-file build (no header files) — merged from the multi-file project.
// Build & run:  g++ -std=c++17 main.cpp -o app && ./app
#include <iomanip>
#include <iostream>
#include <limits>
#include <string>
#include <vector>

using namespace std;

// ----- forward declarations -----
class Account;
class ATM;

// ===== Account.hpp =====
class Account {
private:
    string accountNumber;
    string pin;
    double balance;

public:
    Account(string accountNumber, string pin, double initialBalance = 0.0);
    
    string getAccountNumber() const;
    bool validatePin(const string& inputPin) const;
    double getBalance() const;
    
    bool deposit(double amount);
    bool withdraw(double amount);
    void displayBalance() const;
};

// ===== ATM.hpp =====
class ATM {
private:
    vector<Account*> accounts;
    Account* currentAccount;
    bool isAuthenticated;

public:
    ATM();
    ~ATM();
    
    void addAccount(Account* account);
    bool authenticate(const string& accountNumber, const string& pin);
    void logout();
    
    bool deposit(double amount);
    bool withdraw(double amount);
    void checkBalance() const;
    
    void displayMenu() const;
    void start();
};

// ===== ATM.cpp =====
ATM::ATM() : currentAccount(nullptr), isAuthenticated(false) {}

ATM::~ATM() {
    for (auto account : accounts) {
        delete account;
    }
}

void ATM::addAccount(Account* account) {
    accounts.push_back(account);
}

bool ATM::authenticate(const string& accountNumber, const string& pin) {
    for (auto account : accounts) {
        if (account->getAccountNumber() == accountNumber && account->validatePin(pin)) {
            currentAccount = account;
            isAuthenticated = true;
            return true;
        }
    }
    return false;
}

void ATM::logout() {
    currentAccount = nullptr;
    isAuthenticated = false;
}

bool ATM::deposit(double amount) {
    if (!isAuthenticated || !currentAccount) return false;
    return currentAccount->deposit(amount);
}

bool ATM::withdraw(double amount) {
    if (!isAuthenticated || !currentAccount) return false;
    return currentAccount->withdraw(amount);
}

void ATM::checkBalance() const {
    if (!isAuthenticated || !currentAccount) return;
    currentAccount->displayBalance();
}

void ATM::displayMenu() const {
    cout << "\nATM Menu:" << endl;
    cout << "1. Check Balance" << endl;
    cout << "2. Deposit" << endl;
    cout << "3. Withdraw" << endl;
    cout << "4. Logout" << endl;
    cout << "5. Exit" << endl;
    cout << "Enter your choice: ";
}

void ATM::start() {
    string accountNumber, pin;
    int choice;
    double amount;

    while (true) {
        if (!isAuthenticated) {
            cout << "\nWelcome to ATM" << endl;
            cout << "Enter account number: ";
            cin >> accountNumber;
            cout << "Enter PIN: ";
            cin >> pin;

            if (!authenticate(accountNumber, pin)) {
                cout << "Invalid account number or PIN" << endl;
                continue;
            }
            cout << "Authentication successful!" << endl;
        }

        displayMenu();
        cin >> choice;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        switch (choice) {
            case 1:
                checkBalance();
                break;

            case 2:
                cout << "Enter amount to deposit: $";
                cin >> amount;
                if (deposit(amount)) {
                    cout << "Deposit successful" << endl;
                    checkBalance();
                } else {
                    cout << "Invalid amount" << endl;
                }
                break;

            case 3:
                cout << "Enter amount to withdraw: $";
                cin >> amount;
                if (withdraw(amount)) {
                    cout << "Withdrawal successful" << endl;
                    checkBalance();
                } else {
                    cout << "Invalid amount or insufficient funds" << endl;
                }
                break;

            case 4:
                logout();
                cout << "Logged out successfully" << endl;
                break;

            case 5:
                cout << "Thank you for using ATM. Goodbye!" << endl;
                return;

            default:
                cout << "Invalid choice" << endl;
        }
    }
} 

// ===== Account.cpp =====
Account::Account(string accountNumber, string pin, double initialBalance)
    : accountNumber(accountNumber), pin(pin), balance(initialBalance) {}

string Account::getAccountNumber() const {
    return accountNumber;
}

bool Account::validatePin(const string& inputPin) const {
    return pin == inputPin;
}

double Account::getBalance() const {
    return balance;
}

bool Account::deposit(double amount) {
    if (amount <= 0) return false;
    
    balance += amount;
    return true;
}

bool Account::withdraw(double amount) {
    if (amount <= 0 || amount > balance) return false;
    
    balance -= amount;
    return true;
}

void Account::displayBalance() const {
    cout << "Current balance: $" << fixed << setprecision(2) << balance << endl;
} 

// ===== ATMDemo.cpp =====
int main() {
    ATM atm;
    
    // Create some test accounts
    Account* account1 = new Account("1234", "5678", 1000.0);
    Account* account2 = new Account("4321", "8765", 2000.0);
    
    // Add accounts to ATM
    atm.addAccount(account1);
    atm.addAccount(account2);
    
    // Start the ATM
    atm.start();
    
    return 0;
} 

