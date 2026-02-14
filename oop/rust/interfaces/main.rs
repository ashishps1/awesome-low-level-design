/*
 * INTERFACES IN RUST (TRAITS)
 *
 * Goal: Demonstrate how Traits act as contracts (Java Interface equivalent).
 */

// 1. BASIC INTERFACE
// The Contract
pub trait Vehicle {
    fn start(&self);
    fn stop(&self);
}

// The Data
pub struct Car {
    pub brand: String,
}

// The Implementation (Binding Trait to Struct)
impl Vehicle for Car {
    fn start(&self) {
        println!("{} is starting... 🚗", self.brand);
    }
    fn stop(&self) {
        println!("{} is stopping... 🛑", self.brand);
    }
}

// 2. MULTIPLE INTERFACES (Composition)
trait Flyable {
    fn fly(&self);
}

trait Drivable {
    fn drive(&self);
}

struct FlyingCar;

impl Flyable for FlyingCar {
    fn fly(&self) {
        println!("FlyingCar is flying... ✈️");
    }
}

impl Drivable for FlyingCar {
    fn drive(&self) {
        println!("FlyingCar is driving... 🚙");
    }
}

// 3. DEFAULT & STATIC METHODS
trait Animal {
    fn sound(&self);
    
    // Default method (Optional to override)
    fn sleep(&self) {
        println!("Sleeping... 💤");
    }
}

struct Dog;

impl Animal for Dog {
    fn sound(&self) {
        println!("Dog barks! 🐶");
    }
}

trait MathOperations {
    // Associated Function (Static Method) - No '&self'
    fn add(a: i32, b: i32) -> i32 {
        a + b
    }
}

struct Calculator;
impl MathOperations for Calculator {}

// 4. REAL WORLD PAYMENT (POLYMORPHISM)
trait Payment {
    fn pay(&self, amount: f64);
}

struct CreditCard;
impl Payment for CreditCard {
    fn pay(&self, amount: f64) {
        println!("Paid ${:.2} using Credit Card 💳", amount);
    }
}

struct PayPal;
impl Payment for PayPal {
    fn pay(&self, amount: f64) {
        println!("Paid ${:.2} using PayPal 🅿️", amount);
    }
}

fn main() {
    println!("--- 1. Basic Interface ---");
    let my_car = Car { brand: "Toyota".to_string() };
    my_car.start();
    my_car.stop();

    println!("\n--- 2. Multiple Interfaces ---");
    let fly_car = FlyingCar;
    fly_car.fly();
    fly_car.drive();

    println!("\n--- 3. Default & Static Methods ---");
    let dog = Dog;
    dog.sound();
    dog.sleep(); // Uses default implementation
    
    // Call static method using the Type name
    let sum = Calculator::add(5, 10);
    println!("Sum: {}", sum);

    println!("\n--- 4. Real World Polymorphism ---");
    let cc = CreditCard;
    let pp = PayPal;
    
    // Using explicit loop to simulate processing different payments
    // '&dyn Payment' allows us to store different types in one list
    let payments: Vec<&dyn Payment> = vec![&cc, &pp];
    for p in payments {
        p.pay(100.0);
    }
}