/*
 * CLASSES AND OBJECTS IN RUST
 *
 * Goal: Demonstrate how Rust replaces the "Class" keyword with:
 * 1. Struct (for Data)
 * 2. Impl (for Behavior)
 */

// 1. THE CLASS BLUEPRINT (Data Only)
// In Java, this would be the fields inside 'public class Car'.
// In Rust, we use a Struct to define the "shape" of the data.
pub struct Car {
    pub color: String,
    pub make: String,
    pub model: String,
    pub year: u32,
}

// 2. THE CLASS BEHAVIOR (Methods)
// In Java, these methods would be inside the class curly braces {}.
// In Rust, we use an 'impl' block to attach functions to the Struct.
impl Car {
    // A. CONSTRUCTOR
    // Rust has no 'new' keyword for objects. We create a static function
    // (Associated Function) that returns a new instance of Self.
    pub fn new(color: String, make: String, model: String, year: u32) -> Self {
        Car {
            color: color, 
            make: make,
            model: model,
            year: year,
        }
    }

    // B. INSTANCE METHOD
    // '&self' allows this function to read the data of the specific object calling it.
    // It is exactly like 'this' in Java/C++.
    pub fn display_info(&self) {
        println!("----------------------------");
        println!("Car Details:");
        println!("Make:  {}", self.make);
        println!("Model: {}", self.model);
        println!("Year:  {}", self.year);
        println!("Color: {}", self.color);
        println!("----------------------------");
    }
}

// 3. CREATING OBJECTS (Instances)
fn main() {
    // Instantiation
    // We call the associated function 'Car::new' to create an object.
    // 'car1' is now the Owner of this data.
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

    // Usage
    // We access methods using the dot operator, just like Java.
    car1.display_info();
    car2.display_info();
}