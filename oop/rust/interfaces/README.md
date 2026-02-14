# Interfaces in Rust (Traits)

## Introduction

In Object-Oriented Programming (OOP), an **Interface** is a crucial concept that defines a contract for types to follow. It allows multiple types to share a common structure while enforcing certain behaviors. Interfaces are widely used in Java to achieve **abstraction, polymorphism, and loose coupling**.

In Rust, this concept is called a **Trait**.

A Trait defines functionality a particular type has and can share with other types. We can use traits to define shared behavior in an abstract way.

## What is a Trait?

A **Trait** in Rust is a collection of method signatures that a type can implement. It defines a contract that the implementing types must adhere to.

### **Key Characteristics of Traits**
- Defines a **contract** of behavior (methods) that implementing types must fulfill.
- **Strict Separation:** Unlike Java where you write `class Car implements Vehicle`, in Rust, you define the `struct Car` (data) in one block and the `impl Vehicle for Car` (logic) in a completely separate block.
- **Explicit Context:** Rust methods require you to explicitly say if they use the object's data by passing `&self` as the first argument.
- Supports **Multiple Trait Implementation** (Rust's version of multiple inheritance).
- Can contain **Default Implementations** (methods with code) and **Associated Functions** (static methods).

---

## **Defining and Implementing a Trait**

### **Step 1: Define the Trait**
To define a trait (interface), use the `trait` keyword.

```rust
// Defining a trait 'Vehicle'
// This is the "Contract"
pub trait Vehicle {
    fn start(&self); // Abstract method (no body)
    fn stop(&self);  // Abstract method (no body)
}

```

### **Step 2: Implement the Trait**

In Java, you implement the interface inside the class. In Rust, you use the `impl [Trait] for [Type]` syntax.

```rust
// 1. Define the Data (Struct)
pub struct Car {
    pub brand: String,
}

// 2. Implement the Behavior (Trait) separately
// "Implement the Vehicle Trait FOR the Car Struct"
impl Vehicle for Car {
    fn start(&self) {
        println!("{} is starting... 🚗", self.brand);
    }

    fn stop(&self) {
        println!("{} is stopping... 🛑", self.brand);
    }
}

```

### **Step 3: Using the Implemented Struct**

We create an instance of the struct and call the trait methods.

```rust
fn main() {
    let my_car = Car { brand: "Toyota".to_string() };

    // We can call methods just like in Java
    my_car.start();
    my_car.stop();
}

```

**Output:**

```text
Toyota is starting... 🚗
Toyota is stopping... 🛑

```

---

## **Multiple Traits (Composition)**

Java uses interfaces to solve the "Multiple Inheritance" problem. Rust does the same. A single struct can implement as many traits as necessary.

```rust
// First Trait
trait Flyable {
    fn fly(&self);
}

// Second Trait
trait Drivable {
    fn drive(&self);
}

// The Struct
struct FlyingCar;

// Implement Trait 1
impl Flyable for FlyingCar {
    fn fly(&self) {
        println!("FlyingCar is flying... ✈️");
    }
}

// Implement Trait 2
impl Drivable for FlyingCar {
    fn drive(&self) {
        println!("FlyingCar is driving... 🚙");
    }
}

```

### **Usage**

```rust
fn main() {
    let my_vehicle = FlyingCar;
    
    // The same object can do both actions
    my_vehicle.fly();
    my_vehicle.drive();
}

```

**Output:**

```text
FlyingCar is flying... ✈️
FlyingCar is driving... 🚙

```

---

## **Default and Associated Functions**

Rust traits are powerful. They can have **Default Implementations** (pre-written logic) and **Associated Functions** (static utility methods).

### **Default Implementations**

Just like Java's `default` keyword, Rust allows you to provide a method body in the trait itself. If a struct doesn't override it, the default logic is used.

```rust
trait Animal {
    fn sound(&self); // Abstract method (Must be implemented)

    // Default method (Optional to implement)
    fn sleep(&self) {
        println!("Sleeping... 💤");
    }
}

struct Dog;

impl Animal for Dog {
    fn sound(&self) {
        println!("Dog barks! 🐶");
    }
    // We don't implement sleep(), so Dog gets the default behavior.
}

```

### **Associated Functions (Static Methods)**

If a function inside a trait does **not** take `&self`, it acts like a Java `static` method. It belongs to the *Type*, not the *Instance*.

```rust
trait MathOperations {
    // No '&self' here, so this is a "Static Method"
    fn add(a: i32, b: i32) -> i32 {
        a + b
    }
}

// We need a dummy struct to attach this trait to
struct Calculator;
impl MathOperations for Calculator {}

```

### **Usage**

```rust
fn main() {
    let my_dog = Dog;
    my_dog.sound();
    my_dog.sleep(); // Calls default implementation

    // Call static method using the Type name (::)
    let result = Calculator::add(5, 10);
    println!("Sum: {}", result);
}

```

**Output:**

```text
Dog barks! 🐶
Sleeping... 💤
Sum: 15

```

---

## **Real-World Example: Payment System**

This example demonstrates **Polymorphism**. We want to write a function that can accept *any* payment method, whether it's a Credit Card or PayPal.

```rust
// The Contract
trait Payment {
    fn pay(&self, amount: f64);
}

// Struct 1: Credit Card
struct CreditCard;
impl Payment for CreditCard {
    fn pay(&self, amount: f64) {
        println!("Paid ${:.2} using Credit Card 💳", amount);
    }
}

// Struct 2: PayPal
struct PayPal;
impl Payment for PayPal {
    fn pay(&self, amount: f64) {
        println!("Paid ${:.2} using PayPal 🅿️", amount);
    }
}

```

### **Usage**

```rust
fn main() {
    let card = CreditCard;
    let paypal = PayPal;

    // The same function works for different types!
    // We can use references to the trait object
    let payments: Vec<&dyn Payment> = vec![&card, &paypal];

    for payment in payments {
        payment.pay(100.50);
    }
}

```

**Output:**

```text
Paid $100.50 using Credit Card 💳
Paid $100.50 using PayPal 🅿️

```

---

## 📚 New Terminology (Detailed Explanation)

Since you are moving from Java to Rust, here are the specific new terms introduced in this topic:

| Term | Java Equivalent | Detailed Explanation |
| --- | --- | --- |
| **Trait** | `Interface` | A set of method signatures. It defines *what* an object can do, but not *how* it does it. |
| **`impl Trait for Type`** | `implements` | In Rust, you don't declare implementations inside the struct definition. You use a separate `impl` block to bind the Trait to the Struct. This allows you to add traits to types you didn't even create! |
| **`&self`** | `this` | In Java, `this` is hidden/implicit. In Rust, you must **explicitly** pass `&self` as the first argument to any method that works on an instance. If you forget `&self`, Rust thinks it is a static method. |
| **Associated Function** | `static` method | A function defined inside a trait/struct that does **not** have `&self`. It is called using `::` (e.g., `Calculator::add`) instead of `.` (dot). |
| **`dyn Trait`** | Polymorphism | Short for "Dynamic Dispatch". It tells the compiler: "I don't know the exact size of this object at compile time, but I know it implements this Trait." Used when storing different types in the same list (like `Vec<&dyn Payment>`). |
