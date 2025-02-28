#include "ATM.hpp"
#include <iostream>
#include <limits>

ATM::ATM() : currentAccount(nullptr), isAuthenticated(false) {}

ATM::~ATM() {
    for (auto account : accounts) {
        delete account;
    }
}

void ATM::addAccount(Account* account) {
    accounts.push_back(account);
}

bool ATM::authenticate(const std::string& accountNumber, const std::string& pin) {
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
    std::cout << "\nATM Menu:" << std::endl;
    std::cout << "1. Check Balance" << std::endl;
    std::cout << "2. Deposit" << std::endl;
    std::cout << "3. Withdraw" << std::endl;
    std::cout << "4. Logout" << std::endl;
    std::cout << "5. Exit" << std::endl;
    std::cout << "Enter your choice: ";
}

void ATM::start() {
    std::string accountNumber, pin;
    int choice;
    double amount;

    while (true) {
        if (!isAuthenticated) {
            std::cout << "\nWelcome to ATM" << std::endl;
            std::cout << "Enter account number: ";
            std::cin >> accountNumber;
            std::cout << "Enter PIN: ";
            std::cin >> pin;

            if (!authenticate(accountNumber, pin)) {
                std::cout << "Invalid account number or PIN" << std::endl;
                continue;
            }
            std::cout << "Authentication successful!" << std::endl;
        }

        displayMenu();
        std::cin >> choice;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        switch (choice) {
            case 1:
                checkBalance();
                break;

            case 2:
                std::cout << "Enter amount to deposit: $";
                std::cin >> amount;
                if (deposit(amount)) {
                    std::cout << "Deposit successful" << std::endl;
                    checkBalance();
                } else {
                    std::cout << "Invalid amount" << std::endl;
                }
                break;

            case 3:
                std::cout << "Enter amount to withdraw: $";
                std::cin >> amount;
                if (withdraw(amount)) {
                    std::cout << "Withdrawal successful" << std::endl;
                    checkBalance();
                } else {
                    std::cout << "Invalid amount or insufficient funds" << std::endl;
                }
                break;

            case 4:
                logout();
                std::cout << "Logged out successfully" << std::endl;
                break;

            case 5:
                std::cout << "Thank you for using ATM. Goodbye!" << std::endl;
                return;

            default:
                std::cout << "Invalid choice" << std::endl;
        }
    }
} 