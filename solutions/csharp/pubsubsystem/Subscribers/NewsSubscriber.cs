class NewsSubscriber : ISubscriber
{
    private readonly string id;

    public NewsSubscriber(string id)
    {
        this.id = id;
    }

    public string GetId()
    {
        return id;
    }

    public void OnMessage(Message message)
    {
        Console.WriteLine($"[Subscriber {id}] received message '{message.GetPayload()}'");
    }
}