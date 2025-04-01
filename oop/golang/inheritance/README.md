# Inheritance in Go

## Introduction

Unlike traditional OOP languages like Java and C++, **Go does not have classical inheritance**. Instead, Go achieves similar functionality using **struct embedding and interfaces**. This promotes **code reuse**, **composition over inheritance**, and **flexibility**.

---

## **What is Inheritance (or its Alternative in Go)?**

Go does not support class-based inheritance. Instead, it uses **struct embedding**, which allows one struct to include another, inheriting its fields and methods. This achieves a similar effect to traditional inheritance.

### **Key Benefits of Struct Embedding in Go**
- **Composition over Inheritance**: Encourages modular and maintainable design.
- **Code Reusability**: Allows reusing functionality without rigid class hierarchies.
- **Method Overriding**: Embedded structs’ methods can be overridden in the outer struct.
- **Polymorphism**: Achieved using interfaces rather than class-based inheritance.

---

## **How to Implement Inheritance-like Behavior in Go**

### **Step 1: Define a Parent Struct**
A struct in Go acts like a class with fields and methods.

```go
package main

import "fmt"

// Parent struct
type Animal struct {
    Name string
}

func (a Animal) Eat() {
    fmt.Println(a.Name, "is eating...")
}
```

### **Step 2: Embed the Parent Struct in a Child Struct**
The `Dog` struct embeds `Animal`, inheriting its fields and methods.

```go
// Child struct embedding Animal
type Dog struct {
    Animal // Embedding Animal struct
}

func (d Dog) Bark() {
    fmt.Println(d.Name, "is barking...")
}
```

### **Step 3: Use the Child Struct**
We create an instance of `Dog`, which has access to both `Animal` and `Dog` methods.

```go
func main() {
    myDog := Dog{Animal{Name: "Buddy"}}
    myDog.Eat()  // Inherited from Animal struct
    myDog.Bark() // Defined in Dog struct
}
```

### **Output:**
```
Buddy is eating...
Buddy is barking...
```

---

## **Multiple Inheritance Alternative: Composition**

Go does not support multiple inheritance, but struct embedding allows a struct to include multiple embedded structs.

```go
// First embedded struct
type Engine struct {
    Horsepower int
}

// Second embedded struct
type Wheels struct {
    Count int
}

// Car struct embedding Engine and Wheels
type Car struct {
    Engine
    Wheels
}
```

### **Usage**
```go
func main() {
    myCar := Car{Engine{200}, Wheels{4}}
    fmt.Println("Horsepower:", myCar.Horsepower)
    fmt.Println("Wheels:", myCar.Count)
}
```

### **Output:**
```
Horsepower: 200
Wheels: 4
```

---

## **Method Overriding in Struct Embedding**

A child struct can override an inherited method by defining a new method with the same name.

```go
type Animal struct {
    Name string
}

func (a Animal) Speak() {
    fmt.Println(a.Name, "makes a sound")
}

// Overriding Speak method
type Dog struct {
    Animal
}

func (d Dog) Speak() {
    fmt.Println(d.Name, "barks")
}
```

### **Usage**
```go
func main() {
    myDog := Dog{Animal{Name: "Buddy"}}
    myDog.Speak() // Calls the overridden method
}
```

### **Output:**
```
Buddy barks
```

---

## **Using Interfaces for Polymorphism**

In Go, **interfaces** allow struct-based polymorphism, similar to inheritance in OOP languages.

```go
type Animal interface {
    Speak()
}

type Dog struct {
    Name string
}

func (d Dog) Speak() {
    fmt.Println(d.Name, "barks")
}
```

### **Usage**
```go
func main() {
    var myAnimal Animal = Dog{Name: "Buddy"}
    myAnimal.Speak()
}
```

### **Output:**
```
Buddy barks
```

---

## **Real-World Example: Employee Management System**

```go
type Employee struct {
    Name   string
    Salary float64
}

func (e Employee) DisplayDetails() {
    fmt.Printf("Employee: %s, Salary: %.2f\n", e.Name, e.Salary)
}

type Manager struct {
    Employee
    Bonus float64
}

func (m Manager) DisplayDetails() {
    m.Employee.DisplayDetails()
    fmt.Printf("Bonus: %.2f\n", m.Bonus)
}
```

### **Usage**
```go
func main() {
    manager := Manager{Employee{Name: "Alice", Salary: 70000}, Bonus: 10000}
    manager.DisplayDetails()
}
```

### **Output:**
```
Employee: Alice, Salary: 70000.00
Bonus: 10000.00
```