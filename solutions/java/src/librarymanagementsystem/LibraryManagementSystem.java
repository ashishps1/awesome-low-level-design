package librarymanagementsystem;

import librarymanagementsystem.enums.ItemType;
import librarymanagementsystem.factory.ItemFactory;
import librarymanagementsystem.models.BookCopy;
import librarymanagementsystem.models.LibraryItem;
import librarymanagementsystem.models.Member;
import librarymanagementsystem.strategy.SearchStrategy;

import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;
import java.util.Map;

public class LibraryManagementSystem {
    private static final LibraryManagementSystem INSTANCE = new LibraryManagementSystem();
    private final Map<String, LibraryItem> catalog = new HashMap<>();
    private final Map<String, Member> members = new HashMap<>();
    private final Map<String, BookCopy> copies = new HashMap<>();

    private LibraryManagementSystem() {}
    public static LibraryManagementSystem getInstance() { return INSTANCE; }

    // --- Item Management ---
    public List<BookCopy> addItem(ItemType type, String id, String title, String author, int numCopies) {
        List<BookCopy> bookCopies = new ArrayList<>();
        LibraryItem item = ItemFactory.createItem(type, id, title, author);
        catalog.put(id, item);
        for (int i = 0; i < numCopies; i++) {
            String copyId = id + "-c" + (i + 1);
            BookCopy copy = new BookCopy(copyId, item);
            copies.put(copyId, new BookCopy(copyId, item));
            bookCopies.add(copy);
        }
        System.out.println("Added " + numCopies + " copies of '" + title + "'");
        return bookCopies;
    }

    // --- User Management ---
    public Member addMember(String id, String name) {
        Member member = new Member(id, name);
        members.put(id, member);
        return member;
    }

    // --- Core Actions ---
    public void checkout(String memberId, String copyId) {
        Member member = members.get(memberId);
        BookCopy copy = copies.get(copyId);
        if (member != null && copy != null) {
            copy.checkout(member);
        } else {
            System.out.println("Error: Invalid member or copy ID.");
        }
    }

    public void returnItem(String copyId) {
        BookCopy copy = copies.get(copyId);
        if (copy != null) {
            copy.returnItem();
        } else {
            System.out.println("Error: Invalid copy ID.");
        }
    }

    public void placeHold(String memberId, String itemId) {
        Member member = members.get(memberId);
        LibraryItem item = catalog.get(itemId);
        if (member != null && item != null) {
            // Place hold on any copy that is checked out
            item.getCopies().stream()
                    .filter(c -> !c.isAvailable())
                    .findFirst()
                    .ifPresent(copy -> copy.placeHold(member));
        }
    }

    // --- Search (Using Strategy Pattern) ---
    public List<LibraryItem> search(String query, SearchStrategy strategy) {
        return strategy.search(query, new ArrayList<>(catalog.values()));
    }

    public void printCatalog() {
        System.out.println("\n--- Library Catalog ---");
        catalog.values().forEach(item -> System.out.printf("ID: %s, Title: %s, Author/Publisher: %s, Available: %d\n",
                item.getId(), item.getTitle(), item.getAuthorOrPublisher(), item.getAvailableCopyCount()));
        System.out.println("-----------------------\n");
    }
}
