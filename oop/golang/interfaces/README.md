# Interfaces in Go (Golang)

## Introduction

In Object-Oriented Programming (OOP), an **interface** is a crucial concept that defines a contract for types to follow. It allows multiple types to share a common structure while enforcing certain behaviors. Unlike Java and C++, Go interfaces are **implicit**—a type satisfies an interface simply by implementing its methods.

## What is an Interface?

An **interface** is a set of method signatures that a type must implement. It defines a contract that implementing types must adhere to.

### **Key Characteristics of Interfaces in Go**
- Interfaces in Go are **implicit**, meaning types don’t explicitly declare they implement an interface.
- They define **method signatures** that types must implement.
- Interfaces **enable polymorphism**, allowing functions to operate on different types that share a common behavior.
- They support **multiple interface implementation**, unlike struct embedding.

---

## **Defining and Implementing an Interface in Go**

### **Step 1: Define an Interface**
To define an interface, we use the `interface` keyword.

```go
package main

import "fmt"

// Defining an interface
type Vehicle interface {
    Start()
    Stop()
}
```

### **Step 2: Implement the Interface**
A type implements an interface by defining methods with the same signatures.

```go
// Implementing the Vehicle interface in a Car struct
type Car struct {
    brand string
}

func (c Car) Start() {
    fmt.Println("Car is starting...")
}

func (c Car) Stop() {
    fmt.Println("Car is stopping...")
}
```

### **Step 3: Using the Implemented Interface**
Now, let's create an instance and call the methods.

```go
func main() {
    var myCar Vehicle = Car{brand: "Toyota"} // Interface reference
    myCar.Start()
    myCar.Stop()
}
```

### **Output:**
```
Car is starting...
Car is stopping...
```

---

## **Multiple Interface Implementation in Go**

Go allows a struct to implement multiple interfaces implicitly.

```go
// First interface
type Flyable interface {
    Fly()
}

// Second interface
type Drivable interface {
    Drive()
}

// Implementing multiple interfaces
type FlyingCar struct {}

func (f FlyingCar) Fly() {
    fmt.Println("FlyingCar is flying...")
}

func (f FlyingCar) Drive() {
    fmt.Println("FlyingCar is driving...")
}
```

### **Usage**
```go
func main() {
    var myVehicle Flyable = FlyingCar{}
    myVehicle.Fly()
    
    var myCar Drivable = FlyingCar{}
    myCar.Drive()
}
```

### **Output:**
```
FlyingCar is flying...
FlyingCar is driving...
```

---

## **Interface Composition in Go**

Go interfaces can be composed of other interfaces.

```go
type Engine interface {
    Start()
    Stop()
}

type Transmission interface {
    ShiftGear(gear int)
}

type CarInterface interface {
    Engine
    Transmission
}
```

This means any type that implements `Start()`, `Stop()`, and `ShiftGear()` automatically implements `CarInterface`.

---

## **Real-World Example: Payment System**

```go
type Payment interface {
    Pay(amount float64)
}

type CreditCardPayment struct {}

func (c CreditCardPayment) Pay(amount float64) {
    fmt.Printf("Paid %.2f using Credit Card\n", amount)
}

type PayPalPayment struct {}

func (p PayPalPayment) Pay(amount float64) {
    fmt.Printf("Paid %.2f using PayPal\n", amount)
}
```

### **Usage**
```go
func main() {
    var payment1 Payment = CreditCardPayment{}
    payment1.Pay(100.50)
    
    var payment2 Payment = PayPalPayment{}
    payment2.Pay(200.75)
}
```

### **Output:**
```
Paid 100.50 using Credit Card
Paid 200.75 using PayPal
```