class CheckedOutState : IItemState
{
    public void Checkout(BookCopy copy, Member member)
    {
        Console.WriteLine($"{copy.GetId()} is already checked out.");
    }

    public void ReturnItem(BookCopy copy)
    {
        TransactionService.GetInstance().EndLoan(copy);
        Console.WriteLine($"{copy.GetId()} returned.");
        
        if (copy.GetItem().HasObservers())
        {
            copy.SetState(new OnHoldState());
            copy.GetItem().NotifyObservers();
        }
        else
        {
            copy.SetState(new AvailableState());
        }
    }

    public void PlaceHold(BookCopy copy, Member member)
    {
        copy.GetItem().AddObserver(member);
        Console.WriteLine($"{member.GetName()} placed a hold on '{copy.GetItem().GetTitle()}'");
    }
}