# Chapter: Polymorphism in C#

Polymorphism is a fundamental concept in Object-Oriented Programming (OOP) that allows objects to be treated as instances of their parent class rather than their actual class. The primary goal of polymorphism is to enable objects to achieve "one interface, many implementations." In this chapter, we'll delve into polymorphism, focusing on its types, benefits, and application in C#.

## Table of Contents

1. [What is Polymorphism?](#what-is-polymorphism)
2. [Types of Polymorphism](#types-of-polymorphism)
   - [Compile-Time Polymorphism (Method Overloading)](#compile-time-polymorphism)
   - [Run-Time Polymorphism (Method Overriding)](#run-time-polymorphism)
3. [Polymorphism in C#](#polymorphism-in-c)
   - [Virtual Methods and Overriding](#virtual-methods-and-overriding)
   - [Abstract Classes and Methods](#abstract-classes-and-methods)
   - [Interfaces](#interfaces)
4. [Benefits of Polymorphism](#benefits-of-polymorphism)
5. [Practical Example](#practical-example)
6. [Conclusion](#conclusion)

## What is Polymorphism?

Polymorphism in OOP allows methods to do different things based on the object they are acting on, even when those objects share the same interface. This capability helps in building scalable and maintainable systems.

## Types of Polymorphism

### Compile-Time Polymorphism

Compile-time polymorphism is achieved through *method overloading* and *operator overloading*. This form of polymorphism is decided during the program's compile time.

#### Method Overloading
Method overloading allows a class to have multiple methods with the same name but different signatures (different parameters).

```csharp
public class MathOperations
{
    public int Add(int a, int b)
    {
        return a + b;
    }

    public double Add(double a, double b)
    {
        return a + b;
    }
}
```

### Run-Time Polymorphism

Run-time polymorphism is achieved via *method overriding* and is determined during the program's execution.

#### Method Overriding
Method overriding allows a subclass to provide a specific implementation of a method already defined in its superclass.

```csharp
public class Animal
{
    public virtual void Speak()
    {
        Console.WriteLine("The animal speaks");
    }
}

public class Dog : Animal
{
    public override void Speak()
    {
        Console.WriteLine("The dog barks");
    }
}
```

## Polymorphism in C#

In C#, polymorphism is primarily accomplished through virtual methods, abstract classes, and interfaces.

### Virtual Methods and Overriding

Using the `virtual` keyword in a base class method, you can allow subclasses to provide their specific implementation by overriding those methods.

```csharp
public class Bird
{
    public virtual void Fly()
    {
        Console.WriteLine("The bird flies");
    }
}

public class Sparrow : Bird
{
    public override void Fly()
    {
        Console.WriteLine("The sparrow flies swiftly");
    }
}
```

### Abstract Classes and Methods

An abstract class can contain abstract methods, which are intended to be overridden in derived classes. Abstract methods do not have a body and force the derived class to implement them.

```csharp
public abstract class Shape
{
    public abstract double CalculateArea();
}

public class Circle : Shape
{
    private double radius;

    public Circle(double radius)
    {
        this.radius = radius;
    }

    public override double CalculateArea()
    {
        return Math.PI * radius * radius;
    }
}
```

### Interfaces

Interfaces define a contract for classes that implement them. Interfaces can contain methods, properties, events, and indexers. A class or struct that implements an interface must implement its members.

```csharp
public interface IMovable
{
    void Move();
}

public class Vehicle : IMovable
{
    public void Move()
    {
        Console.WriteLine("The vehicle moves");
    }
}
```

## Benefits of Polymorphism

1. **Reusability:** You can reuse code involving parent classes in various contexts with different derived class implementations.
2. **Flexibility and Maintainability:** New classes can be added with little or no modification to existing code.
3. **Extensibility:** Enables adding new functionalities with minimal changes.

## Practical Example

Here's a simple example illustrating polymorphism:

```csharp
public abstract class Account
{
    public abstract void DisplayAccountType();
}

public class SavingsAccount : Account
{
    public override void DisplayAccountType()
    {
        Console.WriteLine("This is a Savings Account");
    }
}

public class CurrentAccount : Account
{
    public override void DisplayAccountType()
    {
        Console.WriteLine("This is a Current Account");
    }
}

public class Bank
{
    static void Main(string[] args)
    {
        Account myAccount;

        myAccount = new SavingsAccount();
        myAccount.DisplayAccountType();

        myAccount = new CurrentAccount();
        myAccount.DisplayAccountType();
    }
}
```

In this example, both `SavingsAccount` and `CurrentAccount` classes implement the abstract method `DisplayAccountType()`. The method `DisplayAccountType()` is polymorphically called, which results in different behavior based on the instantiated object, showcasing the essence of polymorphism.

## Conclusion

Polymorphism is a powerful feature of OOP that provides flexibility and efficiency in developing scalable software systems. By using polymorphism, developers can create applications that are more modular, flexible, and easier to extend. In C#, polymorphism is implemented via virtual methods, abstract classes, and interfaces, each serving distinct purposes and use cases to enhance code reusability and maintainability. Through this chapter, you should now be equipped to effectively harness polymorphism in your C# applications.

