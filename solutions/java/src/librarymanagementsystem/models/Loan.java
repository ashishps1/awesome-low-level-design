package librarymanagementsystem.models;

import java.time.LocalDate;

public class Loan {
    private final BookCopy copy;
    private final Member member;
    private final LocalDate checkoutDate;

    public Loan(BookCopy copy, Member member) {
        this.copy = copy;
        this.member = member;
        this.checkoutDate = LocalDate.now();
    }

    public BookCopy getCopy() { return copy; }
    public Member getMember() { return member; }
}