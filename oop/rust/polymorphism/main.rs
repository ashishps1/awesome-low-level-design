/*
 * POLYMORPHISM IN RUST
 *
 * Goal: Demonstrate Static Dispatch (Generics) and Dynamic Dispatch (Trait Objects).
 */

// --- 1. COMPILE-TIME POLYMORPHISM (GENERICS) ---

// Define a trait
trait Addable {
    fn add(&self, other: i32) -> i32;
}

// Implement for a struct
struct Number {
    value: i32,
}

impl Addable for Number {
    fn add(&self, other: i32) -> i32 {
        self.value + other
    }
}

// Generic Function (Static Dispatch)
// T: Addable means "Any type T that implements Addable"
// Compiler creates a specific version of this function for 'Number'
fn static_add<T: Addable>(item: T, extra: i32) -> i32 {
    item.add(extra)
}


// --- 2. RUN-TIME POLYMORPHISM (TRAIT OBJECTS) ---

trait Animal {
    fn make_sound(&self);
}

struct Dog;
impl Animal for Dog {
    fn make_sound(&self) {
        println!("Dog barks 🐶");
    }
}

struct Cat;
impl Animal for Cat {
    fn make_sound(&self) {
        println!("Cat meows 🐱");
    }
}


// --- 3. POLYMORPHISM WITH TRAITS (INTERFACES) ---

trait Vehicle {
    fn start(&self);
}

struct Car;
impl Vehicle for Car {
    fn start(&self) {
        println!("Car is starting... 🚗");
    }
}

struct Bike;
impl Vehicle for Bike {
    fn start(&self) {
        println!("Bike is starting... 🏍️");
    }
}


// --- 4. REAL WORLD EXAMPLE: PAYMENT SYSTEM ---

trait Payment {
    fn pay(&self, amount: f64);
}

struct CreditCardPayment;
impl Payment for CreditCardPayment {
    fn pay(&self, amount: f64) {
        println!("Paid ${:.2} using Credit Card 💳", amount);
    }
}

struct PayPalPayment;
impl Payment for PayPalPayment {
    fn pay(&self, amount: f64) {
        println!("Paid ${:.2} using PayPal 🅿️", amount);
    }
}

// Helper function accepting a Trait Object (Dynamic Dispatch)
fn process(payment_method: &dyn Payment, amount: f64) {
    payment_method.pay(amount);
}


fn main() {
    println!("--- 1. Compile-Time Polymorphism (Generics) ---");
    let num = Number { value: 10 };
    // The compiler generates a specific version of static_add for 'Number'
    let result = static_add(num, 5); 
    println!("Result: {}", result);


    println!("\n--- 2. Run-Time Polymorphism (Dynamic Dispatch) ---");
    // We use Box<dyn Animal> to store different types in one Vec
    // This requires a vtable lookup at runtime
    let animals: Vec<Box<dyn Animal>> = vec![
        Box::new(Dog),
        Box::new(Cat),
    ];

    for animal in animals {
        // Method called is determined at runtime
        animal.make_sound();
    }


    println!("\n--- 3. Using Polymorphism with Traits ---");
    let my_car = Car;
    let my_bike = Bike;

    // References (&dyn Vehicle) are also Trait Objects
    let vehicles: Vec<&dyn Vehicle> = vec![&my_car, &my_bike];
    for v in vehicles {
        v.start();
    }


    println!("\n--- 4. Real-World Example: Payment System ---");
    let cc = CreditCardPayment;
    let pp = PayPalPayment;

    // We can swap implementations easily
    process(&cc, 100.50);
    process(&pp, 200.75);
}
