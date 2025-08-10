class AvailableState : IItemState
{
    public void Checkout(BookCopy copy, Member member)
    {
        TransactionService.GetInstance().CreateLoan(copy, member);
        copy.SetState(new CheckedOutState());
        Console.WriteLine($"{copy.GetId()} checked out by {member.GetName()}");
    }

    public void ReturnItem(BookCopy copy)
    {
        Console.WriteLine("Cannot return an item that is already available.");
    }

    public void PlaceHold(BookCopy copy, Member member)
    {
        Console.WriteLine("Cannot place hold on an available item. Please check it out.");
    }
}