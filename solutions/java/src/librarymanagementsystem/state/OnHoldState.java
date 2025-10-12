package librarymanagementsystem.state;

import librarymanagementsystem.models.BookCopy;
import librarymanagementsystem.models.Member;
import librarymanagementsystem.TransactionService;

public class OnHoldState implements ItemState {
    @Override
    public void checkout(BookCopy copy, Member member) {
        // Only a member who placed the hold can check it out.
        if (copy.getItem().isObserver(member)) {
            TransactionService.getInstance().createLoan(copy, member);
            copy.getItem().removeObserver(member); // Remove from waiting list
            copy.setState(new CheckedOutState());
            System.out.println("Hold fulfilled. " + copy.getId() + " checked out by " + member.getName());
        } else {
            System.out.println("This item is on hold for another member.");
        }
    }

    @Override
    public void returnItem(BookCopy c) {
        System.out.println("Invalid action. Item is on hold, not checked out.");
    }

    @Override
    public void placeHold(BookCopy c, Member m) {
        System.out.println("Item is already on hold.");
    }
}
