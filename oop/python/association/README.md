# Association in Python

## Introduction

Association is a fundamental concept in object-oriented programming (OOP) that defines a relationship between two or more objects. It represents how objects interact with each other while maintaining their independence.

Association is **not inheritance**—rather, it is a relationship between objects that allows communication while ensuring they remain loosely coupled.

## What is Association?

Association defines a connection between two classes, where one class is linked to another. The association can be **one-to-one**, **one-to-many**, **many-to-one**, or **many-to-many**. Objects in an association can exist independently of each other.

### Key Characteristics of Association:
- Represents a **uses-a** or **knows-a** relationship.
- Objects in an association **can exist independently**.
- Can be **unidirectional** or **bidirectional**.
- Promotes **modularity** and **code reusability**.

### Example: A Student and a Teacher

A `Student` can be associated with multiple `Teacher` objects, and a `Teacher` can have multiple `Student` objects. This represents a **many-to-many** association.

```python
class Teacher:
    def __init__(self, name):
        self.name = name
        self.students = []
    
    def add_student(self, student):
        self.students.append(student)
    
    def show_students(self):
        print(f"{self.name} teaches:")
        for student in self.students:
            print(f" - {student.name}")

class Student:
    def __init__(self, name):
        self.name = name

# Example Usage
if __name__ == "__main__":
    teacher1 = Teacher("Mr. Smith")
    teacher2 = Teacher("Mrs. Johnson")
    
    student1 = Student("Alice")
    student2 = Student("Bob")
    
    teacher1.add_student(student1)
    teacher1.add_student(student2)
    teacher2.add_student(student2)
    
    teacher1.show_students()
    teacher2.show_students()
```

### Output:
```
Mr. Smith teaches:
 - Alice
 - Bob
Mrs. Johnson teaches:
 - Bob
```

---

## Types of Association

### 1. **One-to-One Association**
   - Each object of class A is associated with one object of class B.
   - Example: A `Person` has one `Passport`.

### 2. **One-to-Many Association**
   - One object of class A can be associated with multiple objects of class B.
   - Example: A `Teacher` teaches multiple `Students`.

### 3. **Many-to-One Association**
   - Multiple objects of class A can be associated with one object of class B.
   - Example: Multiple `Students` belong to one `School`.

### 4. **Many-to-Many Association**
   - Multiple objects of class A can be associated with multiple objects of class B.
   - Example: `Teachers` and `Students`.

---

## Why Use Association?

- **Promotes Code Reusability**: Objects can be reused across multiple associations without duplication.
- **Encourages Loose Coupling**: Objects interact without depending on the internal implementation of each other.
- **Improves Maintainability**: Changing one object does not heavily impact others, making code easier to manage.
- **Better System Design**: Allows modeling of real-world relationships between entities effectively.

---

## Association vs Aggregation vs Composition

| Feature       | Association | Aggregation | Composition |
|--------------|------------|------------|------------|
| Relationship | "Knows-a"  | "Has-a"    | "Has-a"    |
| Object Independence | Objects are independent | Contained object **can exist independently** | Contained object **cannot exist without** the container |
| Lifetime | Objects exist separately | Contained object **outlives** the container | Contained object **is destroyed** with the container |
| Example | Teacher and Student | University and Professors | Car and Engine |

---

## Bidirectional Association

Associations can be **unidirectional** (one object knows about another) or **bidirectional** (both objects know about each other).

### Example: A Library and Books (Bidirectional Association)

```python
class Library:
    def __init__(self, name):
        self.name = name
        self.books = []
    
    def add_book(self, book):
        self.books.append(book)
    
    def show_books(self):
        print(f"Books in {self.name}:")
        for book in self.books:
            print(f" - {book.title}")

class Book:
    def __init__(self, title, library):
        self.title = title
        self.library = library
    
    def show_library(self):
        print(f"{self.title} is in {self.library.name}")

# Example Usage
if __name__ == "__main__":
    library = Library("City Library")
    book1 = Book("1984", library)
    book2 = Book("Brave New World", library)
    
    library.add_book(book1)
    library.add_book(book2)
    
    library.show_books()
    book1.show_library()
    book2.show_library()
```

### Output:
```
Books in City Library:
 - 1984
 - Brave New World
1984 is in City Library
Brave New World is in City Library
```