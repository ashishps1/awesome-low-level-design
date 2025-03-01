# Abstraction

## Introduction to Abstraction

Abstraction is one of the four fundamental principles of Object-Oriented Programming (OOP). It focuses on hiding the complex reality while exposing the essential features of an object. In simpler terms, abstraction is about creating a simple, user-friendly interface over a more complex system. It's about picking out common features and simplifying relationships and interactions in your code.

## Understanding Abstraction in C++

In C++, abstraction is achieved through the use of classes and objects. You define a class to represent a theoretical abstraction, and objects are the tangible manifestation of this concept. Abstraction enables you to concentrate on the object interactions based on their interface, not implementation details.

## Benefits of Abstraction

- **Simplification**: Abstraction helps to manage complexity by focusing on high-level interactions.
- **Reusability**: Abstract classes and functions can be reused across different parts of a program.
- **Maintainability**: By separating interface from implementation, changes can often be made with minimal impact on the codebase.
- **Flexibility**: Developers can implement multiple methods for how the interactions occur without affecting other parts of the system.

## Implementing Abstraction in C++

### Abstract Classes

In C++, an abstract class serves as a blueprint for other classes. They cannot be instantiated on their own and are designed to be inherited by subclasses. This way, they enforce a common interface.

### Pure Virtual Functions

A pure virtual function is a function with no implementation. If a class includes at least one pure virtual function, it becomes an abstract class. Derived classes are responsible for implementing these functions.

**Syntax Example:** 

```cpp
class AbstractBase {
public:
    virtual void display() = 0;  // Pure virtual function
};
```

**Implementation Example:**

```cpp
class AbstractBase {
public:
    virtual void display() = 0;  // Pure virtual function
};

class Derived : public AbstractBase {
public:
    void display() override {
        std::cout << "Implementation of display" << std::endl;
    }
};

int main() {
    Derived obj;
    obj.display();  // Outputs: Implementation of display
    return 0;
}
```

In this example, `Derived` class implements the pure virtual function `display`, making it an instantiable class.

## Real-world Examples

1. **File System Interface**: Consider a filesystem library where you want to interact with various storage types like local disk, cloud storage, etc. An abstract class `FileSystem` can define operations like `read`, `write`, and `delete`. Each specific type of storage implements these operations specifically.

2. **Shape Drawing Example**: Abstract class `Shape` with a pure virtual function `draw()`. Subclasses like `Circle`, `Rectangle`, and `Triangle` can have different `draw` implementations.

```cpp
class Shape {
public:
    virtual void draw() = 0;
};

class Circle : public Shape {
public:
    void draw() override {
        std::cout << "Drawing Circle" << std::endl;
    }
};

class Rectangle : public Shape {
public:
    void draw() override {
        std::cout << "Drawing Rectangle" << std::endl;
    }
};
```