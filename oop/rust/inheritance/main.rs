/*
 * INHERITANCE IN RUST (TRAITS & COMPOSITION)
 *
 * Goal: Demonstrate how to achieve OOP Inheritance patterns using Rust.
 * * 1. Behavior Inheritance -> Traits
 * 2. Data Inheritance -> Composition
 */

// --- 1. BASIC INHERITANCE (TRAITS) ---

// Parent Trait
trait Animal {
    fn name(&self) -> &String;

    // Default method (Acts like a Parent Class method)
    fn eat(&self) {
        println!("{} is eating...", self.name());
    }
}

// Child Struct
struct Dog {
    name: String,
    breed: String,
}

// Implement the Trait
impl Animal for Dog {
    fn name(&self) -> &String {
        &self.name
    }
}

impl Dog {
    fn bark(&self) {
        println!("{} (a {}) is barking!", self.name, self.breed);
    }
}


// --- 2. MULTILEVEL INHERITANCE (SUPERTRAITS) ---

trait Living {
    fn live(&self) { println!("I am alive."); }
}

// 'Mammal' requires 'Living' to be implemented
trait Mammal: Living {
    fn walk(&self) { println!("I can walk."); }
}

struct Cat;

// Must implement the base trait
impl Living for Cat {}

// Can now implement the sub-trait
impl Mammal for Cat {}


// --- 3. METHOD OVERRIDING ---

trait SoundMaker {
    fn make_sound(&self) {
        println!("(Generic Sound)");
    }
}

struct Cow;

impl SoundMaker for Cow {
    // Override the default implementation
    fn make_sound(&self) {
        println!("Moo! 🐮");
    }
}


// --- 4. COMPOSITION (THE 'SUPER' REPLACEMENT) ---

// The "Parent" Data
struct BaseEntity {
    id: u32,
}

impl BaseEntity {
    fn save(&self) {
        println!("Saving Entity ID: {} to database...", self.id);
    }
}

// The "Child" Data
struct User {
    base: BaseEntity, // Composition: User HAS-A BaseEntity
    username: String,
}

impl User {
    fn new(id: u32, username: &str) -> Self {
        User {
            base: BaseEntity { id },
            username: username.to_string(),
        }
    }

    fn save_user(&self) {
        println!("Preparing user {}...", self.username);
        self.base.save(); // Call "super" method explicitly
    }
}


fn main() {
    println!("--- 1. Basic Inheritance (Traits) ---");
    let dog = Dog { 
        name: "Buddy".to_string(), 
        breed: "Golden Retriever".to_string() 
    };
    dog.eat(); // Inherited behavior
    dog.bark(); // Specific behavior

    println!("\n--- 2. Multilevel Inheritance ---");
    let cat = Cat;
    cat.live(); // From Base Trait
    cat.walk(); // From Sub Trait

    println!("\n--- 3. Method Overriding ---");
    let cow = Cow;
    cow.make_sound(); // Overridden behavior

    println!("\n--- 4. Composition (Data Inheritance) ---");
    let user = User::new(101, "Alice");
    user.save_user();
}

