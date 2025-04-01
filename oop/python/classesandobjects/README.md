# Classes and Objects

Classes and objects form the foundation of Object-Oriented Programming (OOP).

## What is a Class?

A class is a blueprint or template. It defines the attributes (fields) and behaviors (methods) of an object.

### Defining a Class in Python

To define a class in Python, you use the `class` keyword followed by the name of the class. 

Here's a simple example:

```python
class Car:
    # Constructor
    def __init__(self, color, make, model, year):
        self.color = color
        self.make = make
        self.model = model
        self.year = year

    # Method to display car details
    def display_info(self):
        print(f"Car Make: {self.make}")
        print(f"Car Model: {self.model}")
        print(f"Car Year: {self.year}")
        print(f"Car Color: {self.color}")
```
- **Attributes**: The class `Car` has four attributes that describe its state: `color`, `make`, `model`, and `year`.
- **Constructor**: The constructor `__init__(self, color, make, model, year)` initializes new objects of the class.
- **Methods**: The `display_info` method is responsible for showcasing the car details.

## What is an Object?

An object is an instance of a class. When you create an object, you are bringing the blueprint of the class into reality. It consists of state and behavior defined by the class, with each object holding its own copy of the data.

### Creating Objects in Python

To create an object, you call the class constructor. 

Here's how you can instantiate objects from the `Car` class:

```python
car1 = Car("Red", "Toyota", "Corolla", 2020)
car2 = Car("Blue", "Ford", "Mustang", 2021)

# Displaying information of each car
car1.display_info()
print("-----------------")
car2.display_info()
```

1. **Initialization**: The constructor (`Car`) initializes the object state with given parameters.
2. **Reference**: The object is referenced through a variable (`car1`, `car2`) that points to its memory location.