/*
 * ENCAPSULATION IN RUST
 *
 * Goal: Demonstrate Access Control, Data Hiding, and Modularity using Modules.
 */

// 1. ENCAPSULATION WITH MODULES (Access Modifiers)
// We define a module to simulate a separate file/package
mod bank {
    pub struct BankAccount {
        pub owner: String, // Public: Accessible everywhere
        balance: f64,      // Private: Accessible only inside 'mod bank'
    }

    impl BankAccount {
        pub fn new(owner: &str, balance: f64) -> Self {
            BankAccount {
                owner: owner.to_string(),
                balance,
            }
        }

        // Getter
        pub fn balance(&self) -> f64 {
            self.balance
        }

        // Setter (Mutating method)
        pub fn deposit(&mut self, amount: f64) {
            if amount > 0.0 {
                self.balance += amount;
                println!("Deposited: {:.2}", amount);
            } else {
                println!("Invalid deposit amount");
            }
        }
    }
}

// 2. GETTERS AND SETTERS (Idiomatic Rust)
mod hr {
    pub struct Employee {
        name: String,
        age: u8,
    }

    impl Employee {
        pub fn new(name: &str, age: u8) -> Self {
            Employee {
                name: name.to_string(),
                age,
            }
        }

        // Getter (Rust style: no 'get_' prefix)
        pub fn name(&self) -> &String {
            &self.name
        }

        // Setter
        pub fn set_age(&mut self, age: u8) {
            if age > 18 {
                self.age = age;
            } else {
                println!("Error: Age must be greater than 18");
            }
        }

        pub fn age(&self) -> u8 {
            self.age
        }
    }
}

// 3. REAL WORLD: PAYMENT PROCESSING (Data Hiding)
mod payment {
    pub struct Processor {
        card_number: String, // Private to keep secure
        amount: f64,
    }

    impl Processor {
        pub fn new(card_number: &str, amount: f64) -> Self {
            Processor {
                // We mask the data immediately upon creation
                card_number: Processor::mask_card(card_number),
                amount,
            }
        }

        // Private helper method (Data Hiding)
        fn mask_card(real_no: &str) -> String {
            if real_no.len() > 4 {
                let last_4 = &real_no[real_no.len() - 4..];
                format!("****-****-****-{}", last_4)
            } else {
                "****".to_string()
            }
        }

        pub fn process(&self) {
            println!("Processing payment of ${:.2} for card {}", self.amount, self.card_number);
        }
    }
}

fn main() {
    println!("--- 1. Access Modifiers ---");
    // We use the full path 'bank::BankAccount'
    let mut account = bank::BankAccount::new("Alice", 1000.0);
    
    // Valid: 'owner' is pub
    println!("Account Holder: {}", account.owner);
    
    // Valid: Accessing private data via public method
    println!("Current Balance: {:.2}", account.balance());
    
    // Invalid: Direct access would cause compile error
    // println!("{}", account.balance); // ERROR: field `balance` is private
    
    account.deposit(500.0);
    println!("Updated Balance: {:.2}", account.balance());


    println!("\n--- 2. Getters & Setters ---");
    let mut emp = hr::Employee::new("John Doe", 25);
    emp.set_age(30);
    // emp.name = "Jane".to_string(); // ERROR: 'name' is private
    println!("Employee: {}, Age: {}", emp.name(), emp.age());


    println!("\n--- 3. Real World: Data Hiding ---");
    let p = payment::Processor::new("1234567812345678", 250.00);
    // The internal logic hid the real card number automatically
    p.process();
}