using System.Collections.Concurrent;

class PubSubService
{
    private static PubSubService instance;
    private static readonly object instanceLock = new object();

    private readonly ConcurrentDictionary<string, Topic> topicRegistry;

    private PubSubService()
    {
        topicRegistry = new ConcurrentDictionary<string, Topic>();
    }

    public static PubSubService GetInstance()
    {
        if (instance == null)
        {
            lock (instanceLock)
            {
                if (instance == null)
                {
                    instance = new PubSubService();
                }
            }
        }
        return instance;
    }

    public void CreateTopic(string topicName)
    {
        topicRegistry.TryAdd(topicName, new Topic(topicName));
        Console.WriteLine($"Topic {topicName} created");
    }

    public void Subscribe(string topicName, ISubscriber subscriber)
    {
        if (!topicRegistry.TryGetValue(topicName, out Topic topic))
        {
            throw new ArgumentException($"Topic not found: {topicName}");
        }
        topic.AddSubscriber(subscriber);
        Console.WriteLine($"Subscriber '{subscriber.GetId()}' subscribed to topic: {topicName}");
    }

    public void Unsubscribe(string topicName, ISubscriber subscriber)
    {
        if (topicRegistry.TryGetValue(topicName, out Topic topic))
        {
            topic.RemoveSubscriber(subscriber);
        }
        Console.WriteLine($"Subscriber '{subscriber.GetId()}' unsubscribed from topic: {topicName}");
    }

    public void Publish(string topicName, Message message)
    {
        Console.WriteLine($"Publishing message to topic: {topicName}");
        if (!topicRegistry.TryGetValue(topicName, out Topic topic))
        {
            throw new ArgumentException($"Topic not found: {topicName}");
        }
        topic.Broadcast(message);
    }

    public void Shutdown()
    {
        Console.WriteLine("PubSubService shutting down...");
        Console.WriteLine("PubSubService shutdown complete.");
    }
}