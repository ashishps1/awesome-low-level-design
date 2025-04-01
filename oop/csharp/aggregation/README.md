# Aggregation in C#

## Introduction

Aggregation is a key concept in object-oriented programming (OOP) that represents a "has-a" relationship between two classes, but with a crucial distinction: the lifecycle of the contained object is independent of the container object. This means that while one class contains another, the contained object can exist independently of the container.

Aggregation allows for better modularity, code reuse, and maintainability. It is different from composition, where the contained object cannot exist without the container.

## What is Aggregation?

Aggregation is a form of association in OOP where an object of one class contains a reference to an object of another class. However, the contained object can exist independently of the container. This means that even if the container object is destroyed, the contained object can still be used elsewhere in the application.

### Key Characteristics of Aggregation:
- Represents a **has-a** relationship.
- The contained object **can exist independently** of the container.
- Implemented using references to objects.
- Promotes **loose coupling** between objects.

### Example: A University and its Professors

Consider a scenario where a `University` contains multiple `Professor` objects. However, a `Professor` can exist independently of any university. This is an example of aggregation.

```csharp
using System;
using System.Collections.Generic;

class Professor {
    public string Name { get; private set; }
    public string Subject { get; private set; }
    
    public Professor(string name, string subject) {
        Name = name;
        Subject = subject;
    }
    
    public void Teach() {
        Console.WriteLine($"{Name} is teaching {Subject}");
    }
}

class University {
    private string universityName;
    private List<Professor> professors;
    
    public University(string universityName) {
        this.universityName = universityName;
        professors = new List<Professor>();
    }
    
    public void AddProfessor(Professor professor) {
        professors.Add(professor);
    }
    
    public void ShowProfessors() {
        Console.WriteLine($"Professors at {universityName}:");
        foreach (var professor in professors) {
            Console.WriteLine($" - {professor.Name}");
        }
    }
}

class AggregationExample {
    static void Main() {
        Professor prof1 = new Professor("Dr. Smith", "Computer Science");
        Professor prof2 = new Professor("Dr. Johnson", "Mathematics");
        
        University university = new University("Harvard University");
        university.AddProfessor(prof1);
        university.AddProfessor(prof2);
        
        university.ShowProfessors();
        
        // Professors can exist independently
        prof1.Teach();
        prof2.Teach();
    }
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
   - Aggregated objects can be used in multiple places without being tightly coupled to a single container class.

### 2. **Encourages Loose Coupling**
   - Aggregation allows objects to interact without being dependent on the lifecycle of each other.

### 3. **Better Maintainability**
   - Changes in one class do not heavily impact the other, making the codebase easier to modify and extend.

### 4. **Real-World Applicability**
   - Many real-world relationships, such as a school and its teachers, a company and its employees, naturally fit the aggregation model.

---

## Aggregation with Interfaces

Using interfaces, we can further enhance the flexibility of aggregation.

```csharp
using System;
using System.Collections.Generic;

interface ITeachable {
    void Teach();
}

class Professor : ITeachable {
    public string Name { get; private set; }
    public string Subject { get; private set; }
    
    public Professor(string name, string subject) {
        Name = name;
        Subject = subject;
    }
    
    public void Teach() {
        Console.WriteLine($"{Name} is teaching {Subject}");
    }
}

class University {
    private string universityName;
    private List<ITeachable> professors;
    
    public University(string universityName) {
        this.universityName = universityName;
        professors = new List<ITeachable>();
    }
    
    public void AddProfessor(ITeachable professor) {
        professors.Add(professor);
    }
    
    public void ShowProfessors() {
        Console.WriteLine($"Professors at {universityName}:");
        foreach (var professor in professors) {
            professor.Teach();
        }
    }
}

class InterfaceAggregationExample {
    static void Main() {
        Professor prof1 = new Professor("Dr. Adams", "Physics");
        Professor prof2 = new Professor("Dr. Lee", "Chemistry");
        
        University university = new University("MIT");
        university.AddProfessor(prof1);
        university.AddProfessor(prof2);
        
        university.ShowProfessors();
    }
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