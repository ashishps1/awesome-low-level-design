package librarymanagementsystem.state;

import librarymanagementsystem.models.BookCopy;
import librarymanagementsystem.models.Member;
import librarymanagementsystem.TransactionService;

public class AvailableState implements ItemState {
    @Override
    public void checkout(BookCopy copy, Member member) {
        TransactionService.getInstance().createLoan(copy, member);
        copy.setState(new CheckedOutState());
        System.out.println(copy.getId() + " checked out by " + member.getName());
    }

    @Override
    public void returnItem(BookCopy c) {
        System.out.println("Cannot return an item that is already available.");
    }

    @Override
    public void placeHold(BookCopy c, Member m) {
        System.out.println("Cannot place hold on an available item. Please check it out.");
    }
}
