class Like
{
    private readonly Member member;
    private readonly DateTime createdAt;

    public Like(Member member)
    {
        this.member = member;
        this.createdAt = DateTime.Now;
    }

    public Member GetMember() { return member; }
}