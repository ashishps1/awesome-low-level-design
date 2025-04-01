# Interfaces

## Introduction

In Object-Oriented Programming (OOP), an **interface** is a crucial concept that defines a contract for classes to follow. It allows multiple classes to share a common structure while enforcing certain behaviors. Interfaces are widely used in Java and other OOP languages to achieve **abstraction, polymorphism, and loose coupling**.

## What is an Interface?

An **interface** in Java is a collection of abstract methods (methods without implementation) that a class can implement. It defines a contract that the implementing classes must adhere to.

### **Key Characteristics of Interfaces**
- Defines a **contract** that implementing classes must follow.
- Cannot have instance variables (only `public static final` constants).
- All methods are **implicitly public and abstract** (unless they have a default or static implementation).
- Supports **multiple inheritance**, unlike classes.
- Improves **code flexibility and testability**.

---

## **Defining and Implementing an Interface in Java**

### **Step 1: Define an Interface**
To define an interface, use the `interface` keyword.

```java
// Defining an interface
public interface Vehicle {
    void start(); // Abstract method (no implementation)
    void stop();  // Abstract method (no implementation)
}
```

### **Step 2: Implement the Interface**
A class implements an interface using the `implements` keyword.

```java
// Implementing the Vehicle interface in a Car class
public class Car implements Vehicle {
    @Override
    public void start() {
        System.out.println("Car is starting...");
    }
    
    @Override
    public void stop() {
        System.out.println("Car is stopping...");
    }
}
```

### **Step 3: Using the Implemented Class**
Now, let's create objects and call the methods.

```java
public class Main {
    public static void main(String[] args) {
        Vehicle myCar = new Car(); // Polymorphism: Interface reference
        myCar.start();
        myCar.stop();
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

Unlike classes, Java **does not support multiple inheritance** with classes, but it does support **multiple inheritance** with interfaces.

```java
// First interface
interface Flyable {
    void fly();
}

// Second interface
interface Drivable {
    void drive();
}

// Implementing multiple interfaces
public class FlyingCar implements Flyable, Drivable {
    @Override
    public void fly() {
        System.out.println("FlyingCar is flying...");
    }
    
    @Override
    public void drive() {
        System.out.println("FlyingCar is driving...");
    }
}
```

### **Usage**
```java
public class Main {
    public static void main(String[] args) {
        FlyingCar myVehicle = new FlyingCar();
        myVehicle.fly();
        myVehicle.drive();
    }
}
```

### **Output:**
```
FlyingCar is flying...
FlyingCar is driving...
```

---

## **Default and Static Methods in Interfaces**

### **Default Methods**
Java 8 introduced **default methods** in interfaces, allowing methods with a body.

```java
interface Animal {
    void sound();
    
    // Default method with implementation
    default void sleep() {
        System.out.println("Sleeping...");
    }
}

class Dog implements Animal {
    @Override
    public void sound() {
        System.out.println("Dog barks");
    }
}
```

### **Usage**
```java
public class Main {
    public static void main(String[] args) {
        Dog myDog = new Dog();
        myDog.sound();
        myDog.sleep(); // Calling default method
    }
}
```

### **Output:**
```
Dog barks
Sleeping...
```

### **Static Methods**
Interfaces can also have **static methods**.

```java
interface MathOperations {
    static int add(int a, int b) {
        return a + b;
    }
}
```

### **Usage**
```java
public class Main {
    public static void main(String[] args) {
        int result = MathOperations.add(5, 10);
        System.out.println("Sum: " + result);
    }
}
```

### **Output:**
```
Sum: 15
```

---

## **Real-World Example: Payment System**

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
```

### **Usage**
```java
public class Main {
    public static void main(String[] args) {
        Payment payment1 = new CreditCardPayment();
        payment1.pay(100.50);
        
        Payment payment2 = new PayPalPayment();
        payment2.pay(200.75);
    }
}
```

### **Output:**
```
Paid 100.5 using Credit Card
Paid 200.75 using PayPal
```
