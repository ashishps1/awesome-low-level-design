/*
 * ABSTRACTION EXAMPLE: A Coffee Machine
 *
 * Goal: The user interacts with a simple interface (make_coffee),
 * hiding the complex logic (grinding, heating, checking water) inside.
 */

// 1. THE ABSTRACTION (The Interface)
// We define a Trait to specify WHAT a Coffee Machine should do.
// The user strictly interacts with these methods.
pub trait CoffeeMaker {
    fn brew(&mut self);
    fn add_water(&mut self, amount: u32);
}

// 2. THE CONCRETE TYPE (The Data)
// These fields represent the internal state.
// Notice we do NOT make the fields 'pub'. They are hidden from the outside world.
pub struct PremiumCoffeeMachine {
    water_level: u32,
    beans_level: u32,
}

// 3. INTERNAL LOGIC (Helper methods)
// These methods are NOT part of the Trait. They are private internal logic
// used to support the public abstraction.
impl PremiumCoffeeMachine {
    pub fn new(water: u32, beans: u32) -> Self {
        PremiumCoffeeMachine {
            water_level: water,
            beans_level: beans,
        }
    }

    // This is an internal detail (Encapsulated logic).
    // The user doesn't need to call this manually.
    fn grind_beans(&mut self) -> bool {
        if self.beans_level > 10 {
            self.beans_level -= 10;
            println!("* Grinding beans... *");
            return true;
        }
        println!("Error: Not enough beans!");
        false
    }

    // Another internal detail.
    fn heat_water(&mut self) -> bool {
        if self.water_level > 20 {
            self.water_level -= 20;
            println!("* Heating water... *");
            return true;
        }
        println!("Error: Add more water!");
        false
    }
}

// 4. IMPLEMENTING THE ABSTRACTION
// We expose only the high-level 'brew' functionality to the user.
impl CoffeeMaker for PremiumCoffeeMachine {
    fn add_water(&mut self, amount: u32) {
        self.water_level += amount;
        println!("Added {}ml of water. Current level: {}ml", amount, self.water_level);
    }

    // This is the implementation of the Abstraction.
    // The complexity of grinding and heating is HIDDEN behind this single function call.
    fn brew(&mut self) {
        println!("\n--- Starting Brew Process ---");
        // We chain internal steps here. The user doesn't know this complexity exists.
        if self.grind_beans() && self.heat_water() {
            println!("Success: Here is your hot coffee! ☕");
        } else {
            println!("Failure: Could not brew coffee.");
        }
        println!("-----------------------------\n");
    }
}

fn main() {
    // User creates the machine
    let mut machine = PremiumCoffeeMachine::new(0, 100);

    // USAGE
    // The user doesn't verify water temp or grind size manually.
    // They just use the abstract interface methods: add_water() and brew().
    
    machine.add_water(50); // User interacts with the interface
    machine.brew();        // User interacts with the interface

    // Trying to brew again without water
    machine.brew();
}