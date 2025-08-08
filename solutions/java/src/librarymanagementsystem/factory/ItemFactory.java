package librarymanagementsystem.factory;

import librarymanagementsystem.enums.ItemType;
import librarymanagementsystem.models.Book;
import librarymanagementsystem.models.LibraryItem;
import librarymanagementsystem.models.Magazine;

public class ItemFactory {
    public static LibraryItem createItem(ItemType type, String id, String title, String author) {
        switch (type) {
            case BOOK: return new Book(id, title, author);
            case MAGAZINE: return new Magazine(id, title, author); // Author might be publisher here
            default: throw new IllegalArgumentException("Unknown item type.");
        }
    }
}
