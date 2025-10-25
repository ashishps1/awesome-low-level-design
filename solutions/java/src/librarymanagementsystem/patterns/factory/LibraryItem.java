// LibraryItem.java
package librarymanagementsystem.patterns.factory;

/**
 * Abstract product for Factory Pattern.
 * Follows OCP - Open for extension, closed for modification
 */
public interface LibraryItem {
    String getItemId();
    String getTitle();
    String getItemType();
    double calculateLateFee(int daysLate);
    boolean isAvailable();
}