# Inheritance in C#

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

## **How to Implement Inheritance in C#**

### **Step 1: Create a Parent Class**
The parent class contains common fields and methods.

```csharp
using System;

// Parent class
class Animal {
    public string Name;
    
    public void Eat() {
        Console.WriteLine(Name + " is eating...");
    }
}
```

### **Step 2: Create a Child Class using `:`**
The child class inherits the properties and methods of the parent class.

```csharp
// Child class
class Dog : Animal {
    public void Bark() {
        Console.WriteLine(Name + " is barking...");
    }
}
```

### **Step 3: Use the Child Class**
Now, let's create an object and use the inherited methods.

```csharp
class Program {
    static void Main() {
        Dog myDog = new Dog();
        myDog.Name = "Buddy";
        myDog.Eat(); // Inherited from Animal class
        myDog.Bark(); // Defined in Dog class
    }
}
```

### **Output:**
```
Buddy is eating...
Buddy is barking...
```

---

## **Types of Inheritance in C#**

C# supports different types of inheritance:

### **1. Single Inheritance**
A subclass inherits from one superclass.

```csharp
class Parent {
    public void Show() {
        Console.WriteLine("This is the parent class");
    }
}

class Child : Parent {
    public void Display() {
        Console.WriteLine("This is the child class");
    }
}
```

### **2. Multilevel Inheritance**
A subclass inherits from another subclass, forming a chain.

```csharp
class Grandparent {
    public void Show() {
        Console.WriteLine("Grandparent class");
    }
}

class Parent : Grandparent {
    public void Display() {
        Console.WriteLine("Parent class");
    }
}

class Child : Parent {
    public void Print() {
        Console.WriteLine("Child class");
    }
}
```

### **3. Hierarchical Inheritance**
A single parent class has multiple child classes.

```csharp
class Parent {
    public void Show() {
        Console.WriteLine("Parent class");
    }
}

class Child1 : Parent {
    public void Display() {
        Console.WriteLine("Child1 class");
    }
}

class Child2 : Parent {
    public void Print() {
        Console.WriteLine("Child2 class");
    }
}
```

**Note:** C# **does not support multiple inheritance** (i.e., a child class inheriting from multiple parents) due to ambiguity problems.

---

## **Method Overriding in Inheritance**

Method overriding allows a child class to **redefine** a method from the parent class.

```csharp
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
```

### **Usage**
```csharp
class Program {
    static void Main() {
        Animal myAnimal = new Dog(); // Polymorphism
        myAnimal.MakeSound();
    }
}
```

### **Output:**
```
Dog barks
```

---

## **The `base` Keyword in Inheritance**

The `base` keyword is used to **refer to the parent class**. It helps to:
1. Call the parent class constructor.
2. Access the parent class methods.
3. Access the parent class fields.

```csharp
class Animal {
    public Animal() {
        Console.WriteLine("Animal Constructor");
    }
    public virtual void MakeSound() {
        Console.WriteLine("Animal makes a sound");
    }
}

class Dog : Animal {
    public Dog() {
        Console.WriteLine("Dog Constructor");
    }
    public override void MakeSound() {
        base.MakeSound(); // Calls parent method
        Console.WriteLine("Dog barks");
    }
}
```

### **Usage**
```csharp
class Program {
    static void Main() {
        Dog myDog = new Dog();
        myDog.MakeSound();
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

```csharp
class Employee {
    public string Name;
    public double Salary;
    
    public Employee(string name, double salary) {
        Name = name;
        Salary = salary;
    }
    public virtual void DisplayDetails() {
        Console.WriteLine("Employee: " + Name + ", Salary: " + Salary);
    }
}

class Manager : Employee {
    public double Bonus;
    
    public Manager(string name, double salary, double bonus) : base(name, salary) {
        Bonus = bonus;
    }
    public override void DisplayDetails() {
        base.DisplayDetails();
        Console.WriteLine("Bonus: " + Bonus);
    }
}
```

### **Usage**
```csharp
class Program {
    static void Main() {
        Manager manager = new Manager("Alice", 70000, 10000);
        manager.DisplayDetails();
    }
}
```

### **Output:**
```
Employee: Alice, Salary: 70000.0
Bonus: 10000.0
```