# Polymorphism in Rust (Generics & Trait Objects)

## Introduction

**Polymorphism** is one of the four fundamental principles of Object-Oriented Programming (OOP). It allows a single interface to be used for different types of objects, enabling **flexibility**, **scalability**, and **code reuse**.

In Java, polymorphism is often divided into "Overloading" and "Overriding."
In Rust, we classify it based on **when** the decision is made:
1.  **Compile-time Polymorphism (Static Dispatch):** Using **Generics**. fast, zero-cost.
2.  **Run-time Polymorphism (Dynamic Dispatch):** Using **Trait Objects** (`dyn`). Flexible, like Java.



## **What is Polymorphism?**

**Polymorphism** means "many forms." It allows a function or method to operate on different types.

### **Key Benefits of Polymorphism**
-   **Code Reusability**: Write a single function that works for multiple types.
-   **Scalability**: Add new types with minimal code changes.
-   **Maintainability**: Reduce complexity and improve code clarity.

---

## **1. Compile-Time Polymorphism (Static Dispatch)**

In Java, this is Method Overloading. Rust **does not** support traditional Method Overloading (same name, different args).

Instead, Rust uses **Generics**.
When you write a generic function, the compiler generates a unique copy of that function for *every concrete type* you use. This is called **Monomorphization**.

### **Example of Generics (Static Dispatch)**

```rust
trait Addable {
    fn add(&self, other: i32) -> i32;
}

struct Number { value: i32 }
impl Addable for Number {
    fn add(&self, other: i32) -> i32 { self.value + other }
}

// GENERIC FUNCTION:
// The compiler creates separate machine code for every type 'T' used.
// It effectively converts 'static_add(num)' into 'static_add_Number(num)'.
fn static_add<T: Addable>(item: T, extra: i32) -> i32 {
    item.add(extra)
}

```

**Why Use Generics?**

* **Zero Runtime Cost:** The decision of which function to call happens during compilation.
* **Type Safety:** Errors are caught at compile time.

---

## **2. Run-Time Polymorphism (Dynamic Dispatch)**

This corresponds to Java's Method Overriding. The exact method to be called is determined **at runtime**.

In Rust, we achieve this using **Trait Objects**.
A Trait Object involves a pointer (like `&` or `Box`) combined with the `dyn` keyword (e.g., `Box<dyn Animal>`). This tells Rust: *"I don't know the exact size of this object, so look up its methods in a vtable (virtual table) at runtime."*

### **Example of Trait Objects**

```rust
trait Animal {
    fn make_sound(&self);
}

struct Dog;
impl Animal for Dog { fn make_sound(&self) { println!("Bark"); } }

struct Cat;
impl Animal for Cat { fn make_sound(&self) { println!("Meow"); } }

fn main() {
    // We store different types in the same list using Box<dyn Animal>
    let animals: Vec<Box<dyn Animal>> = vec![
        Box::new(Dog),
        Box::new(Cat),
    ];

    for animal in animals {
        // The specific method is decided dynamically at runtime via vtable lookup
        animal.make_sound();
    }
}

```

**Why Use Trait Objects?**

* Enables **heterogeneous collections** (storing different types in one list).
* Supports **polymorphic behavior** where the type isn't known until runtime.

---

## **Real-World Example: Payment System**

A common real-world use case is **payment processing**, where we want to process payments regardless of the method (Credit Card, PayPal, etc.).

```rust
trait Payment {
    fn pay(&self, amount: f64);
}

struct CreditCard;
impl Payment for CreditCard {
    fn pay(&self, amount: f64) { println!("Paid with Card: {}", amount); }
}

struct PayPal;
impl Payment for PayPal {
    fn pay(&self, amount: f64) { println!("Paid with PayPal: {}", amount); }
}

// Accepts any type that implements Payment at runtime
fn process(method: &dyn Payment, amount: f64) {
    method.pay(amount);
}

```

---

## 📚 New Terminology (Detailed Explanation)

Since you are moving from Java to Rust, here are the specific new terms introduced in this topic:

| Term | Java Equivalent | Detailed Explanation |
| --- | --- | --- |
| **Generics (`<T>`)** | Generics | In Java, generics are "erased" at runtime (Type Erasure). In Rust, they are "filled in" at compile time (Monomorphization), making them much faster. |
| **Trait Bounds (`T: Animal`)** | `extends Interface` | A rule that says "I will accept any Type T, *as long as* it implements the Animal Trait." |
| **`dyn` Keyword** | Runtime Type | Short for "Dynamic". It tells the compiler: "I don't know the exact size of this object right now, so treat it as a generic object implementing this trait." |
| **Trait Object** | Interface Reference | A combination of a pointer to data and a pointer to methods (vtable). Example: `Box<dyn Animal>` or `&dyn Animal`. |
| **Static Dispatch** | N/A (Optimization) | The compiler decides *exactly* which function to call while compiling. This is the default in Rust. |
| **Dynamic Dispatch** | Method Overriding | The program decides which function to call while running. This is the default in Java. |
| **Monomorphization** | N/A | The fancy word for the compiler copying your generic code for every concrete type you use. |
| **VTable** | Virtual Method Table | A hidden table of function pointers used to look up methods at runtime for dynamic dispatch. |

---

