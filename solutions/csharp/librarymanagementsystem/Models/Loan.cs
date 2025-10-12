class Loan
{
    private readonly BookCopy copy;
    private readonly Member member;
    private readonly DateTime checkoutDate;

    public Loan(BookCopy copy, Member member)
    {
        this.copy = copy;
        this.member = member;
        this.checkoutDate = DateTime.Now;
    }

    public BookCopy GetCopy() { return copy; }
    public Member GetMember() { return member; }
}