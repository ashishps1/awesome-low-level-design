# Aggregation in Rust (References & Lifetimes)

## Introduction

**Aggregation** is a specific type of association in Object-Oriented Programming (OOP) representing a **"Has-A"** relationship.
* **Crucial Distinction:** The lifecycle of the contained object (Child) is **independent** of the container object (Parent).
* **In plain English:** If the University closes down (is destroyed), the Professors do not die; they go home.

**Does Rust support Aggregation?**
Yes, but it is stricter than Java. In Rust, Aggregation is implemented using **References (`&T`)** and **Lifetimes (`'a`)**.



---

## **1. The Core Concept: Borrowing vs. Owning**

To understand Aggregation, you must understand Rust's memory model:

1.  **Composition (Strong):** The Parent **OWNS** the Child.
    * *Rust:* `struct Parent { child: Child }`
    * *Result:* If Parent dies, Child dies immediately.
2.  **Aggregation (Weak):** The Parent **BORROWS** the Child.
    * *Rust:* `struct Parent<'a> { child: &'a Child }`
    * *Result:* Parent holds a pointer. If Parent dies, the Child is unaffected because the Parent never owned it.

---

## **2. The "Lifetime" Problem (`'a`)**

This is the most unique part of Rust. If a struct holds a reference, the borrow checker will reject invalid lifetimes at compile time:
> *"What if the University holds a pointer to a Professor, but the Professor has already been deleted? The University would be pointing to garbage memory!"*

To prevent this, we use **Lifetime Annotations (`'a`)**.

```rust
// <'a> reads as: "This struct lives for a duration called 'a"
struct University<'a> {
    // This reference must live AT LEAST as long as 'a
    professor: &'a Professor,
}

```

**What this tells the compiler:**
*"I promise that the `Professor` will stay alive longer than (or at least as long as) the `University`."*

---

## **3. Code Implementation**

### **Step 1: The Independent Object**

The `Professor` owns its own data. It doesn't know about the University.

```rust
struct Professor {
    name: String,
}

```

### **Step 2: The Container (With Lifetimes)**

The `University` holds a **Reference** (`&`) to the Professor.

```rust
struct University<'a> {
    name: String,
    // Aggregation: We borrow the professor
    staff: Vec<&'a Professor>,
}

```

### **Step 3: Usage**

```rust
fn main() {
    // 1. Create the Child (Owner)
    let prof = Professor { name: "Dr. Smith".into() };

    {
        // 2. Create the Parent (Borrower)
        let mut uni = University { 
            name: "MIT".into(), 
            staff: vec![&prof] // Borrowing here
        }; 
        
        // uni is destroyed here...
    } 

    // 3. PROOF OF AGGREGATION:
    // The Professor is still alive!
    println!("{} is currently unemployed but alive.", prof.name);
}

```

---

## **4. Advanced: Shared Ownership (`Rc<T>`)**

Sometimes, you don't know who will die first. Maybe the Professor belongs to 3 Universities at once.
For this, Rust uses **Reference Counting (`Rc`)**.

* **`Rc<T>`**: A smart pointer that keeps track of how many owners exist.
* The object is only deleted when the **count reaches 0**.

```rust
use std::rc::Rc;

struct Company {
    // Shared Ownership Aggregation
    employee: Rc<Employee>,
}

```

---

## **Comparison: Aggregation vs Composition**

| Feature | Aggregation (Weak) | Composition (Strong) |
| --- | --- | --- |
| **Relationship** | **"Uses a"** / **"Has access to"** | **"Consists of"** |
| **Rust Syntax** | `&'a T` (Reference) | `T` (Direct Value) |
| **Ownership** | **Borrowed** (Parent does not own) | **Owned** (Parent owns Child) |
| **Lifecycle** | **Independent** (Child survives Parent) | **Dependent** (Child dies with Parent) |
| **Drop Rule** | Dropping Parent **does nothing** to Child. | Dropping Parent **drops** Child. |

---

## 📚 New Terminology

| Term | Detailed Explanation |
| --- | --- |
| **Lifetime (`'a`)** | A generic parameter that restricts how long a Reference is valid. It ensures a struct never points to dead memory. |
| **Borrow Checker** | The part of the Rust compiler that enforces Aggregation rules. It ensures the "Child" lives longer than the "Parent". |
| **Dangling Pointer** | A pointer that points to invalid memory. Rust's Aggregation rules exist specifically to prevent this. |
| **`Vec<&T>`** | A Vector that stores *addresses* of objects, not the objects themselves. |



