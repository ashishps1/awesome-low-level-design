# Interfaces in C++

## Introduction

In Object-Oriented Programming (OOP), an **interface** is a crucial concept that defines a contract for classes to follow. It allows multiple classes to share a common structure while enforcing certain behaviors. While C++ does not have explicit support for interfaces like Java, it achieves the same functionality using **pure virtual functions** in abstract classes.

## What is an Interface?

An **interface** is a collection of method definitions that a class must implement. It defines a contract that implementing classes must adhere to.

### **Key Characteristics of Interfaces in C++**
- Uses **abstract classes with pure virtual functions** to define interfaces.
- Defines methods without implementation that must be overridden.
- Supports **multiple inheritance**, unlike normal classes.
- Improves **code flexibility and maintainability**.

---

## **Defining and Implementing an Interface in C++**

### **Step 1: Define an Interface using an Abstract Class**
To define an interface, we use a class with at least one **pure virtual function**.

```cpp
#include <iostream>
using namespace std;

// Defining an interface
class Vehicle {
public:
    virtual void start() = 0; // Pure virtual function
    virtual void stop() = 0;  // Pure virtual function
};
```

### **Step 2: Implement the Interface**
A class implements an interface by inheriting from it and providing concrete implementations of the pure virtual functions.

```cpp
// Implementing the Vehicle interface in a Car class
class Car : public Vehicle {
public:
    void start() override {
        cout << "Car is starting..." << endl;
    }
    
    void stop() override {
        cout << "Car is stopping..." << endl;
    }
};
```

### **Step 3: Using the Implemented Class**
Now, let's create objects and call the methods.

```cpp
int main() {
    Vehicle* myCar = new Car(); // Polymorphism: Interface reference
    myCar->start();
    myCar->stop();
    
    delete myCar; // Clean up memory
    return 0;
}
```

### **Output:**
```
Car is starting...
Car is stopping...
```

---

## **Multiple Inheritance with Interfaces**

Unlike normal classes, C++ **supports multiple inheritance** with interfaces.

```cpp
// First interface
class Flyable {
public:
    virtual void fly() = 0;
};

// Second interface
class Drivable {
public:
    virtual void drive() = 0;
};

// Implementing multiple interfaces
class FlyingCar : public Flyable, public Drivable {
public:
    void fly() override {
        cout << "FlyingCar is flying..." << endl;
    }
    
    void drive() override {
        cout << "FlyingCar is driving..." << endl;
    }
};
```

### **Usage**
```cpp
int main() {
    FlyingCar myVehicle;
    myVehicle.fly();
    myVehicle.drive();
    
    return 0;
}
```

### **Output:**
```
FlyingCar is flying...
FlyingCar is driving...
```

---

## **Providing Default Implementations in Interfaces**

Unlike Java, C++ does not have **default methods** in interfaces, but we can provide default implementations in base classes.

```cpp
class Animal {
public:
    virtual void sound() = 0;
    void sleep() { // Default method
        cout << "Sleeping..." << endl;
    }
};

class Dog : public Animal {
public:
    void sound() override {
        cout << "Dog barks" << endl;
    }
};
```

### **Usage**
```cpp
int main() {
    Dog myDog;
    myDog.sound();
    myDog.sleep();
    
    return 0;
}
```

### **Output:**
```
Dog barks
Sleeping...
```

---

## **Real-World Example: Payment System**

```cpp
class Payment {
public:
    virtual void pay(double amount) = 0;
};

class CreditCardPayment : public Payment {
public:
    void pay(double amount) override {
        cout << "Paid " << amount << " using Credit Card" << endl;
    }
};

class PayPalPayment : public Payment {
public:
    void pay(double amount) override {
        cout << "Paid " << amount << " using PayPal" << endl;
    }
};
```

### **Usage**
```cpp
int main() {
    Payment* payment1 = new CreditCardPayment();
    payment1->pay(100.50);
    
    Payment* payment2 = new PayPalPayment();
    payment2->pay(200.75);
    
    delete payment1;
    delete payment2;
    
    return 0;
}
```

### **Output:**
```
Paid 100.5 using Credit Card
Paid 200.75 using PayPal
```