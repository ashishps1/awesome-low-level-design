abstract class Content
{
    protected readonly string id;
    protected readonly string body;
    protected readonly User author;
    protected readonly DateTime creationTime;

    public Content(string id, string body, User author)
    {
        this.id = id;
        this.body = body;
        this.author = author;
        this.creationTime = DateTime.Now;
    }

    public string GetId() { return id; }
    public string GetBody() { return body; }
    public User GetAuthor() { return author; }
}