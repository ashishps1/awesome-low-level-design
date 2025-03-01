# Abstraction in C++

## Introduction

**Abstraction** is one of the four fundamental principles of Object-Oriented Programming (OOP). It allows you to hide **implementation details** while exposing only the necessary parts of an object. This helps in reducing complexity and increasing maintainability.

Abstraction in C++ is mainly achieved using:
1. **Abstract Classes**
2. **Interfaces (Pure Virtual Functions)**

---

## **What is Abstraction?**

**Abstraction** means showing only the **essential details** and hiding the **implementation**. It allows programmers to focus on **what an object does** rather than **how it does it**.

### **Key Benefits of Abstraction**
- **Reduces complexity**: Hides unnecessary implementation details.
- **Increases code reusability**: Encourages the reuse of abstracted logic.
- **Enhances security**: Protects internal object details from unintended modifications.
- **Improves maintainability**: Makes code easier to manage and update.

---

## **1. Abstraction Using Abstract Classes**

An **abstract class** in C++ is a class that **cannot be instantiated**. It is used to define common behavior that multiple subclasses should implement.

### **Example: Abstract Class in C++**

```cpp
#include <iostream>
using namespace std;

// Abstract class
class Vehicle {
protected:
    string brand;
public:
    Vehicle(string b) : brand(b) {}
    virtual void start() = 0; // Pure virtual function
    void displayBrand() {
        cout << "Brand: " << brand << endl;
    }
};

// Subclass implementing the abstract method
class Car : public Vehicle {
public:
    Car(string b) : Vehicle(b) {}
    void start() override {
        cout << "Car is starting..." << endl;
    }
};

int main() {
    Vehicle* myCar = new Car("Toyota");
    myCar->displayBrand();
    myCar->start();
    delete myCar;
    return 0;
}
```

### **Output:**
```
Brand: Toyota
Car is starting...
```

**Why Use Abstract Classes?**
- Allows defining common behavior that subclasses must implement.
- Enables partial abstraction (can have both abstract and concrete methods).
- Prevents direct instantiation of base classes.

---

## **2. Abstraction Using Interfaces (Pure Virtual Functions)**

An **interface** in C++ is created using a class that contains **only pure virtual functions**.

### **Example: Interface in C++**

```cpp
#include <iostream>
using namespace std;

// Defining an interface
class Animal {
public:
    virtual void makeSound() = 0; // Pure virtual function
};

// Implementing the interface in Dog class
class Dog : public Animal {
public:
    void makeSound() override {
        cout << "Dog barks" << endl;
    }
};

// Implementing the interface in Cat class
class Cat : public Animal {
public:
    void makeSound() override {
        cout << "Cat meows" << endl;
    }
};

int main() {
    Animal* myDog = new Dog();
    myDog->makeSound();
    
    Animal* myCat = new Cat();
    myCat->makeSound();
    
    delete myDog;
    delete myCat;
    return 0;
}
```

### **Output:**
```
Dog barks
Cat meows
```

**Why Use Interfaces?**
- Promotes **full abstraction** (hides all implementation details).
- Supports **multiple inheritance** in C++.
- Provides a standard way for different classes to implement behaviors.

---

## **Abstract Class vs Interface: Key Differences**

| Feature | Abstract Class | Interface (Pure Virtual Functions) |
|---------|---------------|----------------------------------|
| Methods | Can have abstract and concrete methods | Only pure virtual methods |
| Fields | Can have member variables | Should not have data members |
| Constructor | Can have constructors | Cannot have constructors |
| Multiple Inheritance | Not recommended | Supported |
| Access Modifiers | Can have private, protected, public members | Methods are public by default |

---

## **Real-World Example: Payment System**

Abstraction is widely used in real-world applications, such as payment processing.

### **Example: Payment System with Abstraction**

```cpp
#include <iostream>
using namespace std;

// Abstract class for Payment
class Payment {
protected:
    double amount;
public:
    Payment(double amt) : amount(amt) {}
    virtual void pay() = 0; // Abstract method
};

// Implementing payment methods
class CreditCardPayment : public Payment {
public:
    CreditCardPayment(double amt) : Payment(amt) {}
    void pay() override {
        cout << "Paid " << amount << " using Credit Card" << endl;
    }
};

class PayPalPayment : public Payment {
public:
    PayPalPayment(double amt) : Payment(amt) {}
    void pay() override {
        cout << "Paid " << amount << " using PayPal" << endl;
    }
};

int main() {
    Payment* payment;
    
    payment = new CreditCardPayment(150.75);
    payment->pay();
    
    payment = new PayPalPayment(200.50);
    payment->pay();
    
    delete payment;
    return 0;
}
```

### **Output:**
```
Paid 150.75 using Credit Card
Paid 200.50 using PayPal
```

**Why Use Abstraction in Payment Systems?**
- Allows multiple payment methods without modifying existing code.
- Improves maintainability and scalability.
- Provides a **common contract** for different payment types.