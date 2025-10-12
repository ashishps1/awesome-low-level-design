package librarymanagementsystem.state;

import librarymanagementsystem.models.BookCopy;
import librarymanagementsystem.models.Member;

public interface ItemState {
    void checkout(BookCopy copy, Member member);
    void returnItem(BookCopy copy);
    void placeHold(BookCopy copy, Member member);
}
