package librarymanagementsystem.models;


import librarymanagementsystem.state.AvailableState;
import librarymanagementsystem.state.ItemState;

public class BookCopy {
    private final String id;
    private final LibraryItem item;
    private ItemState currentState;

    public BookCopy(String id, LibraryItem item) {
        this.id = id;
        this.item = item;
        this.currentState = new AvailableState();
        item.addCopy(this);
    }

    public void checkout(Member member) { currentState.checkout(this, member); }
    public void returnItem() { currentState.returnItem(this); }
    public void placeHold(Member member) { currentState.placeHold(this, member); }

    public void setState(ItemState state) { this.currentState = state; }
    public String getId() { return id; }
    public LibraryItem getItem() { return item; }
    public boolean isAvailable() { return currentState instanceof AvailableState; }
}
