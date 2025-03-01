# Chapter: Abstraction in Object-Oriented Programming

Welcome to the chapter on Abstraction, a fundamental concept in Object-Oriented Programming (OOP). Abstraction allows us to focus on what an object does rather than how it does it, simplifying complex systems by modeling classes appropriate to the problem domain.

## **Table of Contents**

- [Chapter: Abstraction in Object-Oriented Programming](#chapter-abstraction-in-object-oriented-programming)
  - [**Table of Contents**](#table-of-contents)
  - [**Introduction to Abstraction**](#introduction-to-abstraction)
  - [**Benefits of Abstraction**](#benefits-of-abstraction)
  - [**Abstraction in Python**](#abstraction-in-python)
  - [**Implementing Abstraction using Abstract Base Classes (ABCs)**](#implementing-abstraction-using-abstract-base-classes-abcs)
    - [Example with Multiple Abstract Methods:](#example-with-multiple-abstract-methods)
  - [**Real-world Example**](#real-world-example)
    - [Banking System](#banking-system)
  - [**Conclusion**](#conclusion)
  - [**Further Reading**](#further-reading)

## **Introduction to Abstraction**

Abstraction is a core concept in OOP that serves to reduce complexity by hiding unnecessary details from the user. It involves creating models that capture the relevant attributes and behaviors of an object, omitting the irrelevant details.

This concept helps in managing large codebases, enhances code readability, and fosters flexibility and maintainability. In essence, abstraction enables programmers to handle layers of complexity by focusing on the essential characteristics of an object.

## **Benefits of Abstraction**

- **Simplification**: By presenting only necessary details, abstraction simplifies interaction with complex systems.
- **Code Reusability**: Promotes reusable models as abstract classes can serve as blueprints for various implementations.
- **Reduced Complexity**: Abstraction hides the implementation details, therefore reducing the complexity of interacting with the functionality.
- **Enhanced Maintainability**: Changes in implementation do not affect the end user or other parts of the system, facilitating easier maintenance.

## **Abstraction in Python**

Python supports abstraction in several ways, primarily through the use of abstract classes and interfaces. An abstract class cannot be instantiated directly and typically includes one or more abstract methods (methods without implementation).

```python
from abc import ABC, abstractmethod

class Animal(ABC):
    @abstractmethod
    def make_sound(self):
        pass

class Dog(Animal):
    def make_sound(self):
        return "Bark"

class Cat(Animal):
    def make_sound(self):
        return "Meow"
```

In the above example, `Animal` is an abstract class with an abstract method `make_sound()`. The `Dog` and `Cat` classes inherit from `Animal` and provide their own implementations of the `make_sound()` method.

## **Implementing Abstraction using Abstract Base Classes (ABCs)**

Abstract Base Classes (ABCs) are part of Python's `abc` module and are used to define abstract methods and properties. ABCs serve as a blueprint for other classes:

1. **Define Abstract Methods**: Methods declared with the `@abstractmethod` decorator must be implemented by any subclass.
2. **Inheriting from ABC**: Any class inheriting from an ABC must implement all abstract methods.

### Example with Multiple Abstract Methods:

```python
from abc import ABC, abstractmethod

class Vehicle(ABC):
    @abstractmethod
    def start_engine(self):
        pass

    @abstractmethod
    def stop_engine(self):
        pass

class Car(Vehicle):
    def start_engine(self):
        return "Car engine started"

    def stop_engine(self):
        return "Car engine stopped"

class Motorcycle(Vehicle):
    def start_engine(self):
        return "Motorcycle engine started"

    def stop_engine(self):
        return "Motorcycle engine stopped"
```

In this example, `Vehicle` defines two abstract methods that must be implemented by any subclass. `Car` and `Motorcycle` both provide concrete implementations for these methods.

## **Real-world Example**

Let's create a more realistic example highlighting the power of abstraction in a software modeling scenario:

### Banking System

Consider the case of modeling a banking system where different types of accounts exhibit different behaviours but share a core set of functionalities:

```python
from abc import ABC, abstractmethod

class Account(ABC):
    @abstractmethod
    def deposit(self, amount):
        pass

    @abstractmethod
    def withdraw(self, amount):
        pass

    @abstractmethod
    def get_balance(self):
        pass

class SavingsAccount(Account):
    def __init__(self, balance=0):
        self.balance = balance
    
    def deposit(self, amount):
        self.balance += amount
        print(f"Deposited {amount}, new balance is {self.balance}")
    
    def withdraw(self, amount):
        if self.balance >= amount:
            self.balance -= amount
            print(f"Withdrew {amount}, new balance is {self.balance}")
        else:
            print("Insufficient funds")
    
    def get_balance(self):
        return self.balance

class CheckingAccount(Account):
    def __init__(self, balance=0, overdraft_limit=100):
        self.balance = balance
        self.overdraft_limit = overdraft_limit
    
    def deposit(self, amount):
        self.balance += amount
        print(f"Deposited {amount}, new balance is {self.balance}")
    
    def withdraw(self, amount):
        if self.balance + self.overdraft_limit >= amount:
            self.balance -= amount
            print(f"Withdrew {amount}, new balance is {self.balance}")
        else:
            print("Insufficient funds including overdraft")
    
    def get_balance(self):
        return self.balance
```

In this banking system example, `Account` serves as an abstract base class with abstract methods for deposit, withdrawal, and balance inquiry. `SavingsAccount` and `CheckingAccount` are concrete implementations with their specific details.

## **Conclusion**

Abstraction is a powerful tool in the arsenal of object-oriented programming. It simplifies code interaction and fosters a clean and scalable code architecture. In Python, abstraction is gracefully handled using abstract base classes provided by the `abc` module.

Through abstraction, developers can build intuitive and robust systems, by focusing on high-level functionalities while concealing intricate details of implementation. Remember, a well-abstracted system allows objects to interact seamlessly, maintaining the integrity and functionality of large-scale software applications.

## **Further Reading**

- [Python's `abc` Module - Official Documentation](https://docs.python.org/3/library/abc.html)
- [Design Patterns: Elements of Reusable Object-Oriented Software](https://en.wikipedia.org/wiki/Design_Patterns)
- [The Pragmatic Programmer: Your Journey To Mastery](https://pragprog.com/titles/tpp20/the-pragmatic-programmer-20th-anniversary-edition/)

Abstraction is about generalization and intelligently hiding complexities to create efficient communication interfaces in code. As you continue practicing and applying abstraction, you'll find it an invaluable technique in designing elegant, flexible, and understandable software systems. Happy coding!