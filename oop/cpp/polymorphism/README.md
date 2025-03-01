# Polymorphism in C++

## Introduction

**Polymorphism** is one of the four fundamental principles of Object-Oriented Programming (OOP). It allows a single interface to be used for different types of objects, enabling **flexibility**, **scalability**, and **code reuse**.

Polymorphism in C++ can be classified into two types:
1. **Compile-time Polymorphism (Function Overloading & Operator Overloading)**
2. **Run-time Polymorphism (Function Overriding & Virtual Functions)**

## **What is Polymorphism?**

**Polymorphism** means "many forms." It allows a method, function, or object to behave differently based on the context. Polymorphism enables **dynamic method resolution** and **method flexibility**, making applications easier to extend and maintain.

### **Key Benefits of Polymorphism**
- **Code Reusability**: Write a single interface that works for multiple types.
- **Scalability**: Add new functionalities with minimal code changes.
- **Maintainability**: Reduce complexity and improve code clarity.

---

## **1. Compile-Time Polymorphism (Function Overloading)**

Compile-time polymorphism occurs when multiple functions in the same class share the same name but have **different method signatures** (parameters). The method to be called is determined **at compile time**.

### **Example of Function Overloading**

```cpp
#include <iostream>
using namespace std;

class MathOperations {
public:
    // Function with two parameters
    int add(int a, int b) {
        return a + b;
    }
    
    // Function with three parameters (overloaded)
    int add(int a, int b, int c) {
        return a + b + c;
    }
};

int main() {
    MathOperations math;
    cout << "Sum (2 numbers): " << math.add(5, 10) << endl;
    cout << "Sum (3 numbers): " << math.add(5, 10, 15) << endl;
    return 0;
}
```

### **Output:**
```
Sum (2 numbers): 15
Sum (3 numbers): 30
```

**Why Use Function Overloading?**
- Provides a cleaner and more intuitive interface.
- Reduces redundancy by using a single function name for similar operations.

---

## **2. Run-Time Polymorphism (Function Overriding & Virtual Functions)**

Run-time polymorphism occurs when a subclass provides a **specific implementation** of a method already defined in its parent class. The method to be called is determined **at runtime** using **virtual functions**.

### **Example of Function Overriding with Virtual Functions**

```cpp
#include <iostream>
using namespace std;

class Animal {
public:
    virtual void makeSound() {
        cout << "Animal makes a sound" << endl;
    }
};

class Dog : public Animal {
public:
    void makeSound() override {
        cout << "Dog barks" << endl;
    }
};

class Cat : public Animal {
public:
    void makeSound() override {
        cout << "Cat meows" << endl;
    }
};

int main() {
    Animal* myAnimal = new Dog(); // Upcasting
    myAnimal->makeSound();
    
    myAnimal = new Cat(); // Dynamic method dispatch
    myAnimal->makeSound();
    
    delete myAnimal;
    return 0;
}
```

### **Output:**
```
Dog barks
Cat meows
```

**Why Use Function Overriding?**
- Enables **dynamic method resolution**.
- Supports **polymorphic behavior**, where one interface can be used for multiple implementations.
- Makes code **extensible** by allowing future modifications.

---

## **Using Polymorphism with Abstract Classes**

Polymorphism is widely used with **abstract classes**, allowing multiple derived classes to share a common contract.

```cpp
#include <iostream>
using namespace std;

class Vehicle {
public:
    virtual void start() = 0; // Pure virtual function
};

class Car : public Vehicle {
public:
    void start() override {
        cout << "Car is starting..." << endl;
    }
};

class Bike : public Vehicle {
public:
    void start() override {
        cout << "Bike is starting..." << endl;
    }
};

int main() {
    Vehicle* myVehicle = new Car();
    myVehicle->start();
    
    myVehicle = new Bike();
    myVehicle->start();
    
    delete myVehicle;
    return 0;
}
```

### **Output:**
```
Car is starting...
Bike is starting...
```

**Why Use Abstract Classes with Polymorphism?**
- Promotes **loose coupling**, making code more flexible.
- Allows multiple implementations of the same behavior.
- Enforces common structure in derived classes.

---

## **Real-World Example: Payment System**

A common real-world use case of polymorphism is in **payment processing**.

```cpp
#include <iostream>
using namespace std;

class Payment {
public:
    virtual void pay(double amount) = 0; // Pure virtual function
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

int main() {
    Payment* payment;
    
    payment = new CreditCardPayment();
    payment->pay(100.50);
    
    payment = new PayPalPayment();
    payment->pay(200.75);
    
    delete payment;
    return 0;
}
```

### **Output:**
```
Paid 100.5 using Credit Card
Paid 200.75 using PayPal
```

**Why Use Polymorphism in Payment Systems?**
- Allows new payment methods to be added **without modifying existing code**.
- Provides a **flexible and scalable** design.
- Improves **code readability and maintainability**.