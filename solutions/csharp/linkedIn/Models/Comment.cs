class Comment
{
    private readonly Member author;
    private readonly string text;
    private readonly DateTime createdAt;

    public Comment(Member author, string text)
    {
        this.author = author;
        this.text = text;
        this.createdAt = DateTime.Now;
    }

    public Member GetAuthor() { return author; }
    public string GetText() { return text; }
}