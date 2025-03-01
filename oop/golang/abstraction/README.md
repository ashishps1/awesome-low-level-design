# Abstraction

## What is Abstraction?

Abstraction is an OOP principle that focuses on showing only the necessary features of an object while hiding the irrelevant details. The idea is to expose only what is necessary to the user and omit complex inner workings, thus simplifying the usage of complex systems.

### Real-world Analogy

Think of a car. To drive, you need to understand how to accelerate, brake, and steer. You don't need to understand the intricate details of the engine or the braking system. The complex parts are abstracted away from the driver, exposing only the essential parts relevant for driving.

## Benefits of Abstraction

1. **Simplicity**: By hiding details, you reduce complexity for users.
2. **Reusability**: Abstract components can be reused across different parts of an application or in different projects.
3. **Maintainability**: Streamlines code updates since changes to abstract details do not affect users.
4. **Modularity**: Encourages a modular approach, helping in the organization and management of code.

## Abstraction in Go

Go, being a statically typed language, doesn't have classical inheritance-based OOP features like other object-oriented languages. Instead, Go achieves abstraction primarily through interfaces.

### Interfaces

In Go, interfaces are a way to define behavior by specifying method signatures. They do not describe any data, unlike structs. Any type that implements the methods of an interface is considered to satisfy that interface.

### Example of Abstraction in Go

Let's create an example to illustrate how abstraction can be implemented using interfaces in Go.

```go
package main

import (
	"fmt"
)

// Define an interface `Vehicle`
type Vehicle interface {
	Drive()
	Stop()
}

// Implement `Car` struct
type Car struct {
	Make  string
	Model string
}

// Implement `Drive` and `Stop` methods for `Car`
func (c Car) Drive() {
	fmt.Printf("The %s %s is driving.\n", c.Make, c.Model)
}

func (c Car) Stop() {
	fmt.Printf("The %s %s has stopped.\n", c.Make, c.Model)
}

// Implement `Bike` struct
type Bike struct {
	Brand string
}

// Implement `Drive` and `Stop` methods for `Bike`
func (b Bike) Drive() {
	fmt.Printf("The %s bike is cycling.\n", b.Brand)
}

func (b Bike) Stop() {
	fmt.Printf("The %s bike has stopped.\n", b.Brand)
}

func main() {
	// Create a list of `Vehicle` type
	vehicles := []Vehicle{
		Car{Make: "Toyota", Model: "Corolla"},
		Bike{Brand: "Schwinn"},
	}

	// Use the interface methods
	for _, v := range vehicles {
		v.Drive()
		v.Stop()
	}
}
```

### What Does This Code Do?

- We define a `Vehicle` interface with two methods: `Drive()` and `Stop()`.
- We create two concrete types: `Car` and `Bike`.
- `Car` and `Bike` both implement the `Vehicle` interface by defining the methods `Drive()` and `Stop()`.
- In `main()`, we store instances of `Car` and `Bike` in a slice of type `Vehicle` and call the methods defined by the interface.

This example demonstrates how abstraction allows us to treat `Car` and `Bike` objects uniformly as `Vehicle` objects, focusing only on behavior defined by the `Vehicle` interface without knowing details about the specific types.