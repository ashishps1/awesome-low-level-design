package librarymanagementsystem.models;

import java.util.ArrayList;
import java.util.List;

public abstract class LibraryItem {
    private final String id;
    private final String title;
    protected final List<BookCopy> copies = new ArrayList<>();
    // Observer Pattern: List of members waiting for this item
    private final List<Member> observers = new ArrayList<>();

    public LibraryItem(String id, String title) {
        this.id = id;
        this.title = title;
    }

    public void addCopy(BookCopy copy) { this.copies.add(copy); }
    public void addObserver(Member member) { observers.add(member); }
    public void removeObserver(Member member) { observers.remove(member); }

    public void notifyObservers() {
        System.out.println("Notifying " + observers.size() + " observers for '" + title + "'...");
        // Use a copy to avoid ConcurrentModificationException if observer unsubscribes
        new ArrayList<>(observers).forEach(observer -> observer.update(this));
    }

    public BookCopy getAvailableCopy() {
        return copies.stream()
                .filter(BookCopy::isAvailable)
                .findFirst()
                .orElse(null);
    }

    // Getters
    public String getId() { return id; }
    public String getTitle() { return title; }

    public List<BookCopy> getCopies() {
        return copies;
    }

    public abstract String getAuthorOrPublisher();
    public long getAvailableCopyCount() {
        return copies.stream().filter(BookCopy::isAvailable).count();
    }

    public boolean hasObservers() { return !observers.isEmpty(); }
    public boolean isObserver(Member member) { return observers.contains(member); }
}
