# Abstraction in Rust

**Abstraction** is the design pattern of hiding complex implementation details and exposing only the necessary functionality to the user.

> **Simple Definition:** "Show what it does, hide how it does it."

---

## 🏗️ Prerequisites: The Building Blocks
Before understanding Abstraction in Rust, we must understand two fundamental concepts that replace "Classes" in other languages: **Structs** and **Traits**.

### 1. What is a Struct?
In Java/C++, a Class holds both data and methods. In Rust, data is separated.
A **Struct** is strictly for holding **Data**. It has no behavior on its own.

**Example:**
```rust
// Just data. No logic here.
struct CoffeeMachine {
    water_level: u32,
    beans: u32,
}
```

### 2. What is a Trait?
A **Trait** is Rust's version of an **Interface**. It defines **Behavior**.
It tells us *what* functionality an object must provide, but not *how* it does it.

**Example:**
```rust
// This is the "Contract" or "Interface"
trait Brewable {
    fn make_coffee(&self); // abstract method (no body)
}
```

### 3. What is `impl`?
The `impl` keyword is the glue. It implements the **Trait** (Behavior) for a specific **Struct** (Data).

---

## ☕ Abstraction: The Real-World Example
Let's apply these concepts to build a **Coffee Machine**.

### The Problem (Without Abstraction)
If we don't use abstraction, the user has to manually handle the machine's internal parts. This is dangerous and complex.

```rust
let mut machine = CoffeeMachine { water: 0, beans: 0 };

// BAD: User has to know how the machine works internally!
machine.water = 100;       // User manually filling water?
machine.beans = 50;        // User manually loading beans?
machine.grind_beans();     // User manually starting the grinder?
// This is too complex for a normal user.
```

### The Solution (With Abstraction)
We want to hide the grinding and heating logic. The user should only see one simple button: `brew()`.

#### Step 1: Define the Abstraction (The Interface)
We create a public Trait. This is the **only** thing the user needs to understand.

```rust
// PUBLIC: The user sees this.
pub trait CoffeeMaker {
    fn add_ingredients(&mut self);
    fn press_button(&mut self);
}
```

#### Step 2: Implement the Hidden Logic
We hide the complex steps (`grind_beans`, `heat_water`) inside private helper methods. The user cannot call these directly.

```rust
pub struct PremiumMachine {
    water: u32,
    beans: u32,
}

impl PremiumMachine {
    // PRIVATE: Internal logic (Hidden details)
    fn grind_beans(&self) {
        println!("Grinding beans... 🚜");
    }

    fn heat_water(&self) {
        println!("Heating water... 🔥");
    }
}

// CONNECTING THEM: Implementing the Public Trait
impl CoffeeMaker for PremiumMachine {
    fn add_ingredients(&mut self) {
        self.water = 100;
        self.beans = 50;
    }

    fn press_button(&mut self) {
        // The abstraction happens here!
        // One simple call triggers complex internal logic.
        self.grind_beans();
        self.heat_water();
        println!("Coffee is ready! ☕");
    }
}
```

---

## 🆚 Comparison: Rust vs. OOP Languages

Rust handles abstraction differently than Java or Python because it emphasizes **memory safety** and **separation of concerns**.

| Feature | Java / C++ / Python | Rust |
| :--- | :--- | :--- |
| **Container** | `Class` (Data + Methods together) | `Struct` (Data) + `impl` (Methods) separated |
| **Interface** | `interface` or `abstract class` | `trait` |
| **Hiding Data** | `private` / `protected` keywords | Struct fields are **private by default** to other modules |
| **Override** | `@Override` annotation | Explicit implementation of Trait methods |

---

## 🧠 Why is this useful?
1.  **Safety:** The user cannot accidentally change the `water_level` to a wrong value because the field is private.
2.  **Simplicity:** The user doesn't need to know *how* to grind beans; they just press the button.
3.  **Flexibility:** We can swap the `PremiumMachine` with a `CheapMachine`, and as long as they both implement the `CoffeeMaker` trait, the user code doesn't change.