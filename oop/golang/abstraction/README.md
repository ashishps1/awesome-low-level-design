# Abstraction in Go

## Introduction

**Abstraction** is one of the four fundamental principles of Object-Oriented Programming (OOP). It allows you to hide **implementation details** while exposing only the necessary parts of an object. This helps in reducing complexity and increasing maintainability.

Unlike traditional OOP languages like Java or C++, **Golang does not support classes**. However, abstraction in Go is achieved using:
1. **Interfaces**
2. **Structs with Methods**

## **What is Abstraction?**

**Abstraction** means showing only the **essential details** and hiding the **implementation**. It allows programmers to focus on **what an object does** rather than **how it does it**.

### **Key Benefits of Abstraction**
- **Reduces complexity**: Hides unnecessary implementation details.
- **Increases code reusability**: Encourages the reuse of abstracted logic.
- **Improves maintainability**: Makes code easier to manage and update.
- **Enhances flexibility**: Enables polymorphic behavior in Go.

---

## **1. Abstraction Using Interfaces**

An **interface** in Go defines a set of methods that a type must implement. This allows different types to be treated uniformly.

### **Example: Interface in Golang**

```go
package main

import "fmt"

// Defining an interface
type Vehicle interface {
    Start()
    DisplayBrand()
}

// Concrete implementation of Vehicle (Car)
type Car struct {
    brand string
}

func (c Car) Start() {
    fmt.Println("Car is starting...")
}

func (c Car) DisplayBrand() {
    fmt.Println("Brand:", c.brand)
}

func main() {
    var myCar Vehicle = Car{"Toyota"}
    myCar.DisplayBrand()
    myCar.Start()
}
```

### **Output:**
```
Brand: Toyota
Car is starting...
```

**Why Use Interfaces?**
- Promotes **abstraction** by defining behaviors without implementation details.
- Allows multiple types to adhere to the same contract.
- Supports **polymorphism** by enabling different implementations to be used interchangeably.

---

## **2. Abstraction Using Structs with Methods**

Go does not have traditional classes, but **structs with methods** provide an alternative way to achieve abstraction.

### **Example: Abstracting Animal Behavior**

```go
package main

import "fmt"

// Abstract behavior using an interface
type Animal interface {
    MakeSound()
}

// Concrete struct (Dog)
type Dog struct {}

func (d Dog) MakeSound() {
    fmt.Println("Dog barks")
}

// Concrete struct (Cat)
type Cat struct {}

func (c Cat) MakeSound() {
    fmt.Println("Cat meows")
}

func main() {
    var myAnimal Animal
    
    myAnimal = Dog{}
    myAnimal.MakeSound()
    
    myAnimal = Cat{}
    myAnimal.MakeSound()
}
```

### **Output:**
```
Dog barks
Cat meows
```

**Why Use Structs with Methods?**
- Provides a clean and flexible way to define behavior.
- Makes it easy to extend functionality.
- Improves code readability and organization.

---

## **Real-World Example: Payment System**

Abstraction is widely used in real-world applications, such as payment processing.

### **Example: Payment System with Abstraction**

```go
package main

import "fmt"

// Payment interface
type Payment interface {
    Pay(amount float64)
}

// CreditCardPayment struct

type CreditCardPayment struct {}

func (c CreditCardPayment) Pay(amount float64) {
    fmt.Printf("Paid %.2f using Credit Card\n", amount)
}

// PayPalPayment struct
type PayPalPayment struct {}

func (p PayPalPayment) Pay(amount float64) {
    fmt.Printf("Paid %.2f using PayPal\n", amount)
}

func main() {
    var payment Payment
    
    payment = CreditCardPayment{}
    payment.Pay(150.75)
    
    payment = PayPalPayment{}
    payment.Pay(200.50)
}
```

### **Output:**
```
Paid 150.75 using Credit Card
Paid 200.50 using PayPal
```

**Why Use Abstraction in Payment Systems?**
- Allows multiple payment methods without modifying existing code.
- Improves maintainability and scalability.
- Provides a **common contract** for different payment types.