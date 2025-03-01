# Composition in Python

## Introduction

Composition is one of the fundamental principles of object-oriented programming (OOP). It allows objects to be built using other objects, promoting code reuse, flexibility, and better maintainability. Unlike inheritance, which establishes an "is-a" relationship, composition represents a "has-a" relationship.

## What is Composition?

Composition is a design principle in OOP where one class contains an instance (or instances) of another class as a field. The contained class is often called a component, and the containing class is referred to as a composite class. This helps in building complex systems by combining simpler objects.

### Example: A Car and its Components

Consider a `Car` that consists of multiple components like an `Engine`, `Wheel`, and `Transmission`. Instead of inheriting from these components, a `Car` object will contain them as fields.

```python
class Engine:
    def __init__(self, horsepower):
        self.horsepower = horsepower
    
    def start(self):
        print(f"Engine started with {self.horsepower} HP.")


class Wheel:
    def __init__(self, type):
        self.type = type
    
    def rotate(self):
        print(f"The {self.type} wheel is rotating.")


class Transmission:
    def __init__(self, type):
        self.type = type
    
    def shift_gear(self):
        print(f"Transmission shifted: {self.type}")


class Car:
    def __init__(self, engine, wheel, transmission):
        self.engine = engine
        self.wheel = wheel
        self.transmission = transmission
    
    def drive(self):
        self.engine.start()
        self.wheel.rotate()
        self.transmission.shift_gear()
        print("Car is moving!")


# Example Usage
if __name__ == "__main__":
    engine = Engine(150)
    wheel = Wheel("Alloy")
    transmission = Transmission("Automatic")
    
    car = Car(engine, wheel, transmission)
    car.drive()
```

### Output:
```
Engine started with 150 HP.
The Alloy wheel is rotating.
Transmission shifted: Automatic
Car is moving!
```

---

## Why Prefer Composition Over Inheritance?

### 1. **Encapsulation and Flexibility**
   - Composition allows us to change the behavior of an object dynamically by replacing components at runtime.
   - Inheritance makes it difficult to modify an existing class hierarchy without breaking existing code.

### 2. **Better Code Reusability**
   - Composition promotes reusable components. The `Engine`, `Wheel`, and `Transmission` classes can be used in multiple types of vehicles (Car, Bike, Truck) without modification.

### 3. **Avoids Inheritance Pitfalls**
   - Inheritance can lead to deep class hierarchies, making maintenance difficult.
   - It enforces strict parent-child relationships, which can be too rigid for some designs.

### 4. **Supports Interface-Based Design**
   - Composition can be combined with interfaces (or abstract classes) to achieve powerful decoupling.

---

## Composition with Abstract Classes

Using abstract base classes with composition allows for greater flexibility and loose coupling.

```python
from abc import ABC, abstractmethod

class Engine(ABC):
    @abstractmethod
    def start(self):
        pass


class PetrolEngine(Engine):
    def start(self):
        print("Petrol Engine started.")


class DieselEngine(Engine):
    def start(self):
        print("Diesel Engine started.")


class Car:
    def __init__(self, engine: Engine):
        self.engine = engine
    
    def start_car(self):
        self.engine.start()
        print("Car is ready to go!")


# Example Usage
if __name__ == "__main__":
    petrol_car = Car(PetrolEngine())
    petrol_car.start_car()
    
    diesel_car = Car(DieselEngine())
    diesel_car.start_car()
```

### Output:
```
Petrol Engine started.
Car is ready to go!
Diesel Engine started.
Car is ready to go!
```

---

## When to Use Composition?

- When building complex objects that consist of multiple components.
- When you want to achieve **code reusability** without rigid inheritance hierarchies.
- When different behaviors need to be swapped dynamically (e.g., using different types of engines in a vehicle).
- When following the **favor composition over inheritance** principle.