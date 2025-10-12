class Notification
{
    private readonly string id;
    private readonly string memberId;
    private readonly NotificationType type;
    private readonly string content;
    private readonly DateTime createdAt;
    private bool isRead = false;

    public Notification(string memberId, NotificationType type, string content)
    {
        this.id = Guid.NewGuid().ToString();
        this.memberId = memberId;
        this.type = type;
        this.content = content;
        this.createdAt = DateTime.Now;
    }

    public string GetContent() { return content; }
    public void MarkAsRead() { isRead = true; }
    public bool IsRead() { return isRead; }
}