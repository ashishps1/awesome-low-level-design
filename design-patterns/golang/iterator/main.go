package iterator

import "fmt"

func main() {
	// Create a book collection
	collection := NewBookCollection()

	// Add some books to the collection
	collection.AddBook(NewBook("The Great Gatsby", "F. Scott Fitzgerald"))
	collection.AddBook(NewBook("To Kill a Mockingbird", "Harper Lee"))
	collection.AddBook(NewBook("1984", "George Orwell"))

	// Create an iterator for the collection
	iterator := collection.CreateIterator()

	// Iterate through the books
	fmt.Println("Iterating through the book collection:")
	for iterator.HasNext() {
		book := iterator.Next().(*Book)
		fmt.Printf("Book: %s by %s\n", book.Title, book.Author)
	}
}
