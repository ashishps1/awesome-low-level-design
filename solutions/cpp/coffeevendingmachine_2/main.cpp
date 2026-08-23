// Single-file build (no header files) — merged from the multi-file project.
// Build & run:  g++ -std=c++17 main.cpp -o app && ./app
#include <iomanip>
#include <iostream>
#include <map>
#include <string>
#include <vector>

using namespace std;

// ----- forward declarations -----
class Coffee;
class Inventory;
class CoffeeVendingMachine;

// ===== CoffeeType.hpp =====
enum class CoffeeType {
    ESPRESSO,
    LATTE,
    CAPPUCCINO,
    AMERICANO
};

// ===== Coffee.hpp =====
class Coffee {
private:
    CoffeeType type;
    double price;
    string description;

public:
    Coffee(CoffeeType type, double price, string description);
    
    CoffeeType getType() const;
    double getPrice() const;
    string getDescription() const;
};

// ===== Inventory.hpp =====
class Inventory {
private:
    map<CoffeeType, int> items;

public:
    Inventory();
    
    void addItem(CoffeeType type, int quantity);
    bool hasItem(CoffeeType type);
    void deductItem(CoffeeType type);
    int getQuantity(CoffeeType type) const;
    void display() const;
};

// ===== CoffeeVendingMachine.hpp =====
class CoffeeVendingMachine {
private:
    vector<Coffee> coffeeMenu;
    Inventory inventory;
    double moneyCollected;

public:
    CoffeeVendingMachine();
    
    void initializeMenu();
    void displayMenu() const;
    bool selectCoffee(CoffeeType type, double payment);
    void refillInventory(CoffeeType type, int quantity);
    double getMoneyCollected() const;
    void displayInventory() const;
    
private:
    Coffee* findCoffee(CoffeeType type);
};

// ===== Coffee.cpp =====
Coffee::Coffee(CoffeeType type, double price, string description)
    : type(type), price(price), description(description) {}

CoffeeType Coffee::getType() const { return type; }
double Coffee::getPrice() const { return price; }
string Coffee::getDescription() const { return description; } 

// ===== CoffeeVendingMachine.cpp =====
CoffeeVendingMachine::CoffeeVendingMachine() : moneyCollected(0.0) {
    initializeMenu();
}

void CoffeeVendingMachine::initializeMenu() {
    coffeeMenu.push_back(Coffee(CoffeeType::ESPRESSO, 2.50, "Strong black coffee"));
    coffeeMenu.push_back(Coffee(CoffeeType::LATTE, 3.50, "Coffee with steamed milk"));
    coffeeMenu.push_back(Coffee(CoffeeType::CAPPUCCINO, 3.00, "Coffee topped with foamy milk"));
    coffeeMenu.push_back(Coffee(CoffeeType::AMERICANO, 2.00, "Diluted espresso"));
}

void CoffeeVendingMachine::displayMenu() const {
    cout << "\nCoffee Menu:" << endl;
    cout << fixed << setprecision(2);
    
    for (const auto& coffee : coffeeMenu) {
        cout << "Type: ";
        switch (coffee.getType()) {
            case CoffeeType::ESPRESSO: cout << "Espresso"; break;
            case CoffeeType::LATTE: cout << "Latte"; break;
            case CoffeeType::CAPPUCCINO: cout << "Cappuccino"; break;
            case CoffeeType::AMERICANO: cout << "Americano"; break;
        }
        cout << " - $" << coffee.getPrice() << endl;
        cout << "Description: " << coffee.getDescription() << endl;
        cout << "Available: " << inventory.getQuantity(coffee.getType()) << endl;
        cout << "------------------------" << endl;
    }
}

bool CoffeeVendingMachine::selectCoffee(CoffeeType type, double payment) {
    Coffee* coffee = findCoffee(type);
    if (!coffee) {
        cout << "Invalid coffee selection!" << endl;
        return false;
    }
    
    if (!inventory.hasItem(type)) {
        cout << "Sorry, this coffee is out of stock!" << endl;
        return false;
    }
    
    if (payment < coffee->getPrice()) {
        cout << "Insufficient payment! Price is $" << coffee->getPrice() << endl;
        return false;
    }
    
    inventory.deductItem(type);
    moneyCollected += coffee->getPrice();
    double change = payment - coffee->getPrice();
    
    cout << "\nDispensing " << coffee->getDescription() << endl;
    if (change > 0) {
        cout << "Change: $" << fixed << setprecision(2) << change << endl;
    }
    
    return true;
}

void CoffeeVendingMachine::refillInventory(CoffeeType type, int quantity) {
    inventory.addItem(type, quantity);
    cout << "Inventory refilled successfully!" << endl;
}

double CoffeeVendingMachine::getMoneyCollected() const {
    return moneyCollected;
}

void CoffeeVendingMachine::displayInventory() const {
    inventory.display();
}

Coffee* CoffeeVendingMachine::findCoffee(CoffeeType type) {
    for (auto& coffee : coffeeMenu) {
        if (coffee.getType() == type) {
            return &coffee;
        }
    }
    return nullptr;
} 

// ===== Inventory.cpp =====
Inventory::Inventory() {
    // Initialize inventory with zero quantity for all coffee types
    items[CoffeeType::ESPRESSO] = 0;
    items[CoffeeType::LATTE] = 0;
    items[CoffeeType::CAPPUCCINO] = 0;
    items[CoffeeType::AMERICANO] = 0;
}

void Inventory::addItem(CoffeeType type, int quantity) {
    items[type] += quantity;
}

bool Inventory::hasItem(CoffeeType type) {
    return items[type] > 0;
}

void Inventory::deductItem(CoffeeType type) {
    if (items[type] > 0) {
        items[type]--;
    }
}

int Inventory::getQuantity(CoffeeType type) const {
    auto it = items.find(type);
    return it != items.end() ? it->second : 0;
}

void Inventory::display() const {
    cout << "\nCurrent Inventory:" << endl;
    cout << "Espresso: " << items.at(CoffeeType::ESPRESSO) << endl;
    cout << "Latte: " << items.at(CoffeeType::LATTE) << endl;
    cout << "Cappuccino: " << items.at(CoffeeType::CAPPUCCINO) << endl;
    cout << "Americano: " << items.at(CoffeeType::AMERICANO) << endl;
} 

// ===== CoffeeVendingMachineDemo.cpp =====
int main() {
    CoffeeVendingMachine machine;
    
    // Refill inventory
    machine.refillInventory(CoffeeType::ESPRESSO, 5);
    machine.refillInventory(CoffeeType::LATTE, 5);
    machine.refillInventory(CoffeeType::CAPPUCCINO, 5);
    machine.refillInventory(CoffeeType::AMERICANO, 5);
    
    // Display menu and inventory
    machine.displayMenu();
    machine.displayInventory();
    
    // Make some purchases
    cout << "\nMaking purchases:" << endl;
    
    if (machine.selectCoffee(CoffeeType::ESPRESSO, 3.00)) {
        cout << "Espresso purchased successfully!" << endl;
    }
    
    if (machine.selectCoffee(CoffeeType::LATTE, 3.50)) {
        cout << "Latte purchased successfully!" << endl;
    }
    
    // Try insufficient payment
    if (!machine.selectCoffee(CoffeeType::CAPPUCCINO, 2.00)) {
        cout << "Cappuccino purchase failed - insufficient payment" << endl;
    }
    
    // Display updated inventory and money collected
    machine.displayInventory();
    cout << "\nTotal money collected: $" << machine.getMoneyCollected() << endl;
    
    return 0;
} 

