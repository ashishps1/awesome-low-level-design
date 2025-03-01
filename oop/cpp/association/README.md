# Association in C++

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

```cpp
#include <iostream>
#include <vector>
#include <string>
using namespace std;

class Student;

class Teacher {
private:
    string name;
    vector<Student*> students;
public:
    Teacher(string name) : name(name) {}
    void addStudent(Student* student);
    void showStudents();
    string getName() { return name; }
};

class Student {
private:
    string name;
public:
    Student(string name) : name(name) {}
    string getName() { return name; }
};

void Teacher::addStudent(Student* student) {
    students.push_back(student);
}

void Teacher::showStudents() {
    cout << name << " teaches:" << endl;
    for (Student* student : students) {
        cout << " - " << student->getName() << endl;
    }
}

int main() {
    Teacher teacher1("Mr. Smith");
    Teacher teacher2("Mrs. Johnson");
    
    Student student1("Alice");
    Student student2("Bob");
    
    teacher1.addStudent(&student1);
    teacher1.addStudent(&student2);
    teacher2.addStudent(&student2);
    
    teacher1.showStudents();
    teacher2.showStudents();
    
    return 0;
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

```cpp
#include <iostream>
#include <vector>
#include <string>
using namespace std;

class Library;

class Book {
private:
    string title;
    Library* library;
public:
    Book(string title, Library* library);
    void showLibrary();
    string getTitle() { return title; }
};

class Library {
private:
    string name;
    vector<Book*> books;
public:
    Library(string name) : name(name) {}
    void addBook(Book* book) { books.push_back(book); }
    string getName() { return name; }
    void showBooks();
};

Book::Book(string title, Library* library) : title(title), library(library) {}

void Book::showLibrary() {
    cout << title << " is in " << library->getName() << endl;
}

void Library::showBooks() {
    cout << "Books in " << name << ":" << endl;
    for (Book* book : books) {
        cout << " - " << book->getTitle() << endl;
    }
}

int main() {
    Library library("City Library");
    Book book1("1984", &library);
    Book book2("Brave New World", &library);
    
    library.addBook(&book1);
    library.addBook(&book2);
    
    library.showBooks();
    book1.showLibrary();
    book2.showLibrary();
    
    return 0;
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