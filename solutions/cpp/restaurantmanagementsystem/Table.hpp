#ifndef TABLE_HPP
#define TABLE_HPP

enum class TableStatus {
    AVAILABLE,
    OCCUPIED,
    RESERVED
};

class Table {
private:
    int tableNumber;
    int capacity;
    TableStatus status;

public:
    Table(int tableNumber, int capacity);
    
    int getTableNumber() const;
    int getCapacity() const;
    TableStatus getStatus() const;
    
    void setStatus(TableStatus status);
    void displayInfo() const;
};

#endif 