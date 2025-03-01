# Inheritance in Python

## Introduction

**Inheritance** is one of the core principles of Object-Oriented Programming (OOP). It allows a class (subclass or child class) to acquire the properties and behaviors of another class (superclass or parent class). This promotes **code reuse**, **scalability**, and **maintainability**.

## **What is Inheritance?**

**Inheritance** is a mechanism where a child class derives properties and behaviors from a parent class. The child class can:
- Use the attributes and methods of the parent class
- Override parent class methods to provide a specific implementation
- Add its own additional attributes and methods

### **Key Benefits of Inheritance**
- **Code Reusability**: Avoids code duplication by reusing attributes and methods of the parent class.
- **Improves Maintainability**: Reduces redundancy, making code easier to manage.
- **Enhances Extensibility**: New functionality can be added easily without modifying existing code.

---

## **How to Implement Inheritance in Python**

### **Step 1: Create a Parent Class**
The parent class contains common attributes and methods.

```python
# Parent class
class Animal:
    def __init__(self, name):
        self.name = name
    
    def eat(self):
        print(f"{self.name} is eating...")
```

### **Step 2: Create a Child Class using Parent Class**
The child class inherits the properties and methods of the parent class.

```python
# Child class
class Dog(Animal):
    def bark(self):
        print(f"{self.name} is barking...")
```

### **Step 3: Use the Child Class**
Now, let's create an object and use the inherited methods.

```python
# Using the child class
if __name__ == "__main__":
    my_dog = Dog("Buddy")
    my_dog.eat()  # Inherited from Animal class
    my_dog.bark()  # Defined in Dog class
```

### **Output:**
```
Buddy is eating...
Buddy is barking...
```

---

## **Types of Inheritance in Python**

Python supports different types of inheritance:

### **1. Single Inheritance**
A subclass inherits from one superclass.

```python
class Parent:
    def show(self):
        print("This is the parent class")

class Child(Parent):
    def display(self):
        print("This is the child class")
```

### **2. Multilevel Inheritance**
A subclass inherits from another subclass, forming a chain.

```python
class Grandparent:
    def show(self):
        print("Grandparent class")

class Parent(Grandparent):
    def display(self):
        print("Parent class")

class Child(Parent):
    def print_info(self):
        print("Child class")
```

### **3. Hierarchical Inheritance**
A single parent class has multiple child classes.

```python
class Parent:
    def show(self):
        print("Parent class")

class Child1(Parent):
    def display(self):
        print("Child1 class")

class Child2(Parent):
    def print_info(self):
        print("Child2 class")
```

### **4. Multiple Inheritance**
Unlike Java, Python **supports multiple inheritance**, allowing a subclass to inherit from multiple parent classes.

```python
class Parent1:
    def show1(self):
        print("Parent1 class")

class Parent2:
    def show2(self):
        print("Parent2 class")

class Child(Parent1, Parent2):
    def display(self):
        print("Child class")
```

---

## **Method Overriding in Inheritance**

Method overriding allows a child class to **redefine** a method from the parent class.

```python
class Animal:
    def make_sound(self):
        print("Animal makes a sound")

class Dog(Animal):
    def make_sound(self):
        print("Dog barks")
```

### **Usage**
```python
if __name__ == "__main__":
    my_animal = Dog()  # Polymorphism
    my_animal.make_sound()
```

### **Output:**
```
Dog barks
```

---

## **The `super()` Function in Inheritance**

The `super()` function is used to **refer to the parent class**. It helps to:
1. Call the parent class constructor.
2. Access the parent class methods.

```python
class Animal:
    def __init__(self):
        print("Animal Constructor")
    
    def make_sound(self):
        print("Animal makes a sound")

class Dog(Animal):
    def __init__(self):
        super().__init__()  # Calls the parent class constructor
        print("Dog Constructor")
    
    def make_sound(self):
        super().make_sound()  # Calls parent method
        print("Dog barks")
```

### **Usage**
```python
if __name__ == "__main__":
    my_dog = Dog()
    my_dog.make_sound()
```

### **Output:**
```
Animal Constructor
Dog Constructor
Animal makes a sound
Dog barks
```

---

## **Real-World Example: Employee Management System**

```python
class Employee:
    def __init__(self, name, salary):
        self.name = name
        self.salary = salary
    
    def display_details(self):
        print(f"Employee: {self.name}, Salary: {self.salary}")

class Manager(Employee):
    def __init__(self, name, salary, bonus):
        super().__init__(name, salary)
        self.bonus = bonus
    
    def display_details(self):
        super().display_details()
        print(f"Bonus: {self.bonus}")
```

### **Usage**
```python
if __name__ == "__main__":
    manager = Manager("Alice", 70000, 10000)
    manager.display_details()
```

### **Output:**
```
Employee: Alice, Salary: 70000
Bonus: 10000
```
