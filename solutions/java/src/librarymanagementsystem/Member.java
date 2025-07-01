package librarymanagementsystem;

import java.util.ArrayList;
import java.util.Collections;
import java.util.List;
import java.util.UUID;

public class Member {
    private final String id;
    private final String name;
    private final String contactInfo;
    private final List<Loan> loans;

    public Member(String name, String contactInfo) {
        this.id = UUID.randomUUID().toString();
        this.name = name;
        this.contactInfo = contactInfo;
        this.loans = Collections.synchronizedList(new ArrayList<>());
    }

    public int getBorrowedCount() { return loans.size(); }

    public synchronized void addLoan(Loan loan) {
        loans.add(loan);
    }

    public synchronized void removeLoan(Loan loan) {
        loans.remove(loan);
    }

    public List<Loan> getLoans() {
        return loans;
    }

    public String getId() {
        return id;
    }

    public String getName() {
        return name;
    }
}
