# Aggregation in Java

## Introduction

Aggregation is a key concept in object-oriented programming (OOP) that represents a "has-a" relationship between two classes, but with a crucial distinction: the lifecycle of the contained object is independent of the container object. This means that while one class contains another, the contained object can exist independently of the container.

Aggregation allows for better modularity, code reuse, and maintainability. It is different from composition, where the contained object cannot exist without the container.

---

## What is Aggregation?

Aggregation is a form of association in OOP where an object of one class contains a reference to an object of another class. However, the contained object can exist independently of the container. This means that even if the container object is destroyed, the contained object can still be used elsewhere in the application.

### Key Characteristics of Aggregation:
- Represents a **has-a** relationship.
- The contained object **can exist independently** of the container.
- Implemented using references (pointers) to objects.
- Promotes **loose coupling** between objects.

### Example: A University and its Professors

Consider a scenario where a `University` contains multiple `Professor` objects. However, a `Professor` can exist independently of any university. This is an example of aggregation.

```java
class Professor {
    private String name;
    private String subject;
    
    public Professor(String name, String subject) {
        this.name = name;
        this.subject = subject;
    }
    
    public void teach() {
        System.out.println(name + " is teaching " + subject);
    }
}

class University {
    private String universityName;
    private List<Professor> professors;
    
    public University(String universityName) {
        this.universityName = universityName;
        this.professors = new ArrayList<>();
    }
    
    public void addProfessor(Professor professor) {
        professors.add(professor);
    }
    
    public void showProfessors() {
        System.out.println("Professors at " + universityName + ":");
        for (Professor professor : professors) {
            System.out.println(" - " + professor.name);
        }
    }
}

import java.util.*;

public class AggregationExample {
    public static void main(String[] args) {
        Professor prof1 = new Professor("Dr. Smith", "Computer Science");
        Professor prof2 = new Professor("Dr. Johnson", "Mathematics");
        
        University university = new University("Harvard University");
        university.addProfessor(prof1);
        university.addProfessor(prof2);
        
        university.showProfessors();
        
        // Professors can exist independently
        prof1.teach();
        prof2.teach();
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

```java
interface Teachable {
    void teach();
}

class Professor implements Teachable {
    private String name;
    private String subject;
    
    public Professor(String name, String subject) {
        this.name = name;
        this.subject = subject;
    }
    
    public void teach() {
        System.out.println(name + " is teaching " + subject);
    }
}

class University {
    private String universityName;
    private List<Teachable> professors;
    
    public University(String universityName) {
        this.universityName = universityName;
        this.professors = new ArrayList<>();
    }
    
    public void addProfessor(Teachable professor) {
        professors.add(professor);
    }
    
    public void showProfessors() {
        System.out.println("Professors at " + universityName + ":");
        for (Teachable professor : professors) {
            professor.teach();
        }
    }
}

import java.util.*;

public class InterfaceAggregationExample {
    public static void main(String[] args) {
        Professor prof1 = new Professor("Dr. Adams", "Physics");
        Professor prof2 = new Professor("Dr. Lee", "Chemistry");
        
        University university = new University("MIT");
        university.addProfessor(prof1);
        university.addProfessor(prof2);
        
        university.showProfessors();
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