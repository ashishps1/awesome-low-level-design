package librarymanagementsystem;

import librarymanagementsystem.enums.ItemType;
import librarymanagementsystem.models.BookCopy;
import librarymanagementsystem.models.Member;
import librarymanagementsystem.strategy.SearchByAuthorStrategy;
import librarymanagementsystem.strategy.SearchByTitleStrategy;

import java.util.List;

public class LibraryManagementDemo {
    public static void main(String[] args) {
        LibraryManagementSystem library = LibraryManagementSystem.getInstance();

        // --- Setup: Add items and members using the Facade ---
        System.out.println("=== Setting up the Library ===");

        List<BookCopy> hobbitCopies = library.addItem(ItemType.BOOK, "B001", "The Hobbit", "J.R.R. Tolkien", 2);
        List<BookCopy> duneCopies = library.addItem(ItemType.BOOK, "B002", "Dune", "Frank Herbert", 1);
        List<BookCopy> natGeoCopies = library.addItem(ItemType.MAGAZINE, "M001", "National Geographic", "NatGeo Society", 3);

        Member alice = library.addMember("MEM01", "Alice");
        Member bob = library.addMember("MEM02", "Bob");
        Member charlie = library.addMember("MEM03", "Charlie");
        library.printCatalog();

        // --- Scenario 1: Searching (Strategy Pattern) ---
        System.out.println("\n=== Scenario 1: Searching for Items ===");
        System.out.println("Searching for title 'Dune':");
        library.search("Dune", new SearchByTitleStrategy())
                .forEach(item -> System.out.println("Found: " + item.getTitle()));
        System.out.println("\nSearching for author 'Tolkien':");
        library.search("Tolkien", new SearchByAuthorStrategy())
                .forEach(item -> System.out.println("Found: " + item.getTitle()));

        // --- Scenario 2: Checkout and Return (State Pattern) ---
        System.out.println("\n\n=== Scenario 2: Checkout and Return ===");
        library.checkout(alice.getId(), hobbitCopies.get(0).getId()); // Alice checks out The Hobbit copy 1
        library.checkout(bob.getId(), duneCopies.get(0).getId()); // Bob checks out Dune copy 1
        library.printCatalog();

        System.out.println("Attempting to checkout an already checked-out book:");
        library.checkout(charlie.getId(), hobbitCopies.get(0).getId()); // Charlie fails to check out The Hobbit copy 1

        System.out.println("\nAlice returns The Hobbit:");
        library.returnItem(hobbitCopies.get(0).getId());
        library.printCatalog();

        // --- Scenario 3: Holds and Notifications (Observer Pattern) ---
        System.out.println("\n\n=== Scenario 3: Placing a Hold ===");
        System.out.println("Dune is checked out by Bob. Charlie places a hold.");
        library.placeHold(charlie.getId(), "B002"); // Charlie places a hold on Dune

        System.out.println("\nBob returns Dune. Charlie should be notified.");
        library.returnItem(duneCopies.get(0).getId()); // Bob returns Dune

        System.out.println("\nCharlie checks out the book that was on hold for him.");
        library.checkout(charlie.getId(), duneCopies.get(0).getId());

        System.out.println("\nTrying to check out the same on-hold item by another member (Alice):");
        library.checkout(alice.getId(), duneCopies.get(0).getId()); // Alice fails, it's checked out by Charlie now.

        library.printCatalog();
    }
}
