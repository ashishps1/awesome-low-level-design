# Abstraction in C#

## Introduction

**Abstraction** is one of the four fundamental principles of Object-Oriented Programming (OOP). It allows you to hide **implementation details** while exposing only the necessary parts of an object. This helps in reducing complexity and increasing maintainability.

Abstraction in C# is mainly achieved using:
1. **Abstract Classes**
2. **Interfaces**

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

An **abstract class** in C# is a class that **cannot be instantiated**. It is used to define common behavior that multiple subclasses should implement.

### **Example: Abstract Class in C#**

```csharp
using System;

// Abstract class
abstract class Vehicle {
    protected string Brand;
    
    public Vehicle(string brand) {
        Brand = brand;
    }
    
    public abstract void Start(); // Abstract method
    
    public void DisplayBrand() {
        Console.WriteLine("Brand: " + Brand);
    }
}

// Subclass implementing the abstract method
class Car : Vehicle {
    public Car(string brand) : base(brand) {}
    
    public override void Start() {
        Console.WriteLine("Car is starting...");
    }
}

class Program {
    static void Main() {
        Vehicle myCar = new Car("Toyota");
        myCar.DisplayBrand();
        myCar.Start();
    }
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

## **2. Abstraction Using Interfaces**

An **interface** in C# is a contract that defines methods a class must implement.

### **Example: Interface in C#**

```csharp
using System;

// Defining an interface
interface IAnimal {
    void MakeSound(); // Abstract method
}

// Implementing the interface in Dog class
class Dog : IAnimal {
    public void MakeSound() {
        Console.WriteLine("Dog barks");
    }
}

// Implementing the interface in Cat class
class Cat : IAnimal {
    public void MakeSound() {
        Console.WriteLine("Cat meows");
    }
}

class Program {
    static void Main() {
        IAnimal myDog = new Dog();
        myDog.MakeSound();
        
        IAnimal myCat = new Cat();
        myCat.MakeSound();
    }
}
```

### **Output:**
```
Dog barks
Cat meows
```

**Why Use Interfaces?**
- Promotes **full abstraction** (hides all implementation details).
- Supports **multiple inheritance** in C#.
- Provides a standard way for different classes to implement behaviors.

---

## **Abstract Class vs Interface: Key Differences**

| Feature | Abstract Class | Interface |
|---------|---------------|-----------|
| Methods | Can have abstract and concrete methods | Only abstract methods (before C# 8) |
| Fields | Can have member variables | Cannot have instance variables |
| Constructor | Can have constructors | Cannot have constructors |
| Multiple Inheritance | Not supported | Supported |
| Access Modifiers | Can have different access modifiers | Methods are `public` by default |

---

## **Real-World Example: Payment System**

Abstraction is widely used in real-world applications, such as payment processing.

### **Example: Payment System with Abstraction**

```csharp
using System;

// Abstract class for Payment
abstract class Payment {
    protected double Amount;
    
    public Payment(double amount) {
        Amount = amount;
    }
    
    public abstract void Pay(); // Abstract method
}

// Implementing payment methods
class CreditCardPayment : Payment {
    public CreditCardPayment(double amount) : base(amount) {}
    
    public override void Pay() {
        Console.WriteLine("Paid " + Amount + " using Credit Card");
    }
}

class PayPalPayment : Payment {
    public PayPalPayment(double amount) : base(amount) {}
    
    public override void Pay() {
        Console.WriteLine("Paid " + Amount + " using PayPal");
    }
}

class Program {
    static void Main() {
        Payment payment;
        
        payment = new CreditCardPayment(150.75);
        payment.Pay();
        
        payment = new PayPalPayment(200.50);
        payment.Pay();
    }
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