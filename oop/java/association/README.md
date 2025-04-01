# Association in Object-Oriented Programming (OOP)

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

```java
import java.util.*;

class Teacher {
    private String name;
    private List<Student> students;
    
    public Teacher(String name) {
        this.name = name;
        this.students = new ArrayList<>();
    }
    
    public void addStudent(Student student) {
        students.add(student);
    }
    
    public void showStudents() {
        System.out.println(name + " teaches:");
        for (Student student : students) {
            System.out.println(" - " + student.getName());
        }
    }
    
    public String getName() {
        return name;
    }
}

class Student {
    private String name;
    
    public Student(String name) {
        this.name = name;
    }
    
    public String getName() {
        return name;
    }
}

public class AssociationExample {
    public static void main(String[] args) {
        Teacher teacher1 = new Teacher("Mr. Smith");
        Teacher teacher2 = new Teacher("Mrs. Johnson");
        
        Student student1 = new Student("Alice");
        Student student2 = new Student("Bob");
        
        teacher1.addStudent(student1);
        teacher1.addStudent(student2);
        teacher2.addStudent(student2);
        
        teacher1.showStudents();
        teacher2.showStudents();
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

```java
import java.util.*;

class Book {
    private String title;
    private Library library;
    
    public Book(String title, Library library) {
        this.title = title;
        this.library = library;
    }
    
    public void showLibrary() {
        System.out.println(title + " is in " + library.getName());
    }
    
    public String getTitle() {
        return title;
    }
}

class Library {
    private String name;
    private List<Book> books;
    
    public Library(String name) {
        this.name = name;
        this.books = new ArrayList<>();
    }
    
    public void addBook(Book book) {
        books.add(book);
    }
    
    public String getName() {
        return name;
    }
    
    public void showBooks() {
        System.out.println("Books in " + name + ":");
        for (Book book : books) {
            System.out.println(" - " + book.getTitle());
        }
    }
}

public class BidirectionalAssociationExample {
    public static void main(String[] args) {
        Library library = new Library("City Library");
        Book book1 = new Book("1984", library);
        Book book2 = new Book("Brave New World", library);
        
        library.addBook(book1);
        library.addBook(book2);
        
        library.showBooks();
        book1.showLibrary();
        book2.showLibrary();
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