#include "SplitwiseSystem.hpp"
#include <iostream>

int main() {
    SplitwiseSystem splitwise;
    
    // Register users
    User* user1 = splitwise.registerUser("John", "john@email.com");
    User* user2 = splitwise.registerUser("Alice", "alice@email.com");
    User* user3 = splitwise.registerUser("Bob", "bob@email.com");
    
    std::cout << "Initial users:" << std::endl;
    splitwise.displayUsers();
    
    // Add expenses
    std::vector<std::string> participants = {
        user1->getUserId(), user2->getUserId(), user3->getUserId()
    };
    
    // Equal split expense
    Expense* dinner = splitwise.addExpense("Dinner", 300.0, user1->getUserId(), participants);
    
    // Custom split expense
    std::vector<std::string> movieParticipants = {
        user1->getUserId(), user2->getUserId()
    };
    Expense* movie = splitwise.addExpense("Movie", 100.0, user2->getUserId(),
                                        movieParticipants, ExpenseType::EXACT);
    
    std::map<std::string, double> movieShares = {
        {user1->getUserId(), 60.0},
        {user2->getUserId(), 40.0}
    };
    splitwise.setExpenseShares(movie->getExpenseId(), movieShares);
    
    // Display expenses
    std::cout << "\nAll expenses:" << std::endl;
    splitwise.displayExpenses();
    
    // Show balances
    std::cout << "\nBalances after expenses:" << std::endl;
    splitwise.showAllBalances();
    
    // Show individual expenses
    std::cout << "\nJohn's expenses:" << std::endl;
    splitwise.displayUserExpenses(user1->getUserId());
    
    return 0;
} 