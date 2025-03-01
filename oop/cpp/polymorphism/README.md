# Chapter: Polymorphism in C++

## Introduction

Polymorphism is one of the four fundamental principles of Object-Oriented Programming (OOP), along with encapsulation, inheritance, and abstraction. It provides a way to perform a single action in different forms, allowing methods to do different things based on the object they are acting upon. This chapter focuses on understanding and implementing polymorphism in C++.

## What is Polymorphism?

Polymorphism in C++ refers to the ability of a function or a method to process objects differently depending on their data type or class. It allows one interface to be used for a general class of actions, making it easier to re-use code and to build comprehensive systems through manageable and extendable architectures.

### Types of Polymorphism

1. **Compile-time Polymorphism (Static Binding)**:
   - Achieved via function overloading and operator overloading.
   - The function to be invoked is determined at compile time.

2. **Run-time Polymorphism (Dynamic Binding)**:
   - Achieved using inheritance and virtual functions.
   - The function to be invoked is determined at run time.

## Compile-time Polymorphism

### Function Overloading

Function overloading occurs when multiple functions have the same name but differ in the type or number of their parameters.

```cpp
#include <iostream>

class Print {
public:
    void show(int i) {
        std::cout << "Integer: " << i << std::endl;
    }

    void show(double d) {
        std::cout << "Double: " << d << std::endl;
    }

    void show(std::string str) {
        std::cout << "String: " << str << std::endl;
    }
};

int main() {
    Print printer;
    printer.show(10);
    printer.show(3.14);
    printer.show("Hello World");

    return 0;
}
```

### Operator Overloading

Operator overloading allows you to redefine the way operators work for user-defined types.

```cpp
#include <iostream>

class Complex {
private:
    double real;
    double imag;

public:
    Complex(double r = 0, double i = 0) : real(r), imag(i) {}

    Complex operator + (const Complex &other) {
        return Complex(real + other.real, imag + other.imag);
    }

    void display() {
        std::cout << real << " + " << imag << "i" << std::endl;
    }
};

int main() {
    Complex c1(3.0, 4.0), c2(1.0, 2.0);
    Complex c3 = c1 + c2;
    c3.display();

    return 0;
}
```

## Run-time Polymorphism

Run-time polymorphism is achieved through dynamic method dispatch or method overriding. It relies on the capability of C++ to decide which method to invoke at runtime based on the actual object type.

### Virtual Functions

Virtual functions are declared in the base class using the `virtual` keyword and are intended to be overridden in derived classes.

```cpp
#include <iostream>

class Base {
public:
    virtual void show() {
        std::cout << "Base class show function called." << std::endl;
    }
};

class Derived : public Base {
public:
    void show() override {
        std::cout << "Derived class show function called." << std::endl;
    }
};

int main() {
    Base* b;
    Derived d;
    b = &d;

    b->show(); // Calls Derived class show() method due to dynamic binding

    return 0;
}
```

### Pure Virtual Functions and Abstract Classes

A pure virtual function is defined by assigning 0 to the virtual function in the base class and is used to create abstract classes.

```cpp
#include <iostream>

class Abstract {
public:
    virtual void show() = 0;  // Pure virtual function makes this class abstract
};

class Concrete : public Abstract {
public:
    void show() override {
        std::cout << "Concrete class implementation of show." << std::endl;
    }
};

int main() {
    Concrete c;
    c.show();

    return 0;
}
```

## Conclusion

Polymorphism is an essential aspect of object-oriented programming, enabling flexibility and the reusability of code. Through compile-time and run-time polymorphism, C++ allows you to manage and expand your applications efficiently. Understanding how to leverage polymorphism will make you more adept at designing complex systems that are easier to maintain and modify.

## Exercises

1. Implement a class hierarchy involving at least three classes that demonstrate function overloading.
2. Overload the `<<` operator to print the properties of a custom data type.
3. Create an abstract class with two pure virtual functions and derive it into at least two subclasses implementing these methods.
4. Write a program that dynamically binds to the correct method invocation using polymorphism through virtual functions.

Happy coding! Feel free to explore more about polymorphism and integrate these concepts into larger C++ projects.

