# Association in C#

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

```csharp
using System;
using System.Collections.Generic;

class Teacher {
    public string Name { get; private set; }
    private List<Student> students;
    
    public Teacher(string name) {
        Name = name;
        students = new List<Student>();
    }
    
    public void AddStudent(Student student) {
        students.Add(student);
    }
    
    public void ShowStudents() {
        Console.WriteLine($"{Name} teaches:");
        foreach (var student in students) {
            Console.WriteLine($" - {student.Name}");
        }
    }
}

class Student {
    public string Name { get; private set; }
    
    public Student(string name) {
        Name = name;
    }
}

class AssociationExample {
    static void Main() {
        Teacher teacher1 = new Teacher("Mr. Smith");
        Teacher teacher2 = new Teacher("Mrs. Johnson");
        
        Student student1 = new Student("Alice");
        Student student2 = new Student("Bob");
        
        teacher1.AddStudent(student1);
        teacher1.AddStudent(student2);
        teacher2.AddStudent(student2);
        
        teacher1.ShowStudents();
        teacher2.ShowStudents();
    }
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
   - Example: `Teachers` and `Students` (a student can have multiple teachers, and a teacher can have multiple students).

---

## Why Use Association?

### 1. **Promotes Code Reusability**
   - Objects can be reused across multiple associations without duplication.

### 2. **Encourages Loose Coupling**
   - Objects interact without depending on the internal implementation of each other.

### 3. **Improves Maintainability**
   - Changing one object does not heavily impact others, making code easier to manage.

### 4. **Better System Design**
   - Allows modeling of real-world relationships between entities effectively.

---

## Bidirectional Association

Associations can be **unidirectional** (one object knows about another) or **bidirectional** (both objects know about each other).

### Example: A Library and Books (Bidirectional Association)

```csharp
using System;
using System.Collections.Generic;

class Book {
    public string Title { get; private set; }
    private Library library;
    
    public Book(string title, Library library) {
        Title = title;
        this.library = library;
    }
    
    public void ShowLibrary() {
        Console.WriteLine($"{Title} is in {library.Name}");
    }
}

class Library {
    public string Name { get; private set; }
    private List<Book> books;
    
    public Library(string name) {
        Name = name;
        books = new List<Book>();
    }
    
    public void AddBook(Book book) {
        books.Add(book);
    }
    
    public void ShowBooks() {
        Console.WriteLine($"Books in {Name}:");
        foreach (var book in books) {
            Console.WriteLine($" - {book.Title}");
        }
    }
}

class BidirectionalAssociationExample {
    static void Main() {
        Library library = new Library("City Library");
        Book book1 = new Book("1984", library);
        Book book2 = new Book("Brave New World", library);
        
        library.AddBook(book1);
        library.AddBook(book2);
        
        library.ShowBooks();
        book1.ShowLibrary();
        book2.ShowLibrary();
    }
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