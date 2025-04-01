# Composition in Golang

## Introduction

Composition is one of the fundamental principles of object-oriented programming (OOP). It allows objects to be built using other objects, promoting code reuse, flexibility, and better maintainability. Unlike inheritance, which establishes an "is-a" relationship, composition represents a "has-a" relationship.

## What is Composition?

Composition is a design principle in OOP where one struct contains an instance (or instances) of another struct as a field. The contained struct is often called a component, and the containing struct is referred to as a composite struct. This helps in building complex systems by combining simpler objects.

### Example: A Car and its Components

Consider a `Car` that consists of multiple components like an `Engine`, `Wheel`, and `Transmission`. Instead of inheriting from these components, a `Car` object will contain them as fields.

```go
package main

import "fmt"

type Engine struct {
    Horsepower int
}

func (e Engine) Start() {
    fmt.Printf("Engine started with %d HP.\n", e.Horsepower)
}

type Wheel struct {
    Type string
}

func (w Wheel) Rotate() {
    fmt.Printf("The %s wheel is rotating.\n", w.Type)
}

type Transmission struct {
    Type string
}

func (t Transmission) ShiftGear() {
    fmt.Printf("Transmission shifted: %s\n", t.Type)
}

type Car struct {
    Engine       Engine
    Wheel        Wheel
    Transmission Transmission
}

func (c Car) Drive() {
    c.Engine.Start()
    c.Wheel.Rotate()
    c.Transmission.ShiftGear()
    fmt.Println("Car is moving!")
}

func main() {
    engine := Engine{Horsepower: 150}
    wheel := Wheel{Type: "Alloy"}
    transmission := Transmission{Type: "Automatic"}
    
    car := Car{Engine: engine, Wheel: wheel, Transmission: transmission}
    car.Drive()
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
   - Composition promotes reusable components. The `Engine`, `Wheel`, and `Transmission` structs can be used in multiple types of vehicles (Car, Bike, Truck) without modification.

### 3. **Avoids Inheritance Pitfalls**
   - Inheritance can lead to deep struct hierarchies, making maintenance difficult.
   - It enforces strict parent-child relationships, which can be too rigid for some designs.

### 4. **Supports Interface-Based Design**
   - Composition can be combined with interfaces to achieve powerful decoupling.

---

## Composition with Interfaces

Using interfaces with composition allows for greater flexibility and loose coupling.

```go
package main

import "fmt"

type Engine interface {
    Start()
}

type PetrolEngine struct {}

func (p PetrolEngine) Start() {
    fmt.Println("Petrol Engine started.")
}

type DieselEngine struct {}

func (d DieselEngine) Start() {
    fmt.Println("Diesel Engine started.")
}

type Car struct {
    engine Engine
}

func (c Car) StartCar() {
    c.engine.Start()
    fmt.Println("Car is ready to go!")
}

func main() {
    petrolCar := Car{engine: PetrolEngine{}}
    petrolCar.StartCar()
    
    dieselCar := Car{engine: DieselEngine{}}
    dieselCar.StartCar()
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