# Polymorphism in Object-Oriented Programming (OOP) in Golang

## Introduction

**Polymorphism** is one of the fundamental principles of Object-Oriented Programming (OOP). It allows a single interface to be used for different types of objects, enabling **flexibility**, **scalability**, and **code reuse**.

Polymorphism in Go is primarily achieved using **interfaces**, as Go does not support method overloading or classical inheritance like Java or C#.

---

## **What is Polymorphism?**

**Polymorphism** means "many forms." It allows a method, function, or object to behave differently based on the context. Polymorphism enables **dynamic method resolution** and **method flexibility**, making applications easier to extend and maintain.

### **Key Benefits of Polymorphism**
- **Code Reusability**: Write a single interface that works for multiple types.
- **Scalability**: Add new functionalities with minimal code changes.
- **Maintainability**: Reduce complexity and improve code clarity.

---

## **Polymorphism using Interfaces in Go**

Go achieves polymorphism through **interfaces**. An interface defines a set of method signatures, and any type that implements those methods satisfies the interface.

### **Example: Polymorphism using Interfaces**

```go
package main

import "fmt"

// Define an interface
type Animal interface {
    MakeSound()
}

// Implementing the interface in Dog
type Dog struct{}

func (d Dog) MakeSound() {
    fmt.Println("Dog barks")
}

// Implementing the interface in Cat
type Cat struct{}

func (c Cat) MakeSound() {
    fmt.Println("Cat meows")
}

func main() {
    var animal Animal
    
    animal = Dog{}
    animal.MakeSound()
    
    animal = Cat{}
    animal.MakeSound()
}
```

### **Output:**
```
Dog barks
Cat meows
```

**Why Use Interfaces for Polymorphism?**
- Provides a flexible and modular design.
- Encourages dependency inversion and loose coupling.
- Allows multiple types to satisfy the same interface.

---

## **Using Polymorphism with Functions**

A common use of polymorphism in Go is passing different types to the same function.

```go
package main

import "fmt"

// Define an interface
type Vehicle interface {
    Start()
}

// Implementing the interface in Car
type Car struct{}

func (c Car) Start() {
    fmt.Println("Car is starting...")
}

// Implementing the interface in Bike
type Bike struct{}

func (b Bike) Start() {
    fmt.Println("Bike is starting...")
}

// Function that takes any Vehicle
func StartVehicle(v Vehicle) {
    v.Start()
}

func main() {
    car := Car{}
    bike := Bike{}
    
    StartVehicle(car)
    StartVehicle(bike)
}
```

### **Output:**
```
Car is starting...
Bike is starting...
```

**Why Use Function Parameters for Polymorphism?**
- Allows flexible function behavior based on the type passed.
- Enhances code modularity and testability.

---

## **Real-World Example: Payment System**

A common real-world use case of polymorphism is in **payment processing**.

```go
package main

import "fmt"

// Define an interface
type Payment interface {
    Pay(amount float64)
}

// Implementing the interface in CreditCardPayment
type CreditCardPayment struct{}

func (c CreditCardPayment) Pay(amount float64) {
    fmt.Printf("Paid %.2f using Credit Card\n", amount)
}

// Implementing the interface in PayPalPayment
type PayPalPayment struct{}

func (p PayPalPayment) Pay(amount float64) {
    fmt.Printf("Paid %.2f using PayPal\n", amount)
}

func main() {
    var payment Payment
    
    payment = CreditCardPayment{}
    payment.Pay(100.50)
    
    payment = PayPalPayment{}
    payment.Pay(200.75)
}
```

### **Output:**
```
Paid 100.50 using Credit Card
Paid 200.75 using PayPal
```

**Why Use Polymorphism in Payment Systems?**
- Allows new payment methods to be added **without modifying existing code**.
- Provides a **flexible and scalable** design.
- Improves **code readability and maintainability**.