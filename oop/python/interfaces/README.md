# Interfaces in Python

## Introduction

In Object-Oriented Programming (OOP), an **interface** is a crucial concept that defines a contract for classes to follow. It allows multiple classes to share a common structure while enforcing certain behaviors. While Python does not have built-in support for interfaces like Java, it achieves the same functionality using **abstract base classes (ABCs)** from the `abc` module.

## What is an Interface?

An **interface** is a collection of method definitions that a class must implement. It defines a contract that implementing classes must adhere to.

### **Key Characteristics of Interfaces in Python**
- Uses the `abc` module to create abstract base classes (ABCs).
- Defines methods without implementation that must be overridden.
- Supports **multiple inheritance**, unlike normal classes.
- Improves **code flexibility and maintainability**.

---

## **Defining and Implementing an Interface in Python**

### **Step 1: Define an Interface using `ABC`**
To define an interface, we use the `ABC` class from the `abc` module.

```python
from abc import ABC, abstractmethod

# Defining an interface
class Vehicle(ABC):
    @abstractmethod
    def start(self):
        pass  # Abstract method (no implementation)
    
    @abstractmethod
    def stop(self):
        pass  # Abstract method (no implementation)
```

### **Step 2: Implement the Interface**
A class implements an interface by inheriting from it and providing concrete implementations of the abstract methods.

```python
# Implementing the Vehicle interface in a Car class
class Car(Vehicle):
    def start(self):
        print("Car is starting...")
    
    def stop(self):
        print("Car is stopping...")
```

### **Step 3: Using the Implemented Class**
Now, let's create objects and call the methods.

```python
if __name__ == "__main__":
    my_car = Car()  # Instantiating the class
    my_car.start()
    my_car.stop()
```

### **Output:**
```
Car is starting...
Car is stopping...
```

---

## **Multiple Inheritance with Interfaces**

Unlike normal classes, Python **supports multiple inheritance** with interfaces.

```python
from abc import ABC, abstractmethod

# First interface
class Flyable(ABC):
    @abstractmethod
    def fly(self):
        pass

# Second interface
class Drivable(ABC):
    @abstractmethod
    def drive(self):
        pass

# Implementing multiple interfaces
class FlyingCar(Flyable, Drivable):
    def fly(self):
        print("FlyingCar is flying...")
    
    def drive(self):
        print("FlyingCar is driving...")
```

### **Usage**
```python
if __name__ == "__main__":
    my_vehicle = FlyingCar()
    my_vehicle.fly()
    my_vehicle.drive()
```

### **Output:**
```
FlyingCar is flying...
FlyingCar is driving...
```

---

## **Default Method Behavior in Interfaces**

Unlike Java, Python does not have **default methods** in interfaces, but we can provide default implementations in base classes.

```python
from abc import ABC, abstractmethod

class Animal(ABC):
    @abstractmethod
    def sound(self):
        pass
    
    def sleep(self):  # Default method
        print("Sleeping...")

class Dog(Animal):
    def sound(self):
        print("Dog barks")
```

### **Usage**
```python
if __name__ == "__main__":
    my_dog = Dog()
    my_dog.sound()
    my_dog.sleep()
```

### **Output:**
```
Dog barks
Sleeping...
```

---

## **Real-World Example: Payment System**

```python
from abc import ABC, abstractmethod

class Payment(ABC):
    @abstractmethod
    def pay(self, amount):
        pass

class CreditCardPayment(Payment):
    def pay(self, amount):
        print(f"Paid {amount} using Credit Card")

class PayPalPayment(Payment):
    def pay(self, amount):
        print(f"Paid {amount} using PayPal")
```

### **Usage**
```python
if __name__ == "__main__":
    payment1 = CreditCardPayment()
    payment1.pay(100.50)
    
    payment2 = PayPalPayment()
    payment2.pay(200.75)
```

### **Output:**
```
Paid 100.5 using Credit Card
Paid 200.75 using PayPal
```