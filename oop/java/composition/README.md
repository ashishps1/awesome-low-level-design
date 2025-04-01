# Composition in Java

## Introduction

Composition is one of the fundamental principles of object-oriented programming (OOP). It allows objects to be built using other objects, promoting code reuse, flexibility, and better maintainability. Unlike inheritance, which establishes an "is-a" relationship, composition represents a "has-a" relationship.

## What is Composition?

Composition is a design principle in OOP where one class contains an instance (or instances) of another class as a field. The contained class is often called a component, and the containing class is referred to as a composite class. This helps in building complex systems by combining simpler objects.

### Example: A Car and its Components

Consider a `Car` that consists of multiple components like an `Engine`, `Wheel`, and `Transmission`. Instead of inheriting from these components, a `Car` object will contain them as fields.

```java
class Engine {
    private int horsepower;

    public Engine(int horsepower) {
        this.horsepower = horsepower;
    }

    public void start() {
        System.out.println("Engine started with " + horsepower + " HP.");
    }
}

class Wheel {
    private String type;

    public Wheel(String type) {
        this.type = type;
    }

    public void rotate() {
        System.out.println("The " + type + " wheel is rotating.");
    }
}

class Transmission {
    private String type;

    public Transmission(String type) {
        this.type = type;
    }

    public void shiftGear() {
        System.out.println("Transmission shifted: " + type);
    }
}

class Car {
    private Engine engine;
    private Wheel wheel;
    private Transmission transmission;

    public Car(Engine engine, Wheel wheel, Transmission transmission) {
        this.engine = engine;
        this.wheel = wheel;
        this.transmission = transmission;
    }

    public void drive() {
        engine.start();
        wheel.rotate();
        transmission.shiftGear();
        System.out.println("Car is moving!");
    }
}

public class CompositionExample {
    public static void main(String[] args) {
        Engine engine = new Engine(150);
        Wheel wheel = new Wheel("Alloy");
        Transmission transmission = new Transmission("Automatic");
        
        Car car = new Car(engine, wheel, transmission);
        car.drive();
    }
}
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
   - Composition can be combined with interfaces to achieve powerful decoupling.

---

## Composition with Interfaces

Using interfaces with composition allows for greater flexibility and loose coupling.

```java
interface Engine {
    void start();
}

class PetrolEngine implements Engine {
    public void start() {
        System.out.println("Petrol Engine started.");
    }
}

class DieselEngine implements Engine {
    public void start() {
        System.out.println("Diesel Engine started.");
    }
}

class Car {
    private Engine engine;

    public Car(Engine engine) {
        this.engine = engine;
    }

    public void startCar() {
        engine.start();
        System.out.println("Car is ready to go!");
    }
}

public class InterfaceCompositionExample {
    public static void main(String[] args) {
        Car petrolCar = new Car(new PetrolEngine());
        petrolCar.startCar();
        
        Car dieselCar = new Car(new DieselEngine());
        dieselCar.startCar();
    }
}
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