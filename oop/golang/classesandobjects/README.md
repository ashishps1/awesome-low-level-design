# Classes and Objects

Classes and objects form the foundation of Object-Oriented Programming (OOP).

## What is a Class?

A class is a blueprint or template. It defines the attributes (fields) and behaviors (methods) of an object.

### Defining a Class in Go

Go does not have traditional classes, but you can achieve similar behavior using `struct` and methods.

Here's a simple example:

```go
type Car struct {
    // Attributes
    Color string
    Make string
    Model string
    Year int

    // Method to display car details
    func () DisplayInfo() {
        fmt.Println("Car Make: " + Make)
        fmt.Println("Car Model: " + Model)
        fmt.Println("Car Year: " + Year)
        fmt.Println("Car Color: " + Color)
    }
}
```
- **Attributes**: The struct `Car` has four attributes that describe its state: `Color`, `Make`, `Model`, and `Year`.
- **Methods**: The `DisplayInfo` function is responsible for showcasing the car details.

## What is an Object?

An object is an instance of a struct. When you create an object, you are bringing the blueprint of the struct into reality. It consists of state and behavior defined by the struct, with each object holding its own copy of the data.

### Creating Objects in Go

To create an object, you instantiate the struct `Car`. 

Here's how you can instantiate objects from the `Car` struct:

```go
func main() {
    // Creating an object of the Car class
    car1 := Car{"Red", "Toyota", "Corolla", 2020}
    car2 := Car{"Blue", "Ford", "Mustang", 2021}

    // Displaying information of each car
    car1.DisplayInfo()
    fmt.Println("-----------------")
    car2.DisplayInfo()
}
```

1. **Instantiation**: The struct `Car` is used to create an object, which allocates memory for it.
2. **Initialization**: The struct instance holds its own set of values.
3. **Reference**: The object is referenced using a variable (`car1`, `car2`) that holds its memory location.