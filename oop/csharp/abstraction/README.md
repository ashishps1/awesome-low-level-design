# Abstraction

## Introduction

Abstraction is one of the four fundamental concepts of Object-Oriented Programming (OOP), alongside encapsulation, inheritance, and polymorphism. Abstraction allows developers to reduce complexity by focusing on the essential characteristics of an object while omitting unnecessary details. In C#, abstraction is achieved primarily through the use of abstract classes and interfaces.

## Concept of Abstraction

Abstraction involves the process of identifying the common patterns across objects and defining them in such a way that unnecessary complexity is hidden. It's about creating simple models that represent complex realities, focusing on what an object does rather than how it does it.

## Benefits of Abstraction

- **Simplification**: Abstraction helps to manage complexity by focusing on high-level interactions.
- **Reusability**: Abstract classes and functions can be reused across different parts of a program.
- **Maintainability**: By separating interface from implementation, changes can often be made with minimal impact on the codebase.
- **Flexibility**: Developers can implement multiple methods for how the interactions occur without affecting other parts of the system.

### Real-World Example

Consider a car: it has attributes like speed, fuel type, and color, and behaviors like accelerating, braking, and turning. In the abstraction of a car, you don't need to worry about the exact mechanics of the engine when you're driving, just the interactions with the car's controls. This simplification allows the driver to focus on driving rather than technical details.

## Abstraction in C#

In C#, abstraction is implemented using abstract classes and interfaces. Both provide a way to define the structure for other classes without providing a full implementation.

### Abstract Classes

An abstract class in C# is a class that cannot be instantiated on its own and must be inherited by other classes to be used. It can contain abstract methods that have no implementation, as well as methods with a default implementation.

#### Declaring Abstract Classes

```csharp
public abstract class Vehicle
{
    public abstract void Start(); // Abstract method

    public void Stop() // Non-abstract method
    {
        Console.WriteLine("The vehicle has stopped.");
    }
}
```

#### Inheriting Abstract Classes

```csharp
public class Car : Vehicle
{
    public override void Start() // Implementing the abstract method
    {
        Console.WriteLine("The car engine starts with a roar.");
    }
}
```

### Interfaces

An interface in C# is similar to an abstract class in that it cannot be instantiated, but it is a contract that classes can implement. Interfaces can only contain method signatures, properties, events, and indexers with no implementation.

#### Declaring Interfaces

```csharp
public interface IDriveable
{
    void Accelerate();
    void Brake();
}
```

#### Implementing Interfaces

```csharp
public class Bicycle : IDriveable
{
    public void Accelerate()
    {
        Console.WriteLine("The bicycle accelerates.");
    }

    public void Brake()
    {
        Console.WriteLine("The bicycle slows down using brakes.");
    }
}
```

## Abstract Class vs. Interface

- **Abstract Classes:**
  - Can contain fields and methods with implementations.
  - Use when there is a need to share code across related classes.
  - Suitable for a partially implemented common base class.

- **Interfaces:**
  - Cannot contain fields or implementation logic.
  - Use when multiple unrelated classes need to implement certain behaviors.
  - Ideal for defining capabilities and ensuring a contract is followed.

## When to Use Abstraction

- Use abstraction to hide the complex reality while exposing only the necessary parts of an object.
- Simplify code maintenance by ensuring that changes to implementation details do not affect code using the abstraction.
- Improve code readability and reusability by defining clear contracts with abstract classes and interfaces.