namespace PubSubSystem
{
    public class Message
    {
        public string Content { get; }

        public Message(string content)
        {
            Content = content;
        }
    }
}