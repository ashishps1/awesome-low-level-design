package librarymanagementsystem.patterns.observer;

import librarymanagementsystem.models.Book;
import java.util.ArrayList;
import java.util.List;

/**
 * Concrete Subject - Book notifies observers when available.
 * Implements Observer Design Pattern
 */
public class BookSubject implements Subject {
    private final Book book;
    private final List<Observer> observers;
    
    public BookSubject(Book book) {
        this.book = book;
        this.observers = new ArrayList<>();
    }
    
    @Override
    public void attach(Observer observer) {
        if (!observers.contains(observer)) {
            observers.add(observer);