class Topic
{
    private readonly string name;
    private readonly HashSet<ISubscriber> subscribers;
    private readonly object subscribersLock = new object();

    public Topic(string name)
    {
        this.name = name;
        this.subscribers = new HashSet<ISubscriber>();
    }

    public string GetName()
    {
        return name;
    }

    public void AddSubscriber(ISubscriber subscriber)
    {
        lock (subscribersLock)
        {
            subscribers.Add(subscriber);
        }
    }

    public void RemoveSubscriber(ISubscriber subscriber)
    {
        lock (subscribersLock)
        {
            subscribers.Remove(subscriber);
        }
    }

    public void Broadcast(Message message)
    {
        List<ISubscriber> currentSubscribers;
        lock (subscribersLock)
        {
            currentSubscribers = new List<ISubscriber>(subscribers);
        }

        List<Task> deliveryTasks = new List<Task>();

        foreach (ISubscriber subscriber in currentSubscribers)
        {
            deliveryTasks.Add(Task.Run(() =>
            {
                try
                {
                    subscriber.OnMessage(message);
                }
                catch (Exception e)
                {
                    Console.Error.WriteLine($"Error delivering message to subscriber {subscriber.GetId()}: {e.Message}");
                }
            }));
        }

        Task.WaitAll(deliveryTasks.ToArray());
    }
}