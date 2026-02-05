// MagazineItem.java
package librarymanagementsystem.patterns.factory;

/**
 * Concrete product - Magazine implementation.
 * Part of Factory Design Pattern
 */
public class MagazineItem implements LibraryItem {
    private final String issueNumber;
    private final String title;
    private boolean available;
    
    public MagazineItem(String issueNumber, String title) {
        this.issueNumber = issueNumber;
        this.title = title;
        this.available = true;
    }
    
    @Override
    public String getItemId() {
        return issueNumber;
    }
    
    @Override
    public String getTitle() {
        return title;
    }
    
    @Override
    public String getItemType() {
        return "MAGAZINE";
    }
    
    @Override
    public double calculateLateFee(int daysLate) {
        return daysLate * 0.25; // $0.25 per day for magazines
    }
    
    @Override
    public boolean isAvailable() {
        return available;
    }
    
    public void setAvailable(boolean available) {
        this.available = available;
    }
}