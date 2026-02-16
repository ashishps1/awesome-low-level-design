# Composition in Rust (Ownership & Embedding)

## Introduction

**Composition** is a fundamental Object-Oriented Programming (OOP) principle that represents a **"Has-A"** relationship. It allows complex objects to be built from simpler ones.

In Rust, Composition is not just a design choice; it is the **primary way** to build data structures since Rust does not support Inheritance (`extends`).

**The Core Rule of Composition in Rust:**
When Struct A contains Struct B, **A owns B**.
* They share the same lifecycle.
* They share the same memory region.
* When A is dropped (freed), B is automatically dropped.

## **What is Composition?**

Composition is when one struct embeds another struct as a field.

### **Example: A Car and its Components**

In this example, a `Car` is composed of an `Engine`, `Wheels`, and `Transmission`.
Unlike Aggregation (where we used references `&`), here we use the concrete types directly. This means the `Car` takes full **ownership** of these components.

```rust
struct Engine { horsepower: u32 }

struct Car {
    // Direct Composition (Ownership)
    // The Engine actually lives INSIDE the Car struct in memory.
    engine: Engine, 
    model: String,
}

```

### **Memory Layout Difference**

* **Java (Reference):** `Car` -> (pointer) -> `Engine` (Heap)
* **Rust (Composition):** `Car` [ `Engine` data ... `model` data ] (Stack or Heap, but contiguous)

---

## **Why Prefer Composition Over Inheritance?**

Since Rust does not have Inheritance, Composition is the standard. However, even in languages that do have Inheritance, Composition is preferred because:

1. **Flexibility:** You can swap components (e.g., change a `GasEngine` to an `ElectricEngine`) without changing the `Car` class hierarchy.
2. **Encapsulation:** The wrapper (`Car`) controls exactly how the inner objects (`Engine`) are accessed. It can hide dangerous methods.
3. **Loose Coupling:** The `Car` doesn't need to know the internal details of how `Engine` works; it just calls public methods.

---

## **Composition with Traits (Polymorphism)**

To achieve the flexibility of Java interfaces (e.g., swapping different engine types), Rust uses **Trait Objects** inside `Box`.

Since different engines (Petrol vs Diesel) might have different sizes in memory, we cannot compose them directly on the stack if we want to swap them dynamically. We must put them in a `Box` (Pointer).

```rust
trait Engine {
    fn start(&self);
}

struct PetrolEngine;
impl Engine for PetrolEngine { ... }

struct Car {
    // Box<dyn Engine> allows us to hold ANY struct that implements Engine
    engine: Box<dyn Engine>,
}

```

---

## **Composition vs Aggregation (The "Drop" Difference)**

The most important detail in Rust is **Lifecycle**.

| Feature | Composition (Strong) | Aggregation (Weak) |
| --- | --- | --- |
| **Rust Syntax** | `struct A { b: B }` | `struct A<'a> { b: &'a B }` |
| **Ownership** | **Owned** (A owns B) | **Borrowed** (A borrows B) |
| **Memory** | B is stored *inside* A. | B is stored elsewhere; A points to it. |
| **Destruction** | If A dies, **B dies too.** | If A dies, **B lives on.** |

---

## 📚 New Terminology

| Term | Explanation |
| --- | --- |
| **Ownership** | The Rust rule that says a value can only have one owner. In composition, the container is the owner. |
| **`Box<T>`** | A smart pointer that stores data on the Heap. Required when composing Dynamic Trait Objects (`dyn Trait`) because their size is unknown at compile time. |
| **Contiguous Memory** | In Rust composition, fields are stored side-by-side in memory. This improves CPU cache performance compared to Java's scattered pointers. |
| **Delegate** | A pattern where the wrapper struct (Car) calls a method on the inner struct (Engine). `car.start()` simply calls `self.engine.start()`. |



