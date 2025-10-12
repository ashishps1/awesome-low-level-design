class AlertSubscriber : ISubscriber
{
    private readonly string id;

    public AlertSubscriber(string id)
    {
        this.id = id;
    }

    public string GetId()
    {
        return id;
    }

    public void OnMessage(Message message)
    {
        Console.WriteLine($"!!! [ALERT - {id}] : '{message.GetPayload()}' !!!");
    }
}