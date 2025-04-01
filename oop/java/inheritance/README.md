# Inheritance in Object-Oriented Programming (OOP)

## Introduction

**Inheritance** is one of the core principles of Object-Oriented Programming (OOP). It allows a class (subclass or child class) to acquire the properties and behaviors of another class (superclass or parent class). This promotes **code reuse**, **scalability**, and **maintainability**.

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

## **How to Implement Inheritance in Java**

### **Step 1: Create a Parent Class**
The parent class contains common fields and methods.

```java
// Parent class
public class Animal {
    String name;

    void eat() {
        System.out.println(name + " is eating...");
    }
}
```

### **Step 2: Create a Child Class using `extends`**
The child class inherits the properties and methods of the parent class.

```java
// Child class
public class Dog extends Animal {
    void bark() {
        System.out.println(name + " is barking...");
    }
}
```

### **Step 3: Use the Child Class**
Now, let's create an object and use the inherited methods.

```java
public class Main {
    public static void main(String[] args) {
        Dog myDog = new Dog();
        myDog.name = "Buddy";
        myDog.eat(); // Inherited from Animal class
        myDog.bark(); // Defined in Dog class
    }
}
```

### **Output:**
```
Buddy is eating...
Buddy is barking...
```

---

## **Types of Inheritance in Java**

Java supports different types of inheritance:

### **1. Single Inheritance**
A subclass inherits from one superclass.

```java
class Parent {
    void show() {
        System.out.println("This is the parent class");
    }
}

class Child extends Parent {
    void display() {
        System.out.println("This is the child class");
    }
}
```

### **2. Multilevel Inheritance**
A subclass inherits from another subclass, forming a chain.

```java
class Grandparent {
    void show() {
        System.out.println("Grandparent class");
    }
}

class Parent extends Grandparent {
    void display() {
        System.out.println("Parent class");
    }
}

class Child extends Parent {
    void print() {
        System.out.println("Child class");
    }
}
```

### **3. Hierarchical Inheritance**
A single parent class has multiple child classes.

```java
class Parent {
    void show() {
        System.out.println("Parent class");
    }
}

class Child1 extends Parent {
    void display() {
        System.out.println("Child1 class");
    }
}

class Child2 extends Parent {
    void print() {
        System.out.println("Child2 class");
    }
}
```

**Note:** Java **does not support multiple inheritance** (i.e., a child class inheriting from multiple parents) due to ambiguity problems.

---

## **Method Overriding in Inheritance**

Method overriding allows a child class to **redefine** a method from the parent class.

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
```

### **Usage**
```java
public class Main {
    public static void main(String[] args) {
        Animal myAnimal = new Dog(); // Polymorphism
        myAnimal.makeSound();
    }
}
```

### **Output:**
```
Dog barks
```

---

## **The `super` Keyword in Inheritance**

The `super` keyword is used to **refer to the parent class**. It helps to:
1. Call the parent class constructor.
2. Access the parent class methods.
3. Access the parent class fields.

```java
class Animal {
    Animal() {
        System.out.println("Animal Constructor");
    }
    void makeSound() {
        System.out.println("Animal makes a sound");
    }
}

class Dog extends Animal {
    Dog() {
        super(); // Calls the parent class constructor
        System.out.println("Dog Constructor");
    }
    void makeSound() {
        super.makeSound(); // Calls parent method
        System.out.println("Dog barks");
    }
}
```

### **Usage**
```java
public class Main {
    public static void main(String[] args) {
        Dog myDog = new Dog();
        myDog.makeSound();
    }
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

```java
class Employee {
    String name;
    double salary;
    
    Employee(String name, double salary) {
        this.name = name;
        this.salary = salary;
    }
    void displayDetails() {
        System.out.println("Employee: " + name + ", Salary: " + salary);
    }
}

class Manager extends Employee {
    double bonus;
    
    Manager(String name, double salary, double bonus) {
        super(name, salary);
        this.bonus = bonus;
    }
    void displayDetails() {
        super.displayDetails();
        System.out.println("Bonus: " + bonus);
    }
}
```

### **Usage**
```java
public class Main {
    public static void main(String[] args) {
        Manager manager = new Manager("Alice", 70000, 10000);
        manager.displayDetails();
    }
}
```

### **Output:**
```
Employee: Alice, Salary: 70000.0
Bonus: 10000.0
```