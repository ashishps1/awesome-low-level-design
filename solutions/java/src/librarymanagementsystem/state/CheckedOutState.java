package librarymanagementsystem.state;

import librarymanagementsystem.models.BookCopy;
import librarymanagementsystem.models.Member;
import librarymanagementsystem.TransactionService;

public class CheckedOutState implements ItemState {
    @Override public void checkout(BookCopy c, Member m) { System.out.println(c.getId() + " is already checked out."); }

    @Override
    public void returnItem(BookCopy copy) {
        TransactionService.getInstance().endLoan(copy);
        System.out.println(copy.getId() + " returned.");
        // If there are holds, move to OnHold state. Otherwise, become Available.
        if (copy.getItem().hasObservers()) {
            copy.setState(new OnHoldState());
            copy.getItem().notifyObservers(); // Notify members that item is back but on hold
        } else {
            copy.setState(new AvailableState());
        }
    }

    @Override
    public void placeHold(BookCopy copy, Member member) {
        copy.getItem().addObserver(member);
        System.out.println(member.getName() + " placed a hold on '" + copy.getItem().getTitle() + "'");
    }
}
