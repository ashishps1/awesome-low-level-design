# Polymorphism in C#

## Introduction

**Polymorphism** is one of the four fundamental principles of Object-Oriented Programming (OOP). It allows a single interface to be used for different types of objects, enabling **flexibility**, **scalability**, and **code reuse**.

Polymorphism in C# can be classified into two types:
1. **Compile-time Polymorphism (Method Overloading & Operator Overloading)**
2. **Run-time Polymorphism (Method Overriding & Interfaces)**

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

```csharp
using System;

class MathOperations {
    // Method with two parameters
    public int Add(int a, int b) {
        return a + b;
    }
    
    // Method with three parameters (overloaded)
    public int Add(int a, int b, int c) {
        return a + b + c;
    }
}

class Program {
    static void Main() {
        MathOperations math = new MathOperations();
        Console.WriteLine("Sum (2 numbers): " + math.Add(5, 10));
        Console.WriteLine("Sum (3 numbers): " + math.Add(5, 10, 15));
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

```csharp
using System;

class Animal {
    public virtual void MakeSound() {
        Console.WriteLine("Animal makes a sound");
    }
}

class Dog : Animal {
    public override void MakeSound() {
        Console.WriteLine("Dog barks");
    }
}

class Cat : Animal {
    public override void MakeSound() {
        Console.WriteLine("Cat meows");
    }
}

class Program {
    static void Main() {
        Animal myAnimal = new Dog(); // Upcasting
        myAnimal.MakeSound();
        
        myAnimal = new Cat(); // Dynamic method dispatch
        myAnimal.MakeSound();
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

```csharp
using System;

interface IVehicle {
    void Start();
}

class Car : IVehicle {
    public void Start() {
        Console.WriteLine("Car is starting...");
    }
}

class Bike : IVehicle {
    public void Start() {
        Console.WriteLine("Bike is starting...");
    }
}

class Program {
    static void Main() {
        IVehicle myVehicle = new Car();
        myVehicle.Start();
        
        myVehicle = new Bike();
        myVehicle.Start();
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

```csharp
using System;

interface IPayment {
    void Pay(double amount);
}

class CreditCardPayment : IPayment {
    public void Pay(double amount) {
        Console.WriteLine("Paid " + amount + " using Credit Card");
    }
}

class PayPalPayment : IPayment {
    public void Pay(double amount) {
        Console.WriteLine("Paid " + amount + " using PayPal");
    }
}

class Program {
    static void Main() {
        IPayment payment;
        
        payment = new CreditCardPayment();
        payment.Pay(100.50);
        
        payment = new PayPalPayment();
        payment.Pay(200.75);
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