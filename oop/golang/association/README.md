# Association in Golang

## Introduction

Association is a fundamental concept in object-oriented programming (OOP) that defines a relationship between two or more objects. It represents how objects interact with each other while maintaining their independence.

Association is **not inheritance**—rather, it is a relationship between objects that allows communication while ensuring they remain loosely coupled.

## What is Association?

Association defines a connection between two structs, where one struct is linked to another. The association can be **one-to-one**, **one-to-many**, **many-to-one**, or **many-to-many**. Objects in an association can exist independently of each other.

### Key Characteristics of Association:
- Represents a **uses-a** or **knows-a** relationship.
- Objects in an association **can exist independently**.
- Can be **unidirectional** or **bidirectional**.
- Promotes **modularity** and **code reusability**.

### Example: A Student and a Teacher

A `Student` can be associated with multiple `Teacher` objects, and a `Teacher` can have multiple `Student` objects. This represents a **many-to-many** association.

```go
package main

import "fmt"

type Student struct {
    Name string
}

type Teacher struct {
    Name     string
    Students []*Student
}

func (t *Teacher) AddStudent(s *Student) {
    t.Students = append(t.Students, s)
}

func (t *Teacher) ShowStudents() {
    fmt.Println(t.Name, "teaches:")
    for _, student := range t.Students {
        fmt.Println(" -", student.Name)
    }
}

func main() {
    teacher1 := Teacher{Name: "Mr. Smith"}
    teacher2 := Teacher{Name: "Mrs. Johnson"}
    
    student1 := Student{Name: "Alice"}
    student2 := Student{Name: "Bob"}
    
    teacher1.AddStudent(&student1)
    teacher1.AddStudent(&student2)
    teacher2.AddStudent(&student2)
    
    teacher1.ShowStudents()
    teacher2.ShowStudents()
}
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
   - Each object of struct A is associated with one object of struct B.
   - Example: A `Person` has one `Passport`.

### 2. **One-to-Many Association**
   - One object of struct A can be associated with multiple objects of struct B.
   - Example: A `Teacher` teaches multiple `Students`.

### 3. **Many-to-One Association**
   - Multiple objects of struct A can be associated with one object of struct B.
   - Example: Multiple `Students` belong to one `School`.

### 4. **Many-to-Many Association**
   - Multiple objects of struct A can be associated with multiple objects of struct B.
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

```go
package main

import "fmt"

type Library struct {
    Name  string
    Books []*Book
}

type Book struct {
    Title   string
    Library *Library
}

func (l *Library) AddBook(b *Book) {
    l.Books = append(l.Books, b)
}

func (l *Library) ShowBooks() {
    fmt.Println("Books in", l.Name, ":")
    for _, book := range l.Books {
        fmt.Println(" -", book.Title)
    }
}

func (b *Book) ShowLibrary() {
    fmt.Println(b.Title, "is in", b.Library.Name)
}

func main() {
    library := Library{Name: "City Library"}
    book1 := Book{Title: "1984", Library: &library}
    book2 := Book{Title: "Brave New World", Library: &library}
    
    library.AddBook(&book1)
    library.AddBook(&book2)
    
    library.ShowBooks()
    book1.ShowLibrary()
    book2.ShowLibrary()
}
```

### Output:
```
Books in City Library:
 - 1984
 - Brave New World
1984 is in City Library
Brave New World is in City Library
```