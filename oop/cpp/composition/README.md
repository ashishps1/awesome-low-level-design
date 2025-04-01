# Composition in C++

## Introduction

Composition is one of the fundamental principles of object-oriented programming (OOP). It allows objects to be built using other objects, promoting code reuse, flexibility, and better maintainability. Unlike inheritance, which establishes an "is-a" relationship, composition represents a "has-a" relationship.

## What is Composition?

Composition is a design principle in OOP where one class contains an instance (or instances) of another class as a field. The contained class is often called a component, and the containing class is referred to as a composite class. This helps in building complex systems by combining simpler objects.

### Example: A Car and its Components

Consider a `Car` that consists of multiple components like an `Engine`, `Wheel`, and `Transmission`. Instead of inheriting from these components, a `Car` object will contain them as fields.

```cpp
#include <iostream>
#include <string>

class Engine {
private:
    int horsepower;
public:
    Engine(int hp) : horsepower(hp) {}
    void start() {
        std::cout << "Engine started with " << horsepower << " HP." << std::endl;
    }
};

class Wheel {
private:
    std::string type;
public:
    Wheel(std::string t) : type(t) {}
    void rotate() {
        std::cout << "The " << type << " wheel is rotating." << std::endl;
    }
};

class Transmission {
private:
    std::string type;
public:
    Transmission(std::string t) : type(t) {}
    void shiftGear() {
        std::cout << "Transmission shifted: " << type << std::endl;
    }
};

class Car {
private:
    Engine engine;
    Wheel wheel;
    Transmission transmission;
public:
    Car(Engine e, Wheel w, Transmission t) : engine(e), wheel(w), transmission(t) {}
    void drive() {
        engine.start();
        wheel.rotate();
        transmission.shiftGear();
        std::cout << "Car is moving!" << std::endl;
    }
};

int main() {
    Engine engine(150);
    Wheel wheel("Alloy");
    Transmission transmission("Automatic");
    
    Car car(engine, wheel, transmission);
    car.drive();
    return 0;
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
   - Composition can be combined with abstract classes to achieve powerful decoupling.

---

## Composition with Abstract Classes

Using abstract classes with composition allows for greater flexibility and loose coupling.

```cpp
#include <iostream>
using namespace std;

class Engine {
public:
    virtual void start() = 0; // Pure virtual function
};

class PetrolEngine : public Engine {
public:
    void start() override {
        cout << "Petrol Engine started." << endl;
    }
};

class DieselEngine : public Engine {
public:
    void start() override {
        cout << "Diesel Engine started." << endl;
    }
};

class Car {
private:
    Engine* engine;
public:
    Car(Engine* e) : engine(e) {}
    void startCar() {
        engine->start();
        cout << "Car is ready to go!" << endl;
    }
};

int main() {
    PetrolEngine petrolEngine;
    DieselEngine dieselEngine;
    
    Car petrolCar(&petrolEngine);
    petrolCar.startCar();
    
    Car dieselCar(&dieselEngine);
    dieselCar.startCar();
    
    return 0;
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