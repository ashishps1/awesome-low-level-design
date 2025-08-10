class Connection
{
    private readonly Member fromMember;
    private readonly Member toMember;
    private ConnectionStatus status;
    private readonly DateTime requestedAt;
    private DateTime acceptedAt;

    public Connection(Member fromMember, Member toMember)
    {
        this.fromMember = fromMember;
        this.toMember = toMember;
        this.status = ConnectionStatus.PENDING;
        this.requestedAt = DateTime.Now;
    }

    public Member GetFromMember() { return fromMember; }
    public Member GetToMember() { return toMember; }
    public ConnectionStatus GetStatus() { return status; }

    public void SetStatus(ConnectionStatus status)
    {
        this.status = status;
        if (status == ConnectionStatus.ACCEPTED)
        {
            this.acceptedAt = DateTime.Now;
        }
    }
}