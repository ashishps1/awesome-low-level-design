class OnHoldState : IItemState
{
    public void Checkout(BookCopy copy, Member member)
    {
        if (copy.GetItem().IsObserver(member))
        {
            TransactionService.GetInstance().CreateLoan(copy, member);
            copy.GetItem().RemoveObserver(member);
            copy.SetState(new CheckedOutState());
            Console.WriteLine($"Hold fulfilled. {copy.GetId()} checked out by {member.GetName()}");
        }
        else
        {
            Console.WriteLine("This item is on hold for another member.");
        }
    }

    public void ReturnItem(BookCopy copy)
    {
        Console.WriteLine("Invalid action. Item is on hold, not checked out.");
    }

    public void PlaceHold(BookCopy copy, Member member)
    {
        Console.WriteLine("Item is already on hold.");
    }
}