package librarymanagementsystem;

import java.util.ArrayList;
import java.util.Collections;
import java.util.List;
import java.util.UUID;

public class Member {
    private final String id;
    private final String name;
    private final String contactInfo;
    private final List<Loan> currentLoans;
    private static final int MAX_BOOKS = 5;

    public Member(String name, String contactInfo) {
        this.id = UUID.randomUUID().toString();
        this.name = name;
        this.contactInfo = contactInfo;
        this.currentLoans = Collections.synchronizedList(new ArrayList<>());
    }

    public synchronized boolean canBorrow() {
        return currentLoans.size() < MAX_BOOKS;
    }

    public synchronized void addLoan(Loan loan) {
        currentLoans.add(loan);
    }

    public synchronized void removeLoan(Loan loan) {
        currentLoans.remove(loan);
    }

    public String getId() {
        return id;
    }

    public String getName() {
        return name;
    }
}
