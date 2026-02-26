# Inheritance in Rust (Traits & Composition)

## Introduction

**Inheritance** is one of the core principles of Object-Oriented Programming (OOP). It allows a class (subclass or child class) to acquire the properties and behaviors of another class (superclass or parent class). This promotes **code reuse**, **scalability**, and **maintainability**.

**Does Rust support Inheritance?**
No, Rust does **not** support classical inheritance (e.g., `class Dog extends Animal`). Rust takes a different approach called **Composition over Inheritance**.

Instead of inheriting fields and methods from a parent class, Rust uses:
1.  **Traits:** To share behavior (methods).
2.  **Composition:** To share state (data/fields).

## **What is Inheritance?**

In traditional OOP (Java), **Inheritance** is a mechanism where a child class derives properties and behaviors from a parent class.

In Rust, since we cannot use `extends`, we achieve the same functionality by:
- **Implementing Traits:** A struct implements a specific trait to gain its behavior.
- **Embedding Structs:** A struct contains another struct as a field to reuse its data.

### **Key Benefits of the Rust Approach**

- **Avoids the "Diamond Problem":** Multiple inheritance of state is impossible, preventing complex conflicts.
- **Explicit Dependencies:** You clearly see what data a struct depends on (it's listed in the fields).
- **Flexible Behavior:** You can implement many traits for a single struct, offering more flexibility than single inheritance.

---

## **How to Implement "Inheritance" in Rust**

Since Rust does not have `extends`, we use **Traits** for behavior and **Composition** for data.

### **Step 1: Create a Parent Behavior (Trait)**

The parent trait contains common method signatures and default implementations.

```rust
// Parent Trait (Behavior)
pub trait Animal {
    fn name(&self) -> &String; // Abstract method (getter)

    // Default implementation (Shared Behavior)
    fn eat(&self) {
        println!("{} is eating...", self.name());
    }
}

```

### **Step 2: Create a Child Struct using `impl`**

The child struct implements the properties and methods of the parent trait.

```rust
// Child Struct (Data)
pub struct Dog {
    pub name: String,
    pub breed: String,
}

// Implementing the Trait (The "Inheritance" link)
impl Animal for Dog {
    fn name(&self) -> &String {
        &self.name
    }
    
    // 'eat()' is inherited automatically from the Trait
}

impl Dog {
    // Dog-specific method
    fn bark(&self) {
        println!("{} is barking...", self.name);
    }
}

```

### **Step 3: Use the Child Struct**

Now, let's create an object and use the inherited methods.

```rust
fn main() {
    let my_dog = Dog { 
        name: "Buddy".to_string(),
        breed: "Golden Retriever".to_string(),
    };
    
    // Inherited from Animal trait
    my_dog.eat(); 
    
    // Defined in Dog impl block
    my_dog.bark(); 
}

```

### **Output:**

```
Buddy is eating...
Buddy is barking...

```

---

## **Types of "Inheritance" Patterns in Rust**

Although Rust lacks class inheritance, we can replicate standard OOP patterns.

### **1. Single Inheritance (Trait Implementation)**

A struct implements a single trait.

```rust
trait Parent {
    fn show(&self) {
        println!("This is the parent behavior");
    }
}

struct Child;

impl Parent for Child {} // Inherits 'show'

```

### **2. Multilevel Inheritance (Supertraits)**

A trait inherits from another trait. This is called a **Supertrait**.

```rust
trait Grandparent {
    fn show_grand(&self);
}

// Parent requires Grandparent to be implemented first
trait Parent: Grandparent {
    fn show_parent(&self);
}

struct Child;

// You must implement both
impl Grandparent for Child { 
    fn show_grand(&self) { println!("Grandparent"); } 
}
impl Parent for Child { 
    fn show_parent(&self) { println!("Parent"); } 
}

```

### **3. Hierarchical Inheritance**

A single parent trait is implemented by multiple different structs.

```rust
trait Entity {
    fn id(&self) -> u32;
}

struct User { id: u32 }
impl Entity for User { fn id(&self) -> u32 { self.id } }

struct Product { id: u32 }
impl Entity for Product { fn id(&self) -> u32 { self.id } }

```

---

## **Method Overriding in Rust**

Method overriding allows a struct to **redefine** a default method provided by a Trait.

```rust
trait Animal {
    fn make_sound(&self) {
        println!("Generic Animal Sound");
    }
}

struct Dog;

impl Animal for Dog {
    // Overriding the default method
    fn make_sound(&self) {
        println!("Dog barks! 🐶");
    }
}

```

### **Usage**

```rust
fn main() {
    let my_animal = Dog;
    my_animal.make_sound(); // Runs overridden version
}

```

### **Output:**

```
Dog barks! 🐶

```

---

## **The `super` Concept in Rust (Accessing Parent)**

In Java, `super` calls the parent class. In Rust, we use **Composition** to access "parent" data explicitly.

1. **Composition:** Embedding one struct inside another.
2. **Delegation:** Calling the inner struct's methods.

```rust
// The "Parent" Data
struct Organism {
    age: u8,
}

impl Organism {
    fn breathe(&self) { println!("Breathing..."); }
}

// The "Child" Struct
struct Dog {
    organism: Organism, // Composition (Has-a)
}

impl Dog {
    fn breathe(&self) {
        // Explicitly calling the "Parent" (inner struct)
        self.organism.breathe(); 
        println!("...and panting!");
    }
}

```

### **Summary Table**

| Concept | Java (Inheritance) | Rust (Idiomatic) |
| --- | --- | --- |
| **Relationship** | `Dog extends Animal` | `Dog implements Animal` (Trait) |
| **Data Sharing** | Inherited automatically | Composition (`dog.animal.field`) |
| **Method Sharing** | Inherited from Parent Class | Default Trait Methods |
| **Overriding** | `@Override` | `impl Trait` block |
| **Philosophy** | **Is-a** relationship | **Has-a** & **Can-do** relationship |


