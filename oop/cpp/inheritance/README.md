# Inheritance in C++

## Introduction

**Inheritance** is one of the core principles of Object-Oriented Programming (OOP). It allows a class (subclass or child class) to acquire the properties and behaviors of another class (superclass or parent class). This promotes **code reuse**, **scalability**, and **maintainability**.

---

## **What is Inheritance?**

**Inheritance** is a mechanism where a child class derives properties and behaviors from a parent class. The child class can:
- Use the fields and methods of the parent class
- Override parent class methods to provide a specific implementation
- Add its own additional properties and methods

### **Key Benefits of Inheritance**
- **Code Reusability**: Avoids code duplication by reusing fields and methods of the parent class.
- **Improves Maintainability**: Reduces redundancy, making code easier to manage.
- **Enhances Extensibility**: New functionality can be added easily without modifying existing code.

---

## **How to Implement Inheritance in C++**

### **Step 1: Create a Parent Class**
The parent class contains common fields and methods.

```cpp
#include <iostream>
using namespace std;

// Parent class
class Animal {
public:
    string name;
    void eat() {
        cout << name << " is eating..." << endl;
    }
};
```

### **Step 2: Create a Child Class using `public` Inheritance**
The child class inherits the properties and methods of the parent class.

```cpp
// Child class
class Dog : public Animal {
public:
    void bark() {
        cout << name << " is barking..." << endl;
    }
};
```

### **Step 3: Use the Child Class**
Now, let's create an object and use the inherited methods.

```cpp
int main() {
    Dog myDog;
    myDog.name = "Buddy";
    myDog.eat(); // Inherited from Animal class
    myDog.bark(); // Defined in Dog class
    return 0;
}
```

### **Output:**
```
Buddy is eating...
Buddy is barking...
```

---

## **Types of Inheritance in C++**

C++ supports different types of inheritance:

### **1. Single Inheritance**
A subclass inherits from one superclass.

```cpp
class Parent {
public:
    void show() {
        cout << "This is the parent class" << endl;
    }
};

class Child : public Parent {
public:
    void display() {
        cout << "This is the child class" << endl;
    }
};
```

### **2. Multilevel Inheritance**
A subclass inherits from another subclass, forming a chain.

```cpp
class Grandparent {
public:
    void show() {
        cout << "Grandparent class" << endl;
    }
};

class Parent : public Grandparent {
public:
    void display() {
        cout << "Parent class" << endl;
    }
};

class Child : public Parent {
public:
    void print() {
        cout << "Child class" << endl;
    }
};
```

### **3. Hierarchical Inheritance**
A single parent class has multiple child classes.

```cpp
class Parent {
public:
    void show() {
        cout << "Parent class" << endl;
    }
};

class Child1 : public Parent {
public:
    void display() {
        cout << "Child1 class" << endl;
    }
};

class Child2 : public Parent {
public:
    void print() {
        cout << "Child2 class" << endl;
    }
};
```

### **4. Multiple Inheritance** (Supported in C++)
Unlike Java, C++ allows a child class to inherit from multiple parent classes.

```cpp
class Parent1 {
public:
    void show1() {
        cout << "Parent1 class" << endl;
    }
};

class Parent2 {
public:
    void show2() {
        cout << "Parent2 class" << endl;
    }
};

class Child : public Parent1, public Parent2 {
};
```

---

## **Method Overriding in Inheritance**

Method overriding allows a child class to **redefine** a method from the parent class.

```cpp
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
```

### **Usage**
```cpp
int main() {
    Animal* myAnimal = new Dog(); // Polymorphism
    myAnimal->makeSound();
    delete myAnimal;
    return 0;
}
```

### **Output:**
```
Dog barks
```

---

## **The `super` Equivalent: Using `Base Class` Constructor in C++**

C++ uses the **constructor of the base class** to initialize inherited fields.

```cpp
class Animal {
public:
    Animal() {
        cout << "Animal Constructor" << endl;
    }
    void makeSound() {
        cout << "Animal makes a sound" << endl;
    }
};

class Dog : public Animal {
public:
    Dog() {
        cout << "Dog Constructor" << endl;
    }
    void makeSound() {
        Animal::makeSound(); // Calls parent method
        cout << "Dog barks" << endl;
    }
};
```

### **Usage**
```cpp
int main() {
    Dog myDog;
    myDog.makeSound();
    return 0;
}
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

```cpp
class Employee {
public:
    string name;
    double salary;
    
    Employee(string name, double salary) {
        this->name = name;
        this->salary = salary;
    }
    void displayDetails() {
        cout << "Employee: " << name << ", Salary: " << salary << endl;
    }
};

class Manager : public Employee {
public:
    double bonus;
    
    Manager(string name, double salary, double bonus) : Employee(name, salary) {
        this->bonus = bonus;
    }
    void displayDetails() {
        Employee::displayDetails();
        cout << "Bonus: " << bonus << endl;
    }
};
```

### **Usage**
```cpp
int main() {
    Manager manager("Alice", 70000, 10000);
    manager.displayDetails();
    return 0;
}
```

### **Output:**
```
Employee: Alice, Salary: 70000.0
Bonus: 10000.0
```