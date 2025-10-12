package librarymanagementsystem.strategy;

import librarymanagementsystem.models.LibraryItem;

import java.util.ArrayList;
import java.util.List;

public class SearchByTitleStrategy implements SearchStrategy {
    @Override
    public List<LibraryItem> search(String query, List<LibraryItem> items) {
        List<LibraryItem> result = new ArrayList<>();
        items.stream()
                .filter(item -> item.getTitle().toLowerCase().contains(query.toLowerCase()))
                .forEach(result::add);
        return result;
    }
}
