#include "Table.hpp"
#include <iostream>

Table::Table(int tableNumber, int capacity)
    : tableNumber(tableNumber), capacity(capacity), status(TableStatus::AVAILABLE) {}

int Table::getTableNumber() const { return tableNumber; }
int Table::getCapacity() const { return capacity; }
TableStatus Table::getStatus() const { return status; }

void Table::setStatus(TableStatus status) {
    this->status = status;
}

void Table::displayInfo() const {
    std::cout << "Table " << tableNumber << std::endl;
    std::cout << "Capacity: " << capacity << " persons" << std::endl;
    std::cout << "Status: ";
    switch (status) {
        case TableStatus::AVAILABLE: std::cout << "Available"; break;
        case TableStatus::OCCUPIED: std::cout << "Occupied"; break;
        case TableStatus::RESERVED: std::cout << "Reserved"; break;
    }
    std::cout << std::endl;
} 