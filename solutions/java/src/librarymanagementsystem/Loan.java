package librarymanagementsystem;

import java.time.LocalDate;
import java.util.UUID;

public class Loan {
    private final String id;
    private final BookCopy copy;
    private final Member member;
    private final LocalDate borrowDate;
    private final LocalDate dueDate;
    private boolean active = true;
    private static final int MAX_BORROW_DAYS = 14;

    public Loan(BookCopy copy, Member member) {
        this.id = UUID.randomUUID().toString();
        this.copy = copy;
        this.member = member;
        this.borrowDate = LocalDate.now();
        this.dueDate = borrowDate.plusDays(MAX_BORROW_DAYS);
    }

    public void closeLoan() {
        copy.markReturned();
        member.removeLoan(this);
        active = false;
    }

    public String getId() {
        return id;
    }
}
