class Answer : Post
{
    private bool isAccepted = false;

    public Answer(string body, User author)
        : base(Guid.NewGuid().ToString(), body, author)
    {
    }

    public void SetAccepted(bool accepted)
    {
        isAccepted = accepted;
    }

    public bool IsAcceptedAnswer() { return isAccepted; }
}