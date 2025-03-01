# Chapter: Inheritance in C++

Welcome to the chapter on Inheritance in C++! Inheritance is a fundamental concept of Object-Oriented Programming (OOP) that allows developers to build upon existing code and create a hierarchy of classes. This not only promotes code reusability but also establishes a clear structure that can be extended or modified as required.

## Table of Contents

1. [Introduction to Inheritance](#introduction-to-inheritance)
2. [Types of Inheritance](#types-of-inheritance)
   - Single Inheritance
   - Multiple Inheritance
   - Multilevel Inheritance
   - Hierarchical Inheritance
   - Hybrid Inheritance
3. [Visibility Modes](#visibility-modes)
4. [Benefits of Inheritance](#benefits-of-inheritance)
5. [C++ Code Examples](#c-code-examples)
6. [Best Practices for Using Inheritance](#best-practices-for-using-inheritance)
7. [Conclusion](#conclusion)
8. [Further Reading](#further-reading)

---

## Introduction to Inheritance

Inheritance is a mechanism by which one class, referred to as a "derived class," inherits the properties and behaviors (data members and member functions) of another class, known as the "base class." It provides a way to create a new class from an existing class, enabling the derived class to acquire the functionalities of the base class.

### Key Concepts:
- **Base Class:** The class whose properties are inherited.
- **Derived Class:** The class that inherits properties from the base class.
- **Access Specifiers:** Determine how the base class members are accessed (public, protected, or private).

![Inheritance Diagram](https://upload.wikimedia.org/wikipedia/commons/d/d8/Diagram_inheritance.png)

## Types of Inheritance

### Single Inheritance

A derived class inherits from only one base class.

```cpp
class Base {
public:
    void greet() {
        std::cout << "Hello from Base!" << std::endl;
    }
};

class Derived : public Base {
    // Inherits greet() from Base
};
```

### Multiple Inheritance

A derived class inherits from more than one base class.

```cpp
class Base1 {
public:
    void greet() {
        std::cout << "Hello from Base1!" << std::endl;
    }
};

class Base2 {
public:
    void shout() {
        std::cout << "Hello from Base2!" << std::endl;
    }
};

class Derived : public Base1, public Base2 {
    // Inherits greet() from Base1 and shout() from Base2
};
```

### Multilevel Inheritance

A chain of inheritance where a derived class becomes a base class for another derived class.

```cpp
class Base {
public:
    void greet() {
        std::cout << "Hello from Base!" << std::endl;
    }
};

class Intermediate : public Base {
    // Inherits greet() from Base
};

class Derived : public Intermediate {
    // Inherits greet() from Intermediate (and hence from Base)
};
```

### Hierarchical Inheritance

Several derived classes inherit from a single base class.

```cpp
class Base {
public:
    void greet() {
        std::cout << "Hello from Base!" << std::endl;
    }
};

class Derived1 : public Base {
    // Inherits greet() from Base
};

class Derived2 : public Base {
    // Inherits greet() from Base
};
```

### Hybrid Inheritance

A combination of two or more types of inheritance.

![Hybrid Inheritance Diagram](https://static.javatpoint.com/cpages/images/hybrid-inheritance.jpg)

## Visibility Modes

When inheriting a class, you can specify the visibility mode, which affects the accessibility of the base class's members in the derived class:

- `public`: Public and protected members of the base class remain public and protected in the derived class.
- `protected`: Public and protected members of the base class become protected in the derived class.
- `private`: Public and protected members of the base class become private in the derived class.

```cpp
class Base {
public:
    int publicVar;
protected:
    int protectedVar;
private:
    int privateVar;
};

// Example of public inheritance
class Derived : public Base {
    void show() {
        std::cout << publicVar << " " << protectedVar; // Accessible
        // privateVar is not accessible
    }
};
```

## Benefits of Inheritance

- **Reusability:** Inheritance allows for the reuse of code across multiple classes.
- **Extensibility:** Easier to expand the application with new functionalities.
- **Polymorphism:** Provides a base for polymorphic behavior, allowing the use of base class pointers/references to interact with derived class objects.
- **Simplified Maintenance:** Centralized updates in base classes are automatically propagated to derived classes.

## C++ Code Examples

Let's consider a real-world example with shapes:

```cpp
#include <iostream>
#include <cmath>

// Base Class
class Shape {
public:
    virtual double area() const = 0; // Pure virtual function for area calculation
};

// Derived Class - Circle
class Circle : public Shape {
    double radius;
public:
    Circle(double r) : radius(r) {}
    double area() const override {
        return M_PI * radius * radius;
    }
};

// Derived Class - Rectangle
class Rectangle : public Shape {
    double width, height;
public:
    Rectangle(double w, double h) : width(w), height(h) {}
    double area() const override {
        return width * height;
    }
};

int main() {
    Shape* circle = new Circle(5.0);
    Shape* rectangle = new Rectangle(4.0, 3.0);

    std::cout << "Circle area: " << circle->area() << std::endl;
    std::cout << "Rectangle area: " << rectangle->area() << std::endl;

    delete circle;
    delete rectangle;

    return 0;
}
```

## Best Practices for Using Inheritance

- Favor composition over inheritance where appropriate for better flexibility.
- Use inheritance only if the "is-a" relationship is clear.
- Keep inheritance hierarchies as flat as possible to reduce complexity.
- Be cautious with multiple inheritance due to potential ambiguity issues.
- Always aim to uphold the Liskov Substitution Principle, ensuring derived classes can stand in for their base class counterparts without altering desired properties.

## Conclusion

Inheritance is a powerful tool in software design that offers the benefits of code reusability, extensibility, and a clearer hierarchy of class structures. Understanding when and how to use inheritance effectively is crucial for building robust and maintainable applications in C++.

## Further Reading

- [C++ Programming Language by Bjarne Stroustrup](https://www.stroustrup.com/C++.html)
- [Effective C++ by Scott Meyers](https://www.oreilly.com/library/view/effective-c/9780135150178/)
- [Design Patterns: Elements of Reusable Object-Oriented Software by Erich Gamma, Richard Helm, Ralph Johnson, John Vlissides](https://www.amazon.com/Design-Patterns-Elements-Reusable-Object-Oriented/dp/0201633612/)

Happy coding!

