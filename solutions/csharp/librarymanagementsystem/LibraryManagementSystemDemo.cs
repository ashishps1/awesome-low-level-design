using System;
using System.Collections.Generic;
using System.Linq;

public class LibraryManagementDemo
{
    public static void Main(string[] args)
    {
        var library = LibraryManagementSystem.GetInstance();

        // === Setting up the Library ===
        Console.WriteLine("=== Setting up the Library ===");

        var hobbitCopies = library.AddItem(ItemType.BOOK, "B001", "The Hobbit", "J.R.R. Tolkien", 2);
        var duneCopies = library.AddItem(ItemType.BOOK, "B002", "Dune", "Frank Herbert", 1);
        var natGeoCopies = library.AddItem(ItemType.MAGAZINE, "M001", "National Geographic", "NatGeo Society", 3);

        var alice = library.AddMember("MEM01", "Alice");
        var bob = library.AddMember("MEM02", "Bob");
        var charlie = library.AddMember("MEM03", "Charlie");
        library.PrintCatalog();

        // === Scenario 1: Searching (Strategy Pattern) ===
        Console.WriteLine("\n=== Scenario 1: Searching for Items ===");
        Console.WriteLine("Searching for title 'Dune':");
        var titleResults = library.Search("Dune", new SearchByTitleStrategy());
        foreach (var item in titleResults)
        {
            Console.WriteLine($"Found: {item.GetTitle()}");
        }

        Console.WriteLine("\nSearching for author 'Tolkien':");
        var authorResults = library.Search("Tolkien", new SearchByAuthorStrategy());
        foreach (var item in authorResults)
        {
            Console.WriteLine($"Found: {item.GetTitle()}");
        }

        // === Scenario 2: Checkout and Return (State Pattern) ===
        Console.WriteLine("\n\n=== Scenario 2: Checkout and Return ===");
        library.Checkout(alice.GetId(), hobbitCopies[0].GetId());
        library.Checkout(bob.GetId(), duneCopies[0].GetId());
        library.PrintCatalog();

        Console.WriteLine("Attempting to checkout an already checked-out book:");
        library.Checkout(charlie.GetId(), hobbitCopies[0].GetId());

        Console.WriteLine("\nAlice returns The Hobbit:");
        library.ReturnItem(hobbitCopies[0].GetId());
        library.PrintCatalog();

        // === Scenario 3: Holds and Notifications (Observer Pattern) ===
        Console.WriteLine("\n\n=== Scenario 3: Placing a Hold ===");
        Console.WriteLine("Dune is checked out by Bob. Charlie places a hold.");
        library.PlaceHold(charlie.GetId(), "B002");

        Console.WriteLine("\nBob returns Dune. Charlie should be notified.");
        library.ReturnItem(duneCopies[0].GetId());

        Console.WriteLine("\nCharlie checks out the book that was on hold for him.");
        library.Checkout(charlie.GetId(), duneCopies[0].GetId());

        Console.WriteLine("\nTrying to check out the same on-hold item by another member (Alice):");
        library.Checkout(alice.GetId(), duneCopies[0].GetId());

        library.PrintCatalog();
    }
}