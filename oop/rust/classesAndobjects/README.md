# Classes and Objects

Classes and objects form the foundation of Object-Oriented Programming (OOP).

## What is a Class?

In traditional OOP languages (like Java/C++), a **Class** is a blueprint that bundles data (attributes) and behavior (methods) together.

**Rust is different.** It separates these two concepts:
1.  **Data** is defined in a `struct`.
2.  **Behavior** is defined in an `impl` (implementation) block.

### Defining a Class (Struct + Impl) in Rust

To define the equivalent of a class in Rust, we use the `struct` keyword for the data layout and the `impl` keyword to define methods.

Here's the `Car` example translated to idiomatic Rust:

```rust
// 1. The Blueprint (Data only)
// We use 'pub' to make the struct and fields accessible to other modules.
pub struct Car {
    // Attributes
    pub color: String,
    pub make: String,
    pub model: String,
    pub year: u32,
}

// 2. The Behavior (Methods)
impl Car {
    // Constructor-like function (Associated Function)
    // Rust does not have a 'new' keyword. We create a static function typically named 'new'.
    pub fn new(color: String, make: String, model: String, year: u32) -> Self {
        Car {
            color, // Shorthand initialization (same as color: color)
            make,
            model,
            year,
        }
    }

    // Method to display car details
    // '&self' is a reference to the current object instance (like 'this' in Java)
    pub fn display_info(&self) {
        println!("Car Make: {}", self.make);
        println!("Car Model: {}", self.model);
        println!("Car Year: {}", self.year);
        println!("Car Color: {}", self.color);
    }
}
```

### 🧠 New Rust Terminology
* **`struct`**: Defines the "shape" of the object (the fields).
* **`impl`**: A block where we define functions and methods for a specific struct.
* **`&self`**: A reference to the instance itself. It means "read-only access to my own data". It is equivalent to `this` in Java.
* **Associated Function (`new`)**: Functions defined inside `impl` that do **not** take `self`. They are like `static` methods in Java. We use them as constructors.

---

## What is an Object?

An object is an **instance** of a struct. When you create an instance, you are allocating memory for that specific blueprint and filling it with real data.

### Creating Objects in Rust

In Rust, we don't use the `new` keyword to instantiate. Instead, we call the associated function we created (`Car::new`) or initialize the struct directly.

Here's how you can instantiate objects from the `Car` struct:

```rust
fn main() {
    // Creating an object (Instance) of the Car struct
    // We use "::" to call static methods (associated functions)
    // Note: We use .to_string() because "Red" is a string slice (&str), 
    // but our Struct expects an owned String.
    let car1 = Car::new(
        "Red".to_string(), 
        "Toyota".to_string(), 
        "Corolla".to_string(), 
        2020
    );

    let car2 = Car::new(
        "Blue".to_string(), 
        "Ford".to_string(), 
        "Mustang".to_string(), 
        2021
    );

    // Displaying information of each car
    // We use "." to call instance methods
    car1.display_info();
    println!("-----------------");
    car2.display_info();
}
```

### Key Differences from Java/Go
1.  **Instantiation**: No `new Car(...)`. We call `Car::new(...)` which is just a normal function we wrote.
2.  **Reference**: Variables (`car1`) **own** the data by default. In Java, variables are just references (pointers).
3.  **Strings**: We use `.to_string()` because string literals (`"Red"`) are string slices (`&str`), but our struct wants an owned `String`.


---

## 💡 Why Rust prefers Structs over Classes?

If you are coming from Java or C++, you might wonder: *"Why didn't Rust just add Classes?"*

The answer lies in **Composition over Inheritance**.

### 1. The "Banana in the Jungle" Problem
In traditional OOP (Classes), you often create deep inheritance hierarchies (`Animal` -> `Mammal` -> `Dog`).
Joe Armstrong (creator of Erlang) famously said:

> "The problem with object-oriented languages is they’ve got all this implicit environment that they carry around with them. **You wanted a banana but what you got was a gorilla holding the banana and the entire jungle.**"

In Rust:
* **Structs** are just data (The Banana).
* **Traits** are just behavior (Eating).
* You don't inherit the "Gorilla" just to get the "Banana."

### 2. No "Diamond Problem"
In languages like C++, allowing a class to inherit from two parents leads to conflicts (The Diamond Problem). Rust avoids this entirely because **Structs cannot inherit from other Structs**. You strictly use **Traits** (Interfaces) to share behavior, which is much cleaner and safer.

### 3. Better Memory Control
* **Classes** (in Java/Python) are usually references (pointers) to memory on the Heap. This is slower and causes "Garbage Collection" pauses.
* **Structs** (in Rust) are stored on the Stack by default. They are exactly the size of their data—no overhead, no hidden pointers. This makes Rust significantly faster.

### Summary
Rust replaces **"Is-A"** relationships (Inheritance) with **"Has-A"** and **"Can-Do"** relationships (Composition and Traits).

* **Bad (OOP):** A `Car` **is a** `Vehicle`. (Forces rigid hierarchy)
* **Good (Rust):** A `Car` **has** `Engine` data (Struct) and **can** `drive` (Trait).