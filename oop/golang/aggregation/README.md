# Aggregation in Golang

## Introduction

Aggregation is a key concept in object-oriented programming (OOP) that represents a "has-a" relationship between two classes (or structs in Golang), but with a crucial distinction: the lifecycle of the contained object is independent of the container object. This means that while one struct contains another, the contained struct can exist independently of the container.

Aggregation allows for better modularity, code reuse, and maintainability. It is different from composition, where the contained struct cannot exist without the container.

## What is Aggregation?

Aggregation is a form of association in OOP where an object of one struct contains a reference (pointer) to an object of another struct. However, the contained object can exist independently of the container. This means that even if the container object is destroyed, the contained object can still be used elsewhere in the application.

### Key Characteristics of Aggregation:
- Represents a **has-a** relationship.
- The contained object **can exist independently** of the container.
- Implemented using references (pointers) to objects.
- Promotes **loose coupling** between objects.

### Example: A University and its Professors

Consider a scenario where a `University` contains multiple `Professor` objects. However, a `Professor` can exist independently of any university. This is an example of aggregation.

```go
package main

import "fmt"

// Professor struct (independent entity)
type Professor struct {
    Name    string
    Subject string
}

func (p Professor) Teach() {
    fmt.Printf("%s is teaching %s\n", p.Name, p.Subject)
}

// University struct contains a list of professors (aggregation)
type University struct {
    Name       string
    Professors []*Professor // Aggregation: University has a list of professors
}

func (u *University) AddProfessor(professor *Professor) {
    u.Professors = append(u.Professors, professor)
}

func (u University) ShowProfessors() {
    fmt.Printf("Professors at %s:\n", u.Name)
    for _, professor := range u.Professors {
        fmt.Printf(" - %s\n", professor.Name)
    }
}

func main() {
    prof1 := &Professor{Name: "Dr. Smith", Subject: "Computer Science"}
    prof2 := &Professor{Name: "Dr. Johnson", Subject: "Mathematics"}
    
    university := &University{Name: "Harvard University"}
    university.AddProfessor(prof1)
    university.AddProfessor(prof2)
    
    university.ShowProfessors()
    
    // Professors can exist independently
    prof1.Teach()
    prof2.Teach()
}
```

### Output:
```
Professors at Harvard University:
 - Dr. Smith
 - Dr. Johnson
Dr. Smith is teaching Computer Science
Dr. Johnson is teaching Mathematics
```

---

## Aggregation vs Composition

| Feature       | Aggregation | Composition |
|--------------|------------|-------------|
| Relationship | "Has-a"    | "Has-a"     |
| Ownership    | Contained object **can exist independently** | Contained object **cannot exist without** the container |
| Lifetime     | Contained object **outlives** the container | Contained object **is destroyed** with the container |
| Example      | University and Professors | Car and Engine |

---

## Why Use Aggregation?

### 1. **Promotes Code Reusability**
   - Aggregated objects can be used in multiple places without being tightly coupled to a single container struct.

### 2. **Encourages Loose Coupling**
   - Aggregation allows objects to interact without being dependent on the lifecycle of each other.

### 3. **Better Maintainability**
   - Changes in one struct do not heavily impact the other, making the codebase easier to modify and extend.

### 4. **Real-World Applicability**
   - Many real-world relationships, such as a school and its teachers, a company and its employees, naturally fit the aggregation model.

---

## Aggregation with Interfaces

Using interfaces, we can further enhance the flexibility of aggregation.

```go
package main

import "fmt"

// Teachable interface
type Teachable interface {
    Teach()
}

// Professor struct implementing Teachable interface
type Professor struct {
    Name    string
    Subject string
}

func (p Professor) Teach() {
    fmt.Printf("%s is teaching %s\n", p.Name, p.Subject)
}

// University struct containing a list of professors
type University struct {
    Name       string
    Professors []Teachable
}

func (u *University) AddProfessor(professor Teachable) {
    u.Professors = append(u.Professors, professor)
}

func (u University) ShowProfessors() {
    fmt.Printf("Professors at %s:\n", u.Name)
    for _, professor := range u.Professors {
        professor.Teach()
    }
}

func main() {
    prof1 := Professor{Name: "Dr. Adams", Subject: "Physics"}
    prof2 := Professor{Name: "Dr. Lee", Subject: "Chemistry"}
    
    university := &University{Name: "MIT"}
    university.AddProfessor(prof1)
    university.AddProfessor(prof2)
    
    university.ShowProfessors()
}
```

### Output:
```
Professors at MIT:
Dr. Adams is teaching Physics
Dr. Lee is teaching Chemistry
```

---

## When to Use Aggregation?

- When an object **can exist independently** from the container.
- When designing **loosely coupled** systems.
- When different objects need to be **shared** across multiple containers.
- When following **SOLID principles**, particularly the **Dependency Inversion Principle (DIP)**.