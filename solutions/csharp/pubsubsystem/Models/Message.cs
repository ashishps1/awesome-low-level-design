class Message
{
    private readonly string payload;
    private readonly DateTime timestamp;

    public Message(string payload)
    {
        this.payload = payload;
        this.timestamp = DateTime.Now;
    }

    public string GetPayload()
    {
        return payload;
    }

    public override string ToString()
    {
        return $"Message{{payload='{payload}'}}";
    }
}