# Polymorphism in Python

## Introduction

**Polymorphism** is one of the four fundamental principles of Object-Oriented Programming (OOP). It allows a single interface to be used for different types of objects, enabling **flexibility**, **scalability**, and **code reuse**.

Polymorphism in Python can be classified into two types:
1. **Compile-time Polymorphism (Method Overloading - Python handles it differently)**
2. **Run-time Polymorphism (Method Overriding & Duck Typing)**

## **What is Polymorphism?**

**Polymorphism** means "many forms." It allows a method, function, or object to behave differently based on the context. Polymorphism enables **dynamic method resolution** and **method flexibility**, making applications easier to extend and maintain.

### **Key Benefits of Polymorphism**
- **Code Reusability**: Write a single interface that works for multiple types.
- **Scalability**: Add new functionalities with minimal code changes.
- **Maintainability**: Reduce complexity and improve code clarity.

---

## **1. Compile-Time Polymorphism (Method Overloading in Python)**

Unlike Java or C++, Python does not support method overloading in the traditional sense. However, we can achieve similar functionality by using **default parameters** or variable arguments (`*args`).

### **Example of Method Overloading using Default Arguments**

```python
class MathOperations:
    def add(self, a, b, c=0):
        return a + b + c

math = MathOperations()
print("Sum (2 numbers):", math.add(5, 10))
print("Sum (3 numbers):", math.add(5, 10, 15))
```

### **Output:**
```
Sum (2 numbers): 15
Sum (3 numbers): 30
```

**Why Use Default Arguments?**
- Simulates method overloading by providing optional parameters.
- Reduces redundancy by using a single method name for similar operations.

---

## **2. Run-Time Polymorphism (Method Overriding)**

Run-time polymorphism occurs when a subclass provides a **specific implementation** of a method already defined in its parent class. The method to be called is determined **at runtime**.

### **Example of Method Overriding**

```python
class Animal:
    def make_sound(self):
        print("Animal makes a sound")

class Dog(Animal):
    def make_sound(self):
        print("Dog barks")

class Cat(Animal):
    def make_sound(self):
        print("Cat meows")

# Demonstrating runtime polymorphism
animals = [Dog(), Cat()]
for animal in animals:
    animal.make_sound()
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

## **Using Polymorphism with Duck Typing**

Python follows the **Duck Typing** principle: "If it looks like a duck and quacks like a duck, it is a duck." This means that Python does not require explicit implementation of interfaces.

```python
class Car:
    def start(self):
        print("Car is starting...")

class Bike:
    def start(self):
        print("Bike is starting...")

# Polymorphic function
def vehicle_start(vehicle):
    vehicle.start()

vehicle_start(Car())
vehicle_start(Bike())
```

### **Output:**
```
Car is starting...
Bike is starting...
```

**Why Use Duck Typing?**
- Promotes **loose coupling**, making code more flexible.
- Allows multiple implementations of the same behavior without inheritance.
- Enables **dependency injection**, improving testability.

---

## **Real-World Example: Payment System**

A common real-world use case of polymorphism is in **payment processing**.

```python
class Payment:
    def pay(self, amount):
        pass  # Abstract method

class CreditCardPayment(Payment):
    def pay(self, amount):
        print(f"Paid {amount} using Credit Card")

class PayPalPayment(Payment):
    def pay(self, amount):
        print(f"Paid {amount} using PayPal")

# Demonstrating polymorphism
payments = [CreditCardPayment(), PayPalPayment()]
for payment in payments:
    payment.pay(100.50)
```

### **Output:**
```
Paid 100.5 using Credit Card
Paid 100.5 using PayPal
```

**Why Use Polymorphism in Payment Systems?**
- Allows new payment methods to be added **without modifying existing code**.
- Provides a **flexible and scalable** design.
- Improves **code readability and maintainability**.