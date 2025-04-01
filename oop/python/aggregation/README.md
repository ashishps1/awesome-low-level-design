# Aggregation in Python

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

```python
class Professor:
    def __init__(self, name, subject):
        self.name = name
        self.subject = subject

    def teach(self):
        print(f"{self.name} is teaching {self.subject}")


class University:
    def __init__(self, university_name):
        self.university_name = university_name
        self.professors = []

    def add_professor(self, professor):
        self.professors.append(professor)

    def show_professors(self):
        print(f"Professors at {self.university_name}:")
        for professor in self.professors:
            print(f" - {professor.name}")


# Example Usage
if __name__ == "__main__":
    prof1 = Professor("Dr. Smith", "Computer Science")
    prof2 = Professor("Dr. Johnson", "Mathematics")
    
    university = University("Harvard University")
    university.add_professor(prof1)
    university.add_professor(prof2)
    
    university.show_professors()
    
    # Professors can exist independently
    prof1.teach()
    prof2.teach()
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

## Aggregation with Interfaces (Abstract Base Classes)

Using abstract base classes, we can further enhance the flexibility of aggregation.

```python
from abc import ABC, abstractmethod

class Teachable(ABC):
    @abstractmethod
    def teach(self):
        pass


class Professor(Teachable):
    def __init__(self, name, subject):
        self.name = name
        self.subject = subject

    def teach(self):
        print(f"{self.name} is teaching {self.subject}")


class University:
    def __init__(self, university_name):
        self.university_name = university_name
        self.professors = []

    def add_professor(self, professor):
        self.professors.append(professor)

    def show_professors(self):
        print(f"Professors at {self.university_name}:")
        for professor in self.professors:
            professor.teach()


# Example Usage
if __name__ == "__main__":
    prof1 = Professor("Dr. Adams", "Physics")
    prof2 = Professor("Dr. Lee", "Chemistry")
    
    university = University("MIT")
    university.add_professor(prof1)
    university.add_professor(prof2)
    
    university.show_professors()
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