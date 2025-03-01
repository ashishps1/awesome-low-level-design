# Polymorphism in Java

## Introduction

**Polymorphism** is one of the four fundamental principles of Object-Oriented Programming (OOP). It allows a single interface to be used for different types of objects, enabling **flexibility**, **scalability**, and **code reuse**.

Polymorphism in Java can be classified into two types:
1. **Compile-time Polymorphism (Method Overloading)**
2. **Run-time Polymorphism (Method Overriding)**

## **What is Polymorphism?**

**Polymorphism** means "many forms." It allows a method, function, or object to behave differently based on the context. Polymorphism enables **dynamic method resolution** and **method flexibility**, making applications easier to extend and maintain.

### **Key Benefits of Polymorphism**
- **Code Reusability**: Write a single interface that works for multiple types.
- **Scalability**: Add new functionalities with minimal code changes.
- **Maintainability**: Reduce complexity and improve code clarity.

---

## **1. Compile-Time Polymorphism (Method Overloading)**

Compile-time polymorphism occurs when multiple methods in the same class share the same name but have **different method signatures** (parameters). The method to be called is determined **at compile time**.

### **Example of Method Overloading**

```java
class MathOperations {
    // Method with two parameters
    int add(int a, int b) {
        return a + b;
    }
    
    // Method with three parameters (overloaded)
    int add(int a, int b, int c) {
        return a + b + c;
    }
}

public class Main {
    public static void main(String[] args) {
        MathOperations math = new MathOperations();
        System.out.println("Sum (2 numbers): " + math.add(5, 10));
        System.out.println("Sum (3 numbers): " + math.add(5, 10, 15));
    }
}
```

### **Output:**
```
Sum (2 numbers): 15
Sum (3 numbers): 30
```

**Why Use Method Overloading?**
- Provides a cleaner and more intuitive interface.
- Reduces redundancy by using a single method name for similar operations.

---

## **2. Run-Time Polymorphism (Method Overriding)**

Run-time polymorphism occurs when a subclass provides a **specific implementation** of a method already defined in its parent class. The method to be called is determined **at runtime**.

### **Example of Method Overriding**

```java
class Animal {
    void makeSound() {
        System.out.println("Animal makes a sound");
    }
}

class Dog extends Animal {
    @Override
    void makeSound() {
        System.out.println("Dog barks");
    }
}

class Cat extends Animal {
    @Override
    void makeSound() {
        System.out.println("Cat meows");
    }
}

public class Main {
    public static void main(String[] args) {
        Animal myAnimal = new Dog(); // Upcasting
        myAnimal.makeSound();
        
        myAnimal = new Cat(); // Dynamic method dispatch
        myAnimal.makeSound();
    }
}
```

### **Output:**
```
Dog barks
Cat meows
```

**Why Use Method Overriding?**
- Enables **dynamic method resolution**.
- Supports **polymorphic behavior**, where one interface can be used for multiple implementations.
- Makes code **extensible** by allowing future modifications.

---

## **Using Polymorphism with Interfaces**

Polymorphism is widely used with **interfaces**, allowing multiple classes to share a common contract.

```java
interface Vehicle {
    void start();
}

class Car implements Vehicle {
    public void start() {
        System.out.println("Car is starting...");
    }
}

class Bike implements Vehicle {
    public void start() {
        System.out.println("Bike is starting...");
    }
}

public class Main {
    public static void main(String[] args) {
        Vehicle myVehicle = new Car();
        myVehicle.start();
        
        myVehicle = new Bike();
        myVehicle.start();
    }
}
```

### **Output:**
```
Car is starting...
Bike is starting...
```

**Why Use Interfaces with Polymorphism?**
- Promotes **loose coupling**, making code more flexible.
- Allows multiple implementations of the same behavior.
- Enables **dependency injection**, improving testability.

---

## **Real-World Example: Payment System**

A common real-world use case of polymorphism is in **payment processing**.

```java
interface Payment {
    void pay(double amount);
}

class CreditCardPayment implements Payment {
    @Override
    public void pay(double amount) {
        System.out.println("Paid " + amount + " using Credit Card");
    }
}

class PayPalPayment implements Payment {
    @Override
    public void pay(double amount) {
        System.out.println("Paid " + amount + " using PayPal");
    }
}

public class Main {
    public static void main(String[] args) {
        Payment payment;
        
        payment = new CreditCardPayment();
        payment.pay(100.50);
        
        payment = new PayPalPayment();
        payment.pay(200.75);
    }
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