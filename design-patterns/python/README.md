# Design Patterns in Python

This directory contains Python implementations of various design patterns, following the same examples and structure as the Java implementations.

## Implemented Patterns

### Creational Patterns
- **[Adapter Pattern](adapter/)** - Convert interface of a class into another interface
- **[Factory Method Pattern](factory/)** - Create objects without specifying exact classes
- **[Builder Pattern](builder/)** - Construct complex objects step by step
- **[Singleton Pattern](singleton/)** - Ensure only one instance of a class exists

### Behavioral Patterns
- **[Observer Pattern](observer/)** - Define one-to-many dependency between objects
- **[Strategy Pattern](strategy/)** - Define family of algorithms and make them interchangeable

### Structural Patterns
- **Abstract Factory Pattern** - Create families of related objects
- **Bridge Pattern** - Separate abstraction from implementation
- **Composite Pattern** - Compose objects into tree structures
- **Decorator Pattern** - Add behavior to objects dynamically
- **Facade Pattern** - Provide simplified interface to complex subsystem
- **Flyweight Pattern** - Minimize memory usage with shared objects
- **Proxy Pattern** - Provide placeholder/surrogate for another object

### Additional Behavioral Patterns
- **Chain of Responsibility** - Pass requests along handler chain
- **Command Pattern** - Encapsulate requests as objects
- **Iterator Pattern** - Access elements sequentially without exposing structure
- **Mediator Pattern** - Define how objects interact with each other
- **Memento Pattern** - Capture and restore object state
- **State Pattern** - Allow object to alter behavior when state changes
- **Template Method Pattern** - Define skeleton of algorithm in base class
- **Visitor Pattern** - Define new operations without changing classes

## Running the Examples

Each pattern directory contains demo files that can be run independently:

```bash
# Run adapter pattern demo
python -m design-patterns.python.adapter.ecommerce_app

# Run factory pattern demo
python -m design-patterns.python.factory.factory_method_demo

# Run builder pattern demo
python -m design-patterns.python.builder.http_app_builder

# Run singleton pattern demo
python -m design-patterns.python.singleton.singleton_demo

# Run observer pattern demo
python -m design-patterns.python.observer.fitness_app_observer_demo

# Run strategy pattern demo
python -m design-patterns.python.strategy.ecommerce_app_demo
```

## Key Features

- **Same Examples**: Uses identical examples as Java implementations for consistency
- **Pythonic Code**: Follows Python conventions and best practices
- **Type Hints**: Includes type annotations for better code clarity
- **Separate Files**: Each class is in its own file for better organization
- **Abstract Base Classes**: Uses ABC for interfaces and abstract classes
- **Documentation**: Comprehensive docstrings and comments

## Pattern Structure

Each pattern follows this structure:
```
pattern_name/
├── __init__.py
├── interface_or_abstract.py      # Abstract base classes/interfaces
├── concrete_implementations.py   # Concrete classes
├── context_or_client.py          # Context classes or clients
├── demo.py                       # Demonstration of the pattern
└── README.md                     # Pattern-specific documentation
```

## Design Principles Demonstrated

- **Open/Closed Principle**: Open for extension, closed for modification
- **Dependency Inversion**: Depend on abstractions, not concretions
- **Single Responsibility**: Each class has one reason to change
- **Composition over Inheritance**: Favor object composition
- **Encapsulation**: Hide implementation details behind interfaces

## Contributing

When adding new patterns or modifying existing ones:
1. Follow the existing file structure and naming conventions
2. Include comprehensive type hints
3. Add detailed docstrings
4. Create meaningful demo examples
5. Maintain consistency with Java implementations
6. Include README documentation for each pattern