/*
 * COMPOSITION IN RUST
 *
 * Concept: "Has-a" relationship with Strong Ownership.
 * Pattern: Structs embedding other Structs.
 */

// --- 1. COMPONENT STRUCTS ---

struct Engine {
    horsepower: u32,
}

impl Engine {
    fn new(horsepower: u32) -> Self {
        Engine { horsepower }
    }

    fn start(&self) {
        println!("  -> Engine started with {} HP.", self.horsepower);
    }
}

struct Wheel {
    wheel_type: String,
}

impl Wheel {
    fn new(wheel_type: &str) -> Self {
        Wheel {
            wheel_type: wheel_type.to_string(),
        }
    }

    fn rotate(&self) {
        println!("  -> The {} wheel is rotating.", self.wheel_type);
    }
}

struct Transmission {
    trans_type: String,
}

impl Transmission {
    fn new(trans_type: &str) -> Self {
        Transmission {
            trans_type: trans_type.to_string(),
        }
    }

    fn shift(&self) {
        println!("  -> Transmission shifted: {}", self.trans_type);
    }
}

// --- 2. THE COMPOSITE STRUCT (Strong Ownership) ---

struct Car {
    // The Car OWNS these objects. 
    // If Car is dropped, these are dropped.
    engine: Engine,
    wheels: Wheel, // Simplified to 1 wheel for demo
    transmission: Transmission,
}

impl Car {
    fn new(hp: u32, wheel_type: &str, trans_type: &str) -> Self {
        Car {
            engine: Engine::new(hp),
            wheels: Wheel::new(wheel_type),
            transmission: Transmission::new(trans_type),
        }
    }

    fn drive(&self) {
        println!("Driving Car...");
        self.engine.start();
        self.wheels.rotate();
        self.transmission.shift();
        println!("Car is moving!\n");
    }
}


// --- 3. COMPOSITION WITH TRAITS (Dynamic Swapping) ---

trait PowerSource {
    fn power_up(&self);
}

struct ElectricMotor;
impl PowerSource for ElectricMotor {
    fn power_up(&self) {
        println!("  -> Electric motor humming silently... ⚡");
    }
}

struct DieselMotor;
impl PowerSource for DieselMotor {
    fn power_up(&self) {
        println!("  -> Diesel motor rumbling... ⛽");
    }
}

struct HybridVehicle {
    // We use Box<dyn Trait> to hold any type of engine
    power_source: Box<dyn PowerSource>,
}

impl HybridVehicle {
    fn new(source: Box<dyn PowerSource>) -> Self {
        HybridVehicle { power_source: source }
    }

    fn start(&self) {
        self.power_source.power_up();
    }
}

fn main() {
    println!("--- 1. Direct Composition (Static) ---");
    // We create the parts INSIDE the constructor call
    let my_car = Car::new(150, "Alloy", "Automatic");
    my_car.drive();


    println!("--- 2. Composition with Interfaces (Dynamic) ---");
    
    // We can inject dependencies dynamically
    let ev = HybridVehicle::new(Box::new(ElectricMotor));
    print!("EV: ");
    ev.start();

    let truck = HybridVehicle::new(Box::new(DieselMotor));
    print!("Truck: ");
    truck.start();

    // PROOF OF OWNERSHIP
    // Unlike Aggregation, we cannot access the 'ElectricMotor' independently 
    // after passing it to HybridVehicle. It has been moved inside.
    println!("\n(Note: The motors are now owned by the vehicles and cannot be accessed separately.)");
}