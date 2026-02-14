/*
 * AGGREGATION IN RUST
 *
 * Goal: Demonstrate Independent Lifecycles using References and Lifetimes.
 * Scenario: A Library (Container) holds references to Books (Independent Objects).
 */

#[derive(Debug)]
struct Book {
    title: String,
    author: String,
}

impl Book {
    fn new(title: &str, author: &str) -> Self {
        Book {
            title: title.to_string(),
            author: author.to_string(),
        }
    }

    fn read(&self) {
        println!("  Reading '{}' by {}...", self.title, self.author);
    }
}

// THE CONTAINER (AGGREGATION)
// <'a> ensures Library cannot outlive the Books it holds.
struct Library<'a> {
    name: String,
    // Aggregation: Library 'has' books, but does not 'own' them.
    collection: Vec<&'a Book>,
}

impl<'a> Library<'a> {
    fn new(name: &str) -> Self {
        Library {
            name: name.to_string(),
            collection: Vec::new(),
        }
    }

    // We take a reference with lifetime 'a
    fn add_book(&mut self, book: &'a Book) {
        self.collection.push(book);
    }

    fn list_books(&self) {
        println!("Library '{}' contains:", self.name);
        for book in &self.collection {
            book.read();
        }
    }
}

// ADVANCED: SHARED AGGREGATION (Rc)
use std::rc::Rc;

struct Reader {
    name: String,
    // Multiple readers can hold the SAME book
    favorite_book: Rc<Book>, 
}

fn main() {
    println!("--- 1. Standard Aggregation (References & Lifetimes) ---");

    // STEP A: Create the Independent Objects (Books)
    // These live in the 'main' scope.
    let book1 = Book::new("The Rust Book", "Steve Klabnik");
    let book2 = Book::new("Clean Code", "Robert C. Martin");

    {
        // STEP B: Create the Container (Library) inside a smaller scope
        let mut my_library = Library::new("City Central Lib");

        // STEP C: Aggregate (Borrow the books)
        my_library.add_book(&book1);
        my_library.add_book(&book2);

        my_library.list_books();

        println!("--- Library is closing (Variable 'my_library' dropped) ---");
    } // 'my_library' dies here.

    // STEP D: Verify Independence
    // The library is gone, but the books are still here!
    println!("Verification: '{}' is still on my shelf at home.", book1.title);


    println!("\n--- 2. Shared Aggregation (Rc Smart Pointer) ---");
    
    // We wrap a book in Rc (Reference Counted)
    let shared_book = Rc::new(Book::new("Design Patterns", "Gang of Four"));

    let reader1 = Reader { name: "Alice".into(), favorite_book: Rc::clone(&shared_book) };
    let reader2 = Reader { name: "Bob".into(), favorite_book: Rc::clone(&shared_book) };

    println!("{} loves {}.", reader1.name, reader1.favorite_book.title);
    println!("{} also loves {}.", reader2.name, reader2.favorite_book.title);
    
    // The book stays alive as long as EITHER Alice OR Bob (or the original var) holds it.
}

