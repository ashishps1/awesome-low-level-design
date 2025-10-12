package librarymanagementsystem.strategy;

import librarymanagementsystem.models.LibraryItem;

import java.util.List;

public interface SearchStrategy {
    List<LibraryItem> search(String query, List<LibraryItem> items);
}
