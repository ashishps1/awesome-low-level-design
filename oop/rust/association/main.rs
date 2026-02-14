/*
 * ASSOCIATION IN RUST
 * * Scenario 1: Unidirectional (One-to-Many) using Rc.
 * Scenario 2: Bidirectional (Many-to-Many) using Rc, Weak, and RefCell.
 *
 * NOTE: This uses advanced smart pointers to replicate Java's flexible references.
 */

use std::rc::{Rc, Weak};
use std::cell::RefCell;

// ==========================================
// SCENARIO 1: UNIDIRECTIONAL (Teacher -> Student)
// Multiple Teachers share the SAME Students.
// ==========================================

#[derive(Debug)]
struct Student {
    name: String,
}

struct Teacher {
    name: String,
    // We use Rc so multiple teachers can refer to the SAME student instance
    students: Vec<Rc<Student>>,
}

impl Teacher {
    fn new(name: &str) -> Self {
        Teacher {
            name: name.to_string(),
            students: Vec::new(),
        }
    }

    fn add_student(&mut self, student: Rc<Student>) {
        self.students.push(student);
    }

    fn show_students(&self) {
        println!("{} teaches:", self.name);
        for s in &self.students {
            // Rc auto-dereferences to the inner Student
            println!(" - {}", s.name);
        }
    }
}

// ==========================================
// SCENARIO 2: BIDIRECTIONAL (Library <-> Book)
// Library owns Books. Books know their Library.
// ==========================================

// We need RefCell to allow mutation (adding books) after creation
struct Library {
    name: String,
    books: RefCell<Vec<Rc<Book>>>, // Library owns Books (Strong)
}

struct Book {
    title: String,
    // Book holds a WEAK reference to Library to prevent memory leaks (Cycles)
    library: Weak<Library>, 
}

impl Library {
    // Returns Rc<Library> so it can be shared with Books
    fn new(name: &str) -> Rc<Self> {
        Rc::new(Library {
            name: name.to_string(),
            books: RefCell::new(Vec::new()),
        })
    }

    fn add_book(library: &Rc<Library>, title: &str) {
        // Create the book with a Weak pointer back to the Library
        let book = Rc::new(Book {
            title: title.to_string(),
            library: Rc::downgrade(library), // Convert Strong Rc to Weak
        });

        // Add to library's list (using borrow_mut because of RefCell)
        library.books.borrow_mut().push(book);
    }

    fn show_books(&self) {
        println!("Books in {}:", self.name);
        for book in self.books.borrow().iter() {
            println!(" - {}", book.title);
        }
    }
}

impl Book {
    fn show_library(&self) {
        // We must attempt to "upgrade" the weak pointer to see if the Library still exists
        match self.library.upgrade() {
            Some(lib) => println!("'{}' belongs to library: {}", self.title, lib.name),
            None => println!("'{}' belongs to a library that no longer exists!", self.title),
        }
    }
}

fn main() {
    println!("--- 1. Unidirectional Association (Shared Ownership) ---");
    
    // 1. Create Students (Wrapped in Rc for sharing)
    let s1 = Rc::new(Student { name: "Alice".into() });
    let s2 = Rc::new(Student { name: "Bob".into() });

    // 2. Create Teachers
    let mut t1 = Teacher::new("Mr. Smith");
    let mut t2 = Teacher::new("Mrs. Johnson");

    // 3. Associate (Cloning Rc just increases the reference count, not memory)
    t1.add_student(Rc::clone(&s1)); // Alice -> Smith
    t1.add_student(Rc::clone(&s2)); // Bob -> Smith
    t2.add_student(Rc::clone(&s2)); // Bob -> Johnson (Shared!)

    t1.show_students();
    t2.show_students();

    // Proof of shared memory:
    // Rc::strong_count(&s2) would be 3 (Original + Teacher1 + Teacher2)


    println!("\n--- 2. Bidirectional Association (Weak Pointers) ---");
    
    // 1. Create the Library
    let city_lib = Library::new("City Library");

    // 2. Add Books (Internally links Book -> Library)
    Library::add_book(&city_lib, "1984");
    Library::add_book(&city_lib, "Brave New World");

    // 3. Show relations
    city_lib.show_books();

    // Accessing the books to show their library
    let books = city_lib.books.borrow();
    for b in books.iter() {
        b.show_library();
    }

    println!("\n--- 3. Testing Lifecycle (Weak Pointer Safety) ---");
    // Create a temporary library scope
    let floating_book = {
        let temp_lib = Library::new("Temporary Pop-up Library");
        Library::add_book(&temp_lib, "Temporary Manual");
        
        // We clone the book out of the library
        let book_ref = Rc::clone(&temp_lib.books.borrow()[0]);
        book_ref // Return the book, but the Library gets dropped here
    };

    println!("The book '{}' still exists...", floating_book.title);
    // This should fail gracefully because the Library is dead
    floating_book.show_library(); 
}