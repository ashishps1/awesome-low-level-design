# Classes and Objects

Classes and objects form the foundation of Object-Oriented Programming (OOP).

## What is a Class?

A class is a blueprint or template. It defines the attributes (fields) and behaviors (methods) of an object.

### Defining a Class in C++

To define a class in C++, you use the `class` keyword followed by the name of the class. 

Here's a simple example:

```cpp
#include <iostream>
using namespace std;

class Car {
    // Attributes
    private:
    string color;
    string make;
    string model;
    int year;

    // Constructor
    Car(string color, string make, string model, int year) {
        this->color = color;
        this->make = make;
        this->model = model;
        this->year = year;
    }

    // Method to display car details
    void displayInfo() {
        cout << "Car Make: " << make << endl;
        cout << "Car Model: " << model << endl;
        cout << "Car Year: " << year << endl;
        cout << "Car Color: " << color << endl;
    }
}
```
- **Attributes**: The class `Car` has four attributes that describe its state: `color`, `make`, `model`, and `year`.
- **Constructor**: The constructor `Car(string color, string make, string model, int year)` initializes new objects of the class.
- **Methods**: The `displayInfo` method is responsible for showcasing the car details.

## What is an Object?

An object is an instance of a class. When you create an object, you are bringing the blueprint of the class into reality. It consists of state and behavior defined by the class, with each object holding its own copy of the data.

### Creating Objects in C++

To create an object, you use the class constructor. 

Here's how you can instantiate objects from the `Car` class:

```cpp
int main() {
    // Creating an object of the Car class
    Car car1 = Car("Red", "Toyota", "Corolla", 2020);
    Car car2 = Car("Blue", "Ford", "Mustang", 2021);

    // Displaying information of each car
    car1.displayInfo();
    cout << "-----------------";
    car2.displayInfo();
}
```

1. **Instantiation**: The `Car` constructor is used to create an object, which allocates memory for it.
2. **Initialization**: The constructor (`Car`) initializes the object state with given parameters.
3. **Reference**: The object is referenced through a variable (`car1`, `car2`) that points to its memory location.