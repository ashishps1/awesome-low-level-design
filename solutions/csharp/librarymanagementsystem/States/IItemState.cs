interface IItemState
{
    void Checkout(BookCopy copy, Member member);
    void ReturnItem(BookCopy copy);
    void PlaceHold(BookCopy copy, Member member);
}