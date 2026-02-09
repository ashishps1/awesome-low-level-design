# Encapsulation in Rust (Modules & Visibility)

## Introduction

**Encapsulation** is one of the four fundamental principles of Object-Oriented Programming (OOP). It is the practice of **bundling data (variables) and methods** into a single unit while restricting direct access to the internal details.

**Does Rust support Encapsulation?**
Yes, but it works differently than Java.
1.  **Java:** Uses classes and access modifiers (`private`, `protected`, `public`) to hide data.
2.  **Rust:** Uses **Modules** (`mod`) and the `pub` keyword. Encapsulation boundaries are set at the *Module* level, not the *Struct* level.

## **What is Encapsulation?**

Encapsulation means **wrapping** data and code together and restricting access.

### **Key Benefits of Encapsulation**
-   **Data Protection**: Prevents external code from corrupting internal state (e.g., negative bank balance).
-   **Modularity**: Changes to internal logic (like how interest is calculated) don't break the code that uses it.
-   **Interface Clarity**: Users only interact with `pub` methods, ignoring the complex details inside.

---

## **Encapsulation Using Visibility Modifiers (`pub`)**

In Java, you have `private`, `protected`, `public`, and package-private.
In Rust, everything is **private by default**.

-   **Private (Default):** Accessible only within the current module (and its sub-modules).
-   **`pub`:** Accessible from outside the module.
-   **`pub(crate)`:** Accessible anywhere inside the same project (crate), but not by external users.

### **Example: Encapsulation with Modules**

```rust
// We define a module to create a privacy boundary
mod bank {
    pub struct BankAccount {
        pub owner: String, // Public: Anyone can read/write
        balance: f64,      // Private: Only this 'bank' module can see it
    }

    impl BankAccount {
        pub fn new(owner: &str, balance: f64) -> Self {
            BankAccount {
                owner: owner.to_string(),
                balance,
            }
        }

        pub fn get_balance(&self) -> f64 {
            self.balance
        }
    }
}

fn main() {
    let account = bank::BankAccount::new("Alice", 1000.0);
    
    // Allowed: 'owner' is pub
    println!("{}", account.owner);

    // ERROR: 'balance' is private!
    // println!("{}", account.balance); 
}

```

**Why Use Encapsulation?**

* It ensures you cannot accidentally set `balance = -500.0`. You *must* go through a method that validates the input.

---

## **Encapsulation Using Getters and Setters**

Since Rust fields are often private, we access them using methods.

**Rust Idiom:**

* **Getter:** naming convention is `field_name()`, not `get_field_name()`.
* **Setter:** naming convention is `set_field_name()`.

### **Example: Getters and Setters in Rust**

```rust
pub struct Employee {
    name: String,
    age: u8,
}

impl Employee {
    // Setter
    pub fn set_age(&mut self, age: u8) {
        if age > 18 {
            self.age = age;
        } else {
            println!("Age must be greater than 18");
        }
    }

    // Getter (Note: no 'get_' prefix)
    pub fn age(&self) -> u8 {
        self.age
    }
}

```

---

## **Encapsulation and Data Hiding**

We hide implementation details so the user doesn't need to worry about complex validation logic.

### **Example: Hiding Implementation Details**

```rust
mod finance {
    pub struct Account {
        balance: f64,
    }

    impl Account {
        pub fn new(balance: f64) -> Self {
            Account { balance }
        }

        // Private helper method (Not 'pub', so invisible outside)
        fn validate(&self, amount: f64) -> bool {
            amount > 0.0 && amount <= self.balance
        }

        // Public API
        pub fn withdraw(&mut self, amount: f64) {
            if self.validate(amount) {
                self.balance -= amount;
                println!("Withdrawal Successful: {}", amount);
            } else {
                println!("Invalid transaction");
            }
        }
    }
}

```

**Why Hide Data?**

* **Safety:** The `validate` logic cannot be bypassed by external code.
* **Simplicity:** The user just calls `withdraw`; they don't need to know *how* validation works.

---

## **Real-World Example: Payment System**

A common real-world use case is processing payments where sensitive data (like card numbers) should never be exposed directly.

```rust
mod payment_system {
    pub struct CreditCard {
        number: String, // Private!
        amount: f64,
    }

    impl CreditCard {
        pub fn new(number: &str, amount: f64) -> Self {
            CreditCard {
                number: CreditCard::mask(number), // Internal logic
                amount,
            }
        }

        // Private utility function
        fn mask(real_number: &str) -> String {
            let last_4 = &real_number[real_number.len()-4..];
            format!("****-****-****-{}", last_4)
        }

        pub fn process(&self) {
            println!("Charging {} to card {}", self.amount, self.number);
        }
    }
}

```

---

## 📚 New Terminology (Java vs. Rust)

| Term | Java Equivalent | Detailed Explanation |
| --- | --- | --- |
| **Module (`mod`)** | Package / Class | In Rust, the boundary for privacy is the **Module**, not the Class. Private items in a struct are visible to everything in the same `mod`. |
| **`pub`** | `public` | Makes an item visible to other modules. |
| **(No modifier)** | `private` / package-private | By default, everything in Rust is private. It is only visible within the current module and its children. |
| **`pub(crate)`** | N/A | Visible to the entire project (crate), but hidden from anyone who uses your project as a library. |
| **`&mut self`** | `this` (implicitly mutable) | In Java, you can always modify `this`. In Rust, you must explicitly say `&mut self` if a method changes data (like a Setter). |
| **Getter convention** | `getName()` | In Rust, we simply use the field name: `name()`. |



