# Interfaces in C#

## Introduction

In Object-Oriented Programming (OOP), an **interface** is a crucial concept that defines a contract for classes to follow. It allows multiple classes to share a common structure while enforcing certain behaviors. Interfaces are widely used in C# and other OOP languages to achieve **abstraction, polymorphism, and loose coupling**.

## What is an Interface?

An **interface** is a collection of method definitions that a class must implement. It defines a contract that implementing classes must adhere to.

### **Key Characteristics of Interfaces in C#**
- Defines a **contract** that implementing classes must follow.
- All methods are **implicitly public and abstract** (unless they have a default implementation).
- Cannot have instance variables (only static and constant fields are allowed).
- Supports **multiple inheritance**, unlike classes.
- Improves **code flexibility and maintainability**.

---

## **Defining and Implementing an Interface in C#**

### **Step 1: Define an Interface**
To define an interface, use the `interface` keyword.

```csharp
// Defining an interface
public interface IVehicle {
    void Start(); // Abstract method (no implementation)
    void Stop();  // Abstract method (no implementation)
}
```

### **Step 2: Implement the Interface**
A class implements an interface using the `: (colon)` symbol.

```csharp
// Implementing the IVehicle interface in a Car class
public class Car : IVehicle {
    public void Start() {
        Console.WriteLine("Car is starting...");
    }
    
    public void Stop() {
        Console.WriteLine("Car is stopping...");
    }
}
```

### **Step 3: Using the Implemented Class**
Now, let's create objects and call the methods.

```csharp
public class Program {
    public static void Main(string[] args) {
        IVehicle myCar = new Car(); // Polymorphism: Interface reference
        myCar.Start();
        myCar.Stop();
    }
}
```

### **Output:**
```
Car is starting...
Car is stopping...
```

---

## **Multiple Inheritance with Interfaces**

Unlike classes, C# **supports multiple inheritance** with interfaces.

```csharp
// First interface
public interface IFlyable {
    void Fly();
}

// Second interface
public interface IDrivable {
    void Drive();
}

// Implementing multiple interfaces
public class FlyingCar : IFlyable, IDrivable {
    public void Fly() {
        Console.WriteLine("FlyingCar is flying...");
    }
    
    public void Drive() {
        Console.WriteLine("FlyingCar is driving...");
    }
}
```

### **Usage**
```csharp
public class Program {
    public static void Main(string[] args) {
        FlyingCar myVehicle = new FlyingCar();
        myVehicle.Fly();
        myVehicle.Drive();
    }
}
```

### **Output:**
```
FlyingCar is flying...
FlyingCar is driving...
```

---

## **Default Method Behavior in Interfaces**

C# 8 introduced **default methods** in interfaces, allowing methods with a body.

```csharp
public interface IAnimal {
    void Sound();
    
    // Default method with implementation
    public void Sleep() {
        Console.WriteLine("Sleeping...");
    }
}

public class Dog : IAnimal {
    public void Sound() {
        Console.WriteLine("Dog barks");
    }
}
```

### **Usage**
```csharp
public class Program {
    public static void Main(string[] args) {
        Dog myDog = new Dog();
        myDog.Sound();
        myDog.Sleep(); // Calling default method
    }
}
```

### **Output:**
```
Dog barks
Sleeping...
```

---

## **Real-World Example: Payment System**

```csharp
public interface IPayment {
    void Pay(double amount);
}

public class CreditCardPayment : IPayment {
    public void Pay(double amount) {
        Console.WriteLine($"Paid {amount} using Credit Card");
    }
}

public class PayPalPayment : IPayment {
    public void Pay(double amount) {
        Console.WriteLine($"Paid {amount} using PayPal");
    }
}
```

### **Usage**
```csharp
public class Program {
    public static void Main(string[] args) {
        IPayment payment1 = new CreditCardPayment();
        payment1.Pay(100.50);
        
        IPayment payment2 = new PayPalPayment();
        payment2.Pay(200.75);
    }
}
```

### **Output:**
```
Paid 100.5 using Credit Card
Paid 200.75 using PayPal
```