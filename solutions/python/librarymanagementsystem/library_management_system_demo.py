from library_management_system import LibraryManagementSystem
from item_type import ItemType
from search_strategy import SearchByTitleStrategy, SearchByAuthorStrategy

class LibraryManagementDemo:
    @staticmethod
    def main():
        library = LibraryManagementSystem.get_instance()

        # === Setup: Add items and members using the Facade ===
        print("=== Setting up the Library ===")

        hobbit_copies = library.add_item(ItemType.BOOK, "B001", "The Hobbit", "J.R.R. Tolkien", 2)
        dune_copies = library.add_item(ItemType.BOOK, "B002", "Dune", "Frank Herbert", 1)
        nat_geo_copies = library.add_item(ItemType.MAGAZINE, "M001", "National Geographic", "NatGeo Society", 3)

        alice = library.add_member("MEM01", "Alice")
        bob = library.add_member("MEM02", "Bob")
        charlie = library.add_member("MEM03", "Charlie")
        library.print_catalog()

        # === Scenario 1: Searching (Strategy Pattern) ===
        print("\n=== Scenario 1: Searching for Items ===")
        print("Searching for title 'Dune':")
        for item in library.search("Dune", SearchByTitleStrategy()):
            print(f"Found: {item.get_title()}")
        
        print("\nSearching for author 'Tolkien':")
        for item in library.search("Tolkien", SearchByAuthorStrategy()):
            print(f"Found: {item.get_title()}")

        # === Scenario 2: Checkout and Return (State Pattern) ===
        print("\n\n=== Scenario 2: Checkout and Return ===")
        library.checkout(alice.get_id(), hobbit_copies[0].get_id())  # Alice checks out The Hobbit copy 1
        library.checkout(bob.get_id(), dune_copies[0].get_id())     # Bob checks out Dune copy 1
        library.print_catalog()

        print("Attempting to checkout an already checked-out book:")
        library.checkout(charlie.get_id(), hobbit_copies[0].get_id())  # Charlie fails to check out The Hobbit copy 1

        print("\nAlice returns The Hobbit:")
        library.return_item(hobbit_copies[0].get_id())
        library.print_catalog()

        # === Scenario 3: Holds and Notifications (Observer Pattern) ===
        print("\n\n=== Scenario 3: Placing a Hold ===")
        print("Dune is checked out by Bob. Charlie places a hold.")
        library.place_hold(charlie.get_id(), "B002")  # Charlie places a hold on Dune

        print("\nBob returns Dune. Charlie should be notified.")
        library.return_item(dune_copies[0].get_id())  # Bob returns Dune

        print("\nCharlie checks out the book that was on hold for him.")
        library.checkout(charlie.get_id(), dune_copies[0].get_id())

        print("\nTrying to check out the same on-hold item by another member (Alice):")
        library.checkout(alice.get_id(), dune_copies[0].get_id())  # Alice fails, it's checked out by Charlie now.

        library.print_catalog()


if __name__ == "__main__":
    LibraryManagementDemo.main()