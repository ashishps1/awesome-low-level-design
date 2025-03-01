# Classes and Objects

Classes and objects form the foundation of Object-Oriented Programming (OOP).

## What is a Class?

A class is a blueprint or template. It defines the attributes (fields) and behaviors (methods) of an object.

### Defining a Class in Java

To define a class in Java, you use the `class` keyword followed by the name of the class. 

Here's a simple example:

```java
public class Car {
    // Attributes
    private String color;
    private String make;
    private String model;
    private int year;

    // Constructor
    public Car(String color, String make, String model, int year) {
        this.color = color;
        this.make = make;
        this.model = model;
        this.year = year;
    }

    // Method to display car details
    public void displayInfo() {
        System.out.println("Car Make: " + make);
        System.out.println("Car Model: " + model);
        System.out.println("Car Year: " + year);
        System.out.println("Car Color: " + color);
    }
}
```
- **Attributes**: The class `Car` has four attributes that describe its state: `color`, `make`, `model`, and `year`.
- **Constructor**: The constructor `Car(String color, String make, String model, int year)` initializes new objects of the class.
- **Methods**: The `displayInfo` method is responsible for showcasing the car details.

## What is an Object?

An object is an instance of a class. When you create an object, you are bringing the blueprint of the class into reality. It consists of state and behavior defined by the class, with each object holding its own copy of the data.

### Creating Objects in Java

To create an object, you use the `new` keyword followed by the class constructor. 

Here's how you can instantiate objects from the `Car` class:

```java
public class Main {
    public static void main(String[] args) {
        // Creating an object of the Car class
        Car car1 = new Car("Red", "Toyota", "Corolla", 2020);
        Car car2 = new Car("Blue", "Ford", "Mustang", 2021);

        // Displaying information of each car
        car1.displayInfo();
        System.out.println("-----------------");
        car2.displayInfo();
    }
}
```

1. **Instantiation**: The `new` keyword is used to create an object, which allocates memory for it.
2. **Initialization**: The constructor (`Car`) initializes the object state with given parameters.
3. **Reference**: The object is referenced through a variable (`car1`, `car2`) that points to its memory location.